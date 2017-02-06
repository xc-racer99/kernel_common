/* linux/arch/arm/mach-s5pv210/mach-aries.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/serial_core.h>

#include <asm/hardware/vic.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/mach-types.h>

#include <mach/map.h>
#include <mach/regs-clock.h>

#include <plat/gpio-cfg.h>
#include <plat/regs-serial.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <plat/s5p-time.h>
#include <plat/pm.h>

#include <mach/aries.h>

#include "common.h"

/* Following are default values for UCON, ULCON and UFCON UART registers */
#define ARIES_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#define ARIES_ULCON_DEFAULT	S3C2410_LCON_CS8

#define ARIES_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)

static struct s3c2410_uartcfg aries_uartcfgs[] __initdata = {
	[0] = {
		.hwport		= 0,
		.flags		= 0,
		.ucon		= ARIES_UCON_DEFAULT,
		.ulcon		= ARIES_ULCON_DEFAULT,
		.ufcon		= ARIES_UFCON_DEFAULT,
	},
	[1] = {
		.hwport		= 1,
		.flags		= 0,
		.ucon		= ARIES_UCON_DEFAULT,
		.ulcon		= ARIES_ULCON_DEFAULT,
		.ufcon		= ARIES_UFCON_DEFAULT,
	},
	[2] = {
		.hwport		= 2,
		.flags		= 0,
		.ucon		= ARIES_UCON_DEFAULT,
		.ulcon		= ARIES_ULCON_DEFAULT,
		.ufcon		= ARIES_UFCON_DEFAULT,
	},
	[3] = {
		.hwport		= 3,
		.flags		= 0,
		.ucon		= ARIES_UCON_DEFAULT,
		.ulcon		= ARIES_ULCON_DEFAULT,
		.ufcon		= ARIES_UFCON_DEFAULT,
	},
};

static struct platform_device *aries_devices[] __initdata = {
	&s3c_device_rtc,
	&s3c_device_wdt,
};

static void __init aries_fixup(struct tag *tag, char **cmdline,
		struct meminfo *mi)
{
	mi->bank[0].start = 0x30000000;
	mi->bank[0].size = 80 * SZ_1M;

	mi->bank[1].start = 0x40000000;
	mi->bank[1].size = 256 * SZ_1M;

	mi->bank[2].start = 0x50000000;
	mi->bank[2].size = 128 * SZ_1M;
	mi->nr_banks = 3;
}

static void __init aries_map_io(void)
{
	s5pv210_init_io(NULL, 0);
	s3c24xx_init_clocks(24000000);
	s3c24xx_init_uarts(aries_uartcfgs, ARRAY_SIZE(aries_uartcfgs));
	s5p_set_timer_source(S5P_PWM3, S5P_PWM4);
}

static void __init aries_machine_init(void)
{
	s3c_pm_init();

	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));
}

MACHINE_START(ARIES, "ARIES")
	.atag_offset	= 0x100,
	.fixup		= aries_fixup,
	.init_irq	= s5pv210_init_irq,
	.handle_irq	= vic_handle_irq,
	.map_io		= aries_map_io,
	.init_machine	= aries_machine_init,
	.timer		= &s5p_timer,
	.restart	= s5pv210_restart,
MACHINE_END
