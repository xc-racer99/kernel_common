/* linux/arch/arm/mach-s5pv210/aries-wifi.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/wlan_plat.h>
#include <linux/delay.h>
#include <linux/gpio.h>

#include <mach/irqs.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/devs.h>
#include <plat/sdhci.h>
#include <plat/gpio-cfg.h>

#include <mach/aries.h>

extern void (*aries_sdhci1_notify_func)(struct platform_device *, int);

static int aries_wifi_power(int on)
{
	if (on) {
		s3c_gpio_slp_cfgpin(GPIO_WLAN_BT_EN, S3C_GPIO_SLP_OUT1);
		s3c_gpio_slp_cfgpin(GPIO_WLAN_RST, S3C_GPIO_SLP_OUT1);

		gpio_set_value(GPIO_WLAN_BT_EN, 1);
		gpio_set_value(GPIO_WLAN_RST, 1);
		gpio_set_value(GPIO_WLAN_WAKE, 0);

		msleep(200);
	} else {
		s3c_gpio_slp_cfgpin(GPIO_WLAN_BT_EN, S3C_GPIO_SLP_OUT0);
		s3c_gpio_slp_cfgpin(GPIO_WLAN_RST, S3C_GPIO_SLP_OUT0);

		gpio_set_value(GPIO_WLAN_RST, 0);
		gpio_set_value(GPIO_WLAN_BT_EN, 0);
	}

	return 0;
}

static int aries_wifi_reset(int on)
{
	gpio_set_value(GPIO_WLAN_RST, on);
	return 0;
}

static int aries_wifi_set_carddetect(int on)
{
	aries_sdhci1_notify_func(&s3c_device_hsmmc1, on);
	msleep(500); /* wait for carddetect */
	return 0;
}

static struct wifi_platform_data aries_wifi_pdata = {
	.set_power      = aries_wifi_power,
	.set_reset      = aries_wifi_reset,
	.set_carddetect = aries_wifi_set_carddetect,
};

static struct resource aries_wifi_resources[] = {
	[0] = {
		.name		= "bcmdhd_wlan_irq",
		.flags          = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE,
	},
};

static struct platform_device aries_wifi_device = {
	.name		= "bcmdhd_wlan",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(aries_wifi_resources),
	.resource	= aries_wifi_resources,
	.dev		= {
		.platform_data = &aries_wifi_pdata,
	},
};

static void __init aries_wifi_cfg_gpio(void)
{
	s3c_gpio_cfgrange_nopull(GPIO_WLAN_BT_EN, 1, S3C_GPIO_OUTPUT);
	s3c_gpio_slp_setpull_updown(GPIO_WLAN_BT_EN, S3C_GPIO_SLP_PULL_NONE);

	s3c_gpio_cfgall_range(GPIO_WLAN_RST, 1, S3C_GPIO_OUTPUT, S3C_GPIO_PULL_DOWN);
	s3c_gpio_slp_setpull_updown(GPIO_WLAN_RST, S3C_GPIO_SLP_PULL_NONE);

	s3c_gpio_cfgrange_nopull(GPIO_WLAN_WAKE, 1, S3C_GPIO_OUTPUT);

	s3c_gpio_cfgrange_nopull(GPIO_WLAN_HOST_WAKE, 1, EINT_MODE);
	aries_wifi_resources[0].start = gpio_to_irq(GPIO_WLAN_HOST_WAKE);
	aries_wifi_resources[0].end = aries_wifi_resources[0].start;
}

void __init aries_wifi_init(void)
{
	aries_wifi_cfg_gpio();
	platform_device_register(&aries_wifi_device);
}
