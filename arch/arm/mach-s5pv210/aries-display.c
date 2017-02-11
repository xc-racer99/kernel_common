/* linux/arch/arm/mach-s5pv210/aries-mfd.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_gpio.h>

#include <mach/irqs.h>
#include <mach/gpio.h>
#include <mach/power-domain.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>

#include <plat/devs.h>
#include <plat/fb.h>
#include <plat/gpio-cfg.h>

#include <../../../drivers/video/samsung/s3cfb.h>

#include <mach/aries.h>

static struct s3cfb_lcd s6e63m0 = {
	.width = S5PV210_LCD_WIDTH,
	.height = S5PV210_LCD_HEIGHT,
	.p_width = 52,
	.p_height = 86,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 16,
		.h_bp = 16,
		.h_sw = 2,
		.v_fp = 28,
		.v_fpe = 1,
		.v_bp = 1,
		.v_bpe = 1,
		.v_sw = 2,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 1,
	},
};

static void tl2796_cfg_gpio(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < 8; i++)
		s3c_gpio_cfgpin(S5PV210_GPF0(i), S3C_GPIO_SFN(2));

	for (i = 0; i < 8; i++)
		s3c_gpio_cfgpin(S5PV210_GPF1(i), S3C_GPIO_SFN(2));

	for (i = 0; i < 8; i++)
		s3c_gpio_cfgpin(S5PV210_GPF2(i), S3C_GPIO_SFN(2));

	for (i = 0; i < 4; i++)
		s3c_gpio_cfgpin(S5PV210_GPF3(i), S3C_GPIO_SFN(2));

	/* mDNIe SEL: why we shall write 0x2 ? */
#ifdef CONFIG_FB_S3C_MDNIE
	writel(0x1, S5P_MDNIE_SEL);
#else
	writel(0x2, S5P_MDNIE_SEL);
#endif

	s3c_gpio_setpull(GPIO_OLED_DET, S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(GPIO_OLED_ID, S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(GPIO_DIC_ID, S3C_GPIO_PULL_NONE);
}

void lcd_cfg_gpio_early_suspend(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF0(i), S3C_GPIO_OUTPUT);
		gpio_set_value(S5PV210_GPF0(i), 0);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF1(i), S3C_GPIO_OUTPUT);
		gpio_set_value(S5PV210_GPF1(i), 0);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF2(i), S3C_GPIO_OUTPUT);
		gpio_set_value(S5PV210_GPF2(i), 0);
	}

	for (i = 0; i < 4; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF3(i), S3C_GPIO_OUTPUT);
		gpio_set_value(S5PV210_GPF3(i), 0);
	}

	gpio_set_value(GPIO_MLCD_RST, 0);

	gpio_set_value(GPIO_DISPLAY_CS, 0);
	gpio_set_value(GPIO_DISPLAY_CLK, 0);
	gpio_set_value(GPIO_DISPLAY_SI, 0);

	s3c_gpio_setpull(GPIO_OLED_DET, S3C_GPIO_PULL_DOWN);
	s3c_gpio_setpull(GPIO_OLED_ID, S3C_GPIO_PULL_DOWN);
	s3c_gpio_setpull(GPIO_DIC_ID, S3C_GPIO_PULL_DOWN);
}
EXPORT_SYMBOL(lcd_cfg_gpio_early_suspend);

void lcd_cfg_gpio_late_resume(void)
{

}
EXPORT_SYMBOL(lcd_cfg_gpio_late_resume);

static int tl2796_reset_lcd(struct platform_device *pdev)
{
	int err;

	err = gpio_request(GPIO_MLCD_RST, "MLCD_RST");
	if (err) {
		printk(KERN_ERR "failed to request MP0(5) for "
				"lcd reset control\n");
		return err;
	}

	gpio_direction_output(GPIO_MLCD_RST, 1);
	msleep(10);

	gpio_set_value(GPIO_MLCD_RST, 0);
	msleep(10);

	gpio_set_value(GPIO_MLCD_RST, 1);
	msleep(10);

	gpio_free(GPIO_MLCD_RST);

	return 0;
}

static int tl2796_backlight_on(struct platform_device *pdev)
{
	return 0;
}

static struct s3c_platform_fb tl2796_data __initdata = {
	.hw_ver		= 0x62,
	.clk_name	= "sclk_fimd",
	.nr_wins	= 5,
	.default_win	= CONFIG_FB_S3C_DEFAULT_WINDOW,
	.swap		= FB_SWAP_HWORD | FB_SWAP_WORD,

	.lcd = &s6e63m0,
	.cfg_gpio	= tl2796_cfg_gpio,
	.backlight_on	= tl2796_backlight_on,
	.reset_lcd	= tl2796_reset_lcd,
};

#define LCD_BUS_NUM     3
#define DISPLAY_CS      S5PV210_MP01(1)
#define SUB_DISPLAY_CS  S5PV210_MP01(2)
#define DISPLAY_CLK     S5PV210_MP04(1)
#define DISPLAY_SI      S5PV210_MP04(3)

static struct spi_board_info spi_board_info[] __initdata = {
	{
		.modalias	= "tl2796",
		.platform_data	= &aries_panel_data,
		.max_speed_hz	= 1200000,
		.bus_num	= LCD_BUS_NUM,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,
		.controller_data = (void *)DISPLAY_CS,
	},
};

static struct spi_gpio_platform_data tl2796_spi_gpio_data = {
	.sck	= DISPLAY_CLK,
	.mosi	= DISPLAY_SI,
	.miso	= -1,
	.num_chipselect = 2,
};

static struct platform_device s3c_device_spi_gpio = {
	.name	= "spi_gpio",
	.id	= LCD_BUS_NUM,
	.dev	= {
		.parent		= &s3c_device_fb.dev,
		.platform_data	= &tl2796_spi_gpio_data,
	},
};

static struct platform_device *aries_devices[] __initdata = {
	&s3c_device_fb,
	&s3c_device_g3d,
	&s3c_device_lcd,
	&s3c_device_spi_gpio,

	&s5pv210_pd_lcd,
	&s5pv210_pd_g3d,
};

void __init aries_display_init(void)
{
	/* register devices */
	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));

	/* panel */
	spi_register_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
	s3cfb_set_platdata(&tl2796_data);
}
