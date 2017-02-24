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
#include <linux/platform_data/s3c-hsotg.h>

#include <asm/hardware/vic.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/mach-types.h>

#include <mach/map.h>
#include <mach/media.h>
#include <mach/regs-clock.h>

#include <plat/gpio-cfg.h>
#include <plat/regs-serial.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <plat/s5p-time.h>
#include <plat/media.h>
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

#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0 (11264 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2 (11264 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC0 (14336 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC1 (21504 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMD (S5PV210_LCD_WIDTH * \
					     S5PV210_LCD_HEIGHT * 4 * \
					     (CONFIG_FB_S3C_NR_BUFFERS + \
						 (CONFIG_FB_S3C_NUM_OVLY_WIN * \
						  CONFIG_FB_S3C_NUM_BUF_OVLY_WIN)))
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG (916 * SZ_1K)

static struct s5p_media_device aries_media_devs[] = {
#ifdef CONFIG_VIDEO_MFC50
	[0] = {
		.id = S5P_MDEV_MFC,
		.name = "mfc",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC0,
		.paddr = 0,
	},
	[1] = {
		.id = S5P_MDEV_MFC,
		.name = "mfc",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC1,
		.paddr = 0,
	},
#endif
#ifdef CONFIG_VIDEO_FIMC
	[2] = {
		.id = S5P_MDEV_FIMC0,
		.name = "fimc0",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0,
		.paddr = 0,
	},
	[3] = {
		.id = S5P_MDEV_FIMC2,
		.name = "fimc2",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2,
		.paddr = 0,
	},
#endif
#ifdef CONFIG_VIDEO_JPEG_V2
	[4] = {
		.id = S5P_MDEV_JPEG,
		.name = "jpeg",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG,
		.paddr = 0,
	},
#endif
	[5] = {
		.id = S5P_MDEV_FIMD,
		.name = "fimd",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMD,
		.paddr = 0,
	},
};

static struct platform_device *aries_devices[] __initdata = {
	&s3c_device_adc,
	&s3c_device_rtc,
	&s3c_device_wdt,

	&s3c_device_timer[0],
	&s3c_device_timer[1],
	&s3c_device_timer[2],
};

static void __init aries_fixup(struct tag *tag, char **cmdline,
		struct meminfo *mi)
{
	mi->bank[0].start = 0x30000000;
	mi->bank[0].size = 80 * SZ_1M;

	mi->bank[1].start = 0x40000000;
	mi->bank[1].size = 384 * SZ_1M;
	mi->nr_banks = 2;
}

static void __init aries_map_io(void)
{
	s5pv210_init_io(NULL, 0);
	s3c24xx_init_clocks(24000000);
	s3c24xx_init_uarts(aries_uartcfgs, ARRAY_SIZE(aries_uartcfgs));
	s5p_set_timer_source(S5P_PWM3, S5P_PWM4);

	s5p_reserve_bootmem(aries_media_devs,
		ARRAY_SIZE(aries_media_devs), S5P_RANGE_MFC);
}

static struct s3c_hsotg_plat aries_hsotg_pdata;

static void __init aries_machine_init(void)
{

	aries_pm_init();

	/* Initialize the GPIOs */
	aries_gpio_init();

	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));

	/* Initialize max8998 */
	aries_mfd_init();

	/* Power */
	aries_power_init();

	/* Display */
	aries_display_init();

	/* Input */
	aries_input_init();

	/* fsa940 */
	aries_switch_init();

	/* OneNAND */
	aries_onenand_init();

	/* SDHCI */
	aries_sdhci_init();

	/* Wifi */
	aries_wifi_init();

	s3c_hsotg_set_platdata(&aries_hsotg_pdata);
	platform_device_register(&s3c_device_usb_hsotg);
}

MACHINE_START(ARIES, "ARIES")
	.atag_offset	= 0x100,
	.fixup		= aries_fixup,
	.init_irq	= s5pv210_init_irq,
	.handle_irq	= vic_handle_irq,
	.map_io		= aries_map_io,
	.init_machine	= aries_machine_init,
	.timer		= &s5p_timer,
	.restart	= aries_restart,
MACHINE_END
