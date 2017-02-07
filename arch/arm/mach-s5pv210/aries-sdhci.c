/* linux/arch/arm/mach-s5pv210/aries-sdhci.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/delay.h>
#include <linux/switch.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdhci.h>
#include <linux/mmc/pm.h>

#include <mach/irqs.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/devs.h>
#include <plat/sdhci.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-sdhci.h>

#include <mach/aries.h>

#define S3C_SDHCI_CTRL3_FCSELTX_INVERT  (0)
#define S3C_SDHCI_CTRL3_FCSELTX_BASIC \
	(S3C_SDHCI_CTRL3_FCSEL3 | S3C_SDHCI_CTRL3_FCSEL2)
#define S3C_SDHCI_CTRL3_FCSELRX_INVERT  (0)
#define S3C_SDHCI_CTRL3_FCSELRX_BASIC \
	(S3C_SDHCI_CTRL3_FCSEL1 | S3C_SDHCI_CTRL3_FCSEL0)

void (*aries_sdhci1_notify_func)(struct platform_device *, int);

static int aries_sdhci1_ext_cd_init(void (*notify_func)(struct platform_device *, int))
{
	aries_sdhci1_notify_func = notify_func;
	return 0;
}

static void aries_setup_sdhci1_cfg_clock(struct platform_device *dev,
			       struct sdhci_host *host, unsigned int clock)
{
	u32 ctrl2;
	u32 ctrl3;

	ctrl2 = readl(host->ioaddr + S3C_SDHCI_CONTROL2);
	ctrl2 &= S3C_SDHCI_CTRL2_SELBASECLK_MASK;
	ctrl2 |= (S3C64XX_SDHCI_CTRL2_ENSTAASYNCCLR |
		  S3C64XX_SDHCI_CTRL2_ENCMDCNFMSK |
		  S3C_SDHCI_CTRL2_DFCNT_NONE |
		  S3C_SDHCI_CTRL2_ENCLKOUTHOLD);

	if (clock <= (400 * 1000)) {
		ctrl2 &= ~(S3C_SDHCI_CTRL2_ENFBCLKTX |
			   S3C_SDHCI_CTRL2_ENFBCLKRX);
		ctrl3 = 0;
	} else {
		ctrl2 |= S3C_SDHCI_CTRL2_ENFBCLKTX |
			 S3C_SDHCI_CTRL2_ENFBCLKRX;

		if ((clock >  25 * 1000 * 1000) && (clock < 37 * 1000 * 1000))
			ctrl3 = S3C_SDHCI_CTRL3_FCSELTX_BASIC |
				S3C_SDHCI_CTRL3_FCSELRX_BASIC;
		else
			ctrl3 = S3C_SDHCI_CTRL3_FCSELTX_BASIC |
				S3C_SDHCI_CTRL3_FCSELRX_INVERT;
	}


	writel(ctrl2, host->ioaddr + S3C_SDHCI_CONTROL2);
	writel(ctrl3, host->ioaddr + S3C_SDHCI_CONTROL3);
}

static struct s3c_sdhci_platdata hsmmc1_platdata = {
	.cd_type		= S3C_SDHCI_CD_EXTERNAL,
	.ext_cd_init	= aries_sdhci1_ext_cd_init,
	.cfg_clock		= aries_setup_sdhci1_cfg_clock,
	.host_caps2		= MMC_CAP2_BROKEN_VOLTAGE,
	.host_quirks	= SDHCI_QUIRK_BROKEN_TIMEOUT_VAL,
	.pm_caps		= MMC_PM_KEEP_POWER | MMC_PM_IGNORE_PM_NOTIFY,
	.pm_flags		= MMC_PM_KEEP_POWER | MMC_PM_IGNORE_PM_NOTIFY,
};

static void aries_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	s5pv210_setup_sdhci2_cfg_gpio(dev, width);

	s3c_gpio_cfgrange_nopull(GPIO_T_FLASH_DETECT, 1, EINT_MODE);
}

static struct s3c_sdhci_platdata hsmmc2_platdata = {
	.cd_type		= S3C_SDHCI_CD_GPIO,
	.ext_cd_gpio		= GPIO_T_FLASH_DETECT,
	.ext_cd_gpio_invert	= true,
	.cfg_gpio		= aries_setup_sdhci2_cfg_gpio,
	.host_caps2		= MMC_CAP2_BROKEN_VOLTAGE,
};

static struct platform_device *aries_devices[] __initdata = {
	&s3c_device_hsmmc1,
	&s3c_device_hsmmc2,
};

void __init aries_sdhci_init(void)
{
	/* hsmmc1 */
	s5pv210_default_sdhci1();
	s3c_sdhci1_set_platdata(&hsmmc1_platdata);

	/* hsmmc2 */
	s5pv210_default_sdhci2();
	s3c_sdhci2_set_platdata(&hsmmc2_platdata);

	/* register devices */
	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));
}
