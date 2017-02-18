#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/gpio_event.h>
#include <linux/i2c.h>
#include <linux/i2c/atmel_mxt_ts.h>
#include <linux/input/cypress-touchkey.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

#include <mach/gpio.h>

#include <plat/devs.h>
#include <plat/gpio-cfg.h>
#include <plat/iic.h>

#include <mach/aries.h>

/* Cypress Touchkey */
static void touchkey_onoff(int onoff)
{
	gpio_direction_output(_3_GPIO_TOUCH_EN, onoff);

	if (onoff == TOUCHKEY_OFF)
		msleep(30);
	else
		msleep(25);
}

static void touchkey_gpio_sleep(int onoff) {
	if (onoff == TOUCHKEY_ON)
		s3c_gpio_slp_cfgpin(_3_GPIO_TOUCH_EN, S3C_GPIO_SLP_OUT1);
	else
		s3c_gpio_slp_cfgpin(_3_GPIO_TOUCH_EN, S3C_GPIO_SLP_OUT0);
}

static const int touchkey_code[] = {
	KEY_MENU,
	KEY_BACK,
	KEY_HOMEPAGE,
	KEY_SEARCH
};

static struct touchkey_platform_data touchkey_data = {
	.keycode_cnt = ARRAY_SIZE(touchkey_code),
	.keycode = touchkey_code,
	.touchkey_onoff = touchkey_onoff,
	.touchkey_sleep_onoff = touchkey_gpio_sleep,
	.scl_pin = _3_TOUCH_SCL_28V,
	.sda_pin = _3_TOUCH_SDA_28V,
	.en_pin = _3_GPIO_TOUCH_EN,
};

static struct i2c_board_info i2c10_devs[] __initdata = {
	{
		I2C_BOARD_INFO(CYPRESS_TOUCHKEY_DEV_NAME, 0x20),
		.platform_data = &touchkey_data,
	},
};

static void __init touchkey_gpio_init(void)
{
	int ret = 0;

	ret = gpio_request(_3_GPIO_TOUCH_EN, "TOUCH_EN");
	if (ret)
		printk(KERN_ERR "Failed to request gpio touch_en.\n");

	/* gpio interrupt */
	s3c_gpio_cfgrange_nopull(_3_GPIO_TOUCH_INT, 1, _3_GPIO_TOUCH_INT_AF);
	ret = s5p_register_gpio_interrupt(_3_GPIO_TOUCH_INT);
	if (ret < 0)
		printk(KERN_ERR "aries-input: unable to register touchkey interrupt\n");
	else
		i2c10_devs[0].irq = ret;
}

/* Hardware Keys */

static struct gpio_event_direct_entry aries_keypad_key_map[] = {
	{
		.gpio	= S5PV210_GPH2(6),
		.code	= KEY_POWER,
	}, {
		.gpio	= S5PV210_GPH3(2),
		.code	= KEY_VOLUMEDOWN,
	}, {
		.gpio	= S5PV210_GPH3(1),
		.code	= KEY_VOLUMEUP,
	}
};

static struct gpio_event_input_info aries_keypad_key_info = {
	.info.func = gpio_event_input_func,
	.info.no_suspend = true,
	.debounce_time.tv64 = 5 * NSEC_PER_MSEC,
	.type = EV_KEY,
	.keymap = aries_keypad_key_map,
	.keymap_size = ARRAY_SIZE(aries_keypad_key_map)
};

static struct gpio_event_info *aries_input_info[] = {
	&aries_keypad_key_info.info,
};


static struct gpio_event_platform_data aries_input_data = {
	.names = {
		"aries-keypad",
		NULL,
	},
	.info = aries_input_info,
	.info_count = ARRAY_SIZE(aries_input_info),
};

static struct platform_device aries_input_device = {
	.name = GPIO_EVENT_DEV_NAME,
	.id = 0,
	.dev = {
		.platform_data = &aries_input_data,
	},
};

/* TSP */
static struct mxt_platform_data qt602240_platform_data = {
	.x_line		= 19,
	.y_line		= 11,
	.x_size		= 800,
	.y_size		= 480,
	.blen		= 0x21,
	.threshold	= 0x28,
	.voltage	= 2800000,              /* 2.8V */
	.orient		= MXT_DIAGONAL,
	.irqflags	= IRQF_TRIGGER_FALLING,
};

static struct s3c2410_platform_i2c i2c2_data __initdata = {
	.flags		= 0,
	.bus_num	= 2,
	.slave_addr	= 0x10,
	.frequency	= 400 * 1000,
	.sda_delay	= 100,
};

static struct i2c_board_info i2c2_devs[] __initdata = {
	{
		I2C_BOARD_INFO("qt602240_ts", 0x4a),
		.platform_data = &qt602240_platform_data,
	},
};

static void __init aries_tsp_init(void)
{
	int gpio, ret;

	gpio = S5PV210_GPJ1(3);		/* XMSMADDR_11 */
	gpio_request(gpio, "TSP_LDO_ON");
	gpio_direction_output(gpio, 1);
	gpio_export(gpio, 0);

	s3c_gpio_cfgall_range(S5PV210_GPJ0(5), 1, S3C_GPIO_SFN(0xf), S3C_GPIO_PULL_UP);
	ret = s5p_register_gpio_interrupt(S5PV210_GPJ0(5));
	if (ret < 0)
		printk(KERN_ERR "aries-input: unable to register tsp interrupt\n");
	else
		i2c2_devs[0].irq = ret;
}

static struct platform_device *aries_devices[] __initdata = {
	&s3c_device_i2c2,
	&s3c_device_i2c10,
	&aries_input_device,
};

void __init aries_input_init(void)
{
	/* register devices */
	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));

	/* TSP: call before I2C 2 registeration */
	aries_tsp_init();

	/* I2C2 */
	s3c_i2c2_set_platdata(&i2c2_data);
	i2c_register_board_info(2, i2c2_devs, ARRAY_SIZE(i2c2_devs));

	/* Cypress Touchkey */
	touchkey_gpio_init();
	i2c_register_board_info(10, i2c10_devs, ARRAY_SIZE(i2c10_devs));
}
