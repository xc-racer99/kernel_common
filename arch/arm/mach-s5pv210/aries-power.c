/* linux/arch/arm/mach-s5pv210/aries-mfd.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/max17040_battery.h>
#include <linux/power/charger-manager.h>
#include <linux/regulator/consumer.h>
#include <linux/types.h>

#include <mach/irqs.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/adc.h>
#include <plat/devs.h>
#include <plat/iic.h>
#include <plat/irqs.h>

#include <mach/aries.h>

#define ADC_NUM_SAMPLES		10
#define ADC_LIMIT_ERR_COUNT	5

#define S3C_ADC_TEMPERATURE	6

#define HIGH_BLOCK_TEMP		500
#define HIGH_RECOVER_TEMP	430
#define LOW_BLOCK_TEMP		0
#define LOW_RECOVER_TEMP	30

/**
 * @adc_value : max8998 adc value
 * @temperature : temperature(C) * 10
 */
struct temp_adc_table_data {
	int adc_value;
	int temperature;
};

static struct temp_adc_table_data aries_temper[] = {
	/* ADC, Temperature (C) - froyo */
	{ 206,		700	},
	{ 220,		690	},
	{ 240,		680	},
	{ 254,		670	},
	{ 265,		660	},
	{ 279,		650	},
	{ 290,		640	}, // [[junghyunseok edit temperature table 20100531
	{ 296,		630	},
	{ 303,		620	},
	{ 311,		610	},
	{ 325,		600	},
	{ 334,		590	},
	{ 347,		580	},
	{ 360,		570	},
	{ 375,		560	},
	{ 396,		550	},
	{ 405,		540	},
	{ 416,		530	},
	{ 431,		520	},
	{ 440,		510	}, // [[junghyunseok edit temperature table 20100531
	{ 461,		500	},
	{ 478,		490	},
	{ 495,		480	},
	{ 512,		470	},
	{ 529,		460	},
	{ 548,		450	},
	{ 565,		440	},
	{ 580,		430	}, // [[junghyunseok edit temperature table 20100531
	{ 599,		420	},
	{ 616,		410	},
	{ 636,		400	},
	{ 654,		390	},
	{ 672,		380	},
	{ 690,		370	},
	{ 708,		360	},
	{ 728,		350	},
	{ 750,		340	},
	{ 772,		330	},
	{ 794,		320	},
	{ 816,		310	},
	{ 841,		300	},
	{ 865,		290	},
	{ 889,		280	},
	{ 913,		270	},
	{ 937,		260	},
	{ 963,		250	},
	{ 987,		240	},
	{ 1011,		230	},
	{ 1035,		220	},
	{ 1059,		210	},
	{ 1086,		200	},
	{ 1110,		190	},
	{ 1134,		180	},
	{ 1158,		170	},
	{ 1182,		160	},
	{ 1206,		150	},
	{ 1230,		140	},
	{ 1254,		130	},
	{ 1278,		120	},
	{ 1302,		110	},
	{ 1326,		100	},
	{ 1346,		90	},
	{ 1366,		80	},
	{ 1386,		70	},
	{ 1406,		60	},
	{ 1420,		50	},
	{ 1430,		40	},
	{ 1450,		30	},
	{ 1460,		20	},
	{ 1470,		10	},
	{ 1480,		0	}, // 20
	{ 1490,		-10	},
	{ 1500,		-20	},
	{ 1510,		-30	},
	{ 1550,		-40	},
	{ 1635,		-50	},
	{ 1649,		-60	},
	{ 1663,		-70	},
	{ 1677,		-80	},
	{ 1691,		-90	},
	{ 1705,		-100	}, // 10
	{ 1722,		-110	},
	{ 1739,		-120	},
	{ 1756,		-130	},
	{ 1773,		-140	},
	{ 1790,		-150	},
	{ 1804,		-160	},
	{ 1818,		-170	},
	{ 1832,		-180	},
	{ 1846,		-190	},
	{ 1859,		-200	},
};

static int s3c_get_adc_data(int ch)
{
	int adc_data;
	int adc_max = -1;
	int adc_min = 1 << 11;
	int adc_total = 0;
	int i, j;
	static struct s3c_adc_client *client;

	if (IS_ERR(client))
		return PTR_ERR(client);
	
	if (!client) {
		client = s3c_adc_register(&s3c_device_i2c9, NULL, NULL, 0);
		if (IS_ERR(client)) {
			pr_err("aries-power: cannot register adc\n");
			return PTR_ERR(client);
		}
	}
	
	for (i = 0; i < ADC_NUM_SAMPLES; i++) {
		adc_data = s3c_adc_read(client, ch);
		if (adc_data == -EAGAIN) {
			for (j = 0; j < ADC_LIMIT_ERR_COUNT; j++) {
				msleep(20);
				adc_data = s3c_adc_read(client, ch);
				if (adc_data > 0)
					break;
			}
			if (j >= ADC_LIMIT_ERR_COUNT) {
				pr_err("%s: Retry count exceeded[ch:%d]\n",
					__func__, ch);
				return adc_data;
			}
		} else if (adc_data < 0) {
			pr_err("%s: Failed read adc value : %d [ch:%d]\n",
				__func__, adc_data, ch);
			return adc_data;
		}

		if (adc_data > adc_max)
			adc_max = adc_data;
		if (adc_data < adc_min)
			adc_min = adc_data;

		adc_total += adc_data;
	}
	return (adc_total - adc_max - adc_min) / (ADC_NUM_SAMPLES - 2);
}

static int aries_battery_temp(void)
{
	int array_size = ARRAY_SIZE(aries_temper);
	int temp_adc = s3c_get_adc_data(S3C_ADC_TEMPERATURE);
	int mid;
	int left_side = 0;
	int right_side = array_size - 1;
	int temp = 0;

	if (temp_adc < 0) {
		pr_err("%s : Invalid temperature adc value [%d]\n",
			__func__, temp_adc);
		return temp_adc;
	}

	while (left_side <= right_side) {
		mid = (left_side + right_side) / 2;
		if (mid == 0 || mid == array_size - 1 ||
				(aries_temper[mid].adc_value <= temp_adc &&
				 aries_temper[mid+1].adc_value > temp_adc)) {
			temp = aries_temper[mid].temperature;
			break;
		} else if (temp_adc - aries_temper[mid].adc_value > 0) {
			left_side = mid + 1;
		} else {
			right_side = mid - 1;
		}
	}

	return temp;
}

static struct max17040_platform_data max17040_pdata = {
	.rcomp_value = 0xD000,
};

static struct i2c_board_info i2c9_devs[] __initdata = {
	{
		I2C_BOARD_INFO("max17040", (0x6D >> 1)),
		.platform_data = &max17040_pdata,
		.irq = IRQ_EINT(27),
	},
};

static char *charger_src[] = {
	"max8998_usb",
	"max8998_ac",
	NULL,
};

static struct regulator_bulk_data charger_regulators[] = {
	{ .supply = "charger", },
};

int cm_battery_temp(int *mC)
{
	int temp = aries_battery_temp();
	int ret = 0;

	if (temp >= HIGH_BLOCK_TEMP) {
		ret = 1;
	} else if (temp <= HIGH_RECOVER_TEMP && temp >= LOW_RECOVER_TEMP) {
		ret = 0;
	} else if (temp <= LOW_BLOCK_TEMP) {
		ret = -1;
	}

	*mC = temp * 100;

	return ret;
}

static struct charger_desc charger_pdata = {
	.psy_name		= "battery",
	.polling_mode		= CM_POLL_ALWAYS,
	.polling_interval_ms	= 10 * 60,
	.fullbatt_uV		= 4140000,
	.battery_present	= CM_FUEL_GAUGE,
	.psy_charger_stat	= charger_src,
	.psy_fuel_gauge		= "max17040_battery",
	.charger_regulators	= charger_regulators,
	.num_charger_regulators	= ARRAY_SIZE(charger_regulators),
	.temperature_out_of_range = cm_battery_temp,
	.measure_battery_temp	= true,
};

static struct platform_device aries_charger = {
	.name		= "charger-manager",
	.id		= -1,
	.dev = {
		.platform_data = &charger_pdata,
	}
};

static struct platform_device *aries_devices[] __initdata = {
	&s3c_device_i2c9,
	&aries_charger,
};

void __init aries_power_init(void)
{
	/* max17040 */
	i2c_register_board_info(9, i2c9_devs, ARRAY_SIZE(i2c9_devs));

	/* register devices */
	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));
}
