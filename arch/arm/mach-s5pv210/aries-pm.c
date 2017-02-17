#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/pm.h>
#include <linux/reboot.h>
#include <linux/slab.h>
#include <linux/string.h>

#include <asm/io.h>
#include <asm/system_info.h>

#include <mach/regs-clock.h>

#include <plat/map-base.h>
#include <plat/pm.h>
#include <plat/watchdog-reset.h>

#include <mach/aries.h>

#define REBOOT_MODE_NONE 0
#define REBOOT_MODE_RECOVERY 2

#define S5PV210_PS_HOLD_CONTROL_REG (S3C_VA_SYS+0xE81C)

/* Ugly hack to inject parameters (e.g. device serial, bootmode) into /proc/cmdline */
static void __init aries_inject_cmdline(void) {
	char *new_command_line;
	int bootmode = __raw_readl(S5P_INFORM6);
	int size;

	size = strlen(boot_command_line);
	new_command_line = kmalloc(size + 40 + 11, GFP_KERNEL);
	strcpy(new_command_line, saved_command_line);
	size += sprintf(new_command_line + size, " androidboot.serialno=%08X%08X",
				system_serial_high, system_serial_low);

	/* LPM charging mode */
	if (readl(S5P_INFORM5)) {
		size += sprintf(new_command_line + size, " androidboot.mode=charger");
	} else {
		/* Only write bootmode when less than 10 to prevent confusion with watchdog
		 * reboot (0xee = 238)
		 */
		if (bootmode < 10) {
			size += sprintf(new_command_line + size, " bootmode=%d", bootmode);
		}
	}

	saved_command_line = new_command_line;
}

static int aries_notifier_call(struct notifier_block *this,
					unsigned long code, void *_cmd)
{
	int mode = REBOOT_MODE_NONE;

	if ((code == SYS_RESTART) && _cmd) {
		if (!strcmp((char *)_cmd, "recovery"))
			mode = REBOOT_MODE_RECOVERY;
		else
			mode = REBOOT_MODE_NONE;
	}
	__raw_writel(mode, S5P_INFORM6);

	return NOTIFY_DONE;
}

static struct notifier_block aries_reboot_notifier = {
	.notifier_call = aries_notifier_call,
};

static void aries_power_off(void)
{
	while (1) {
		/* Wait for power button release */
		if (gpio_get_value(GPIO_nPOWER)) {
			pr_info("%s: set PS_HOLD low\n", __func__);

			/* PS_HOLD high  PS_HOLD_CONTROL, R/W, 0xE010_E81C */
			writel(readl(S5PV210_PS_HOLD_CONTROL_REG) & 0xFFFFFEFF,
			       S5PV210_PS_HOLD_CONTROL_REG);

			pr_crit("%s: should not reach here!\n", __func__);
		}

		/* If power button is not released, wait and check TA again */
		pr_info("%s: PowerButton is not released.\n", __func__);
		mdelay(1000);
	}
}

void aries_restart(char mode, const char *cmd)
{
	/* On a normal reboot, INFORM6 will contain a small integer
	 * reason code from the notifier hook.  On a panic, it will
	 * contain the 0xee we set at boot.  Write 0xbb to differentiate
	 * a watchdog-timeout-and-reboot (0xee) from a controlled reboot
	 * (0xbb)
	 */
	if (__raw_readl(S5P_INFORM6) == 0xee)
		__raw_writel(0xbb, S5P_INFORM6);

	/* Turn off low power mode */
	writel(0x12345678, S5P_INFORM5);

	arch_wdt_reset();
}

void __init aries_pm_init(void)
{
	aries_inject_cmdline();

	pm_power_off = aries_power_off;

	s3c_pm_init();

	register_reboot_notifier(&aries_reboot_notifier);

	/* write something into the INFORM6 register that we can use to
	 * differentiate an unclear reboot from a clean reboot (which
	 * writes a small integer code to INFORM6).
	 */
	__raw_writel(0xee, S5P_INFORM6);
}
