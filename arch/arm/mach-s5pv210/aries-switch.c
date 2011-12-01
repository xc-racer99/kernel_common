/* linux/arch/arm/mach-s5pv210/aries-switch.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/platform_data/fsa9480.h>
#include <linux/switch.h>

#include <mach/irqs.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/devs.h>
#include <plat/gpio-cfg.h>
#include <plat/iic.h>

#include <mach/aries.h>

static struct fsa9480_platform_data fsa9480_pdata = {
	.wakeup	= true,
};

static struct i2c_board_info i2c7_devs[] __initdata = {
	{
		I2C_BOARD_INFO("fsa9480", (0x4A >> 1)),
		.platform_data = &fsa9480_pdata,
		.irq = IRQ_EINT(23),
	},
};

static void __init aries_switch_cfg_gpio(void)
{
	s3c_gpio_cfgpin(GPIO_USB_SEL, S3C_GPIO_OUTPUT);
	s3c_gpio_setpull(GPIO_USB_SEL, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(GPIO_UART_SEL, S3C_GPIO_OUTPUT);
	s3c_gpio_setpull(GPIO_UART_SEL, S3C_GPIO_PULL_NONE);

	s3c_gpio_cfgpin(GPIO_JACK_nINT, S3C_GPIO_SFN(0xf));
	s3c_gpio_setpull(GPIO_JACK_nINT, S3C_GPIO_PULL_NONE);
}

void __init aries_switch_init(void)
{
	/* register device */
	platform_device_register(&s3c_device_i2c7);

	/* switch gpio config */
	aries_switch_cfg_gpio();

	/* register fsa9480 */
	i2c_register_board_info(7, i2c7_devs, ARRAY_SIZE(i2c7_devs));
}
