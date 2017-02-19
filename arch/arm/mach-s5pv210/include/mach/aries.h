/* linux/arch/arm/mach-s5pv210/include/mach/aries.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ARIES_H
#define __ARIES_H __FILE__

#include <linux/mfd/max8998.h>

#define S5PV210_LCD_WIDTH	480
#define S5PV210_LCD_HEIGHT	800

/* inits */
void aries_display_init(void) __init;
void aries_gpio_init(void) __init;
void aries_input_init(void) __init;
void aries_mfd_init(void) __init;
void aries_onenand_init(void) __init;
void aries_pm_init(void) __init;
void aries_power_init(void) __init;
void aries_sdhci_init(void) __init;
void aries_switch_init(void) __init;
void aries_wifi_init(void) __init;

/* devices */
extern struct s5p_panel_data aries_panel_data;

/* restart handler */
void aries_restart(char mode, const char *cmd);

/* USB switch callback */
extern struct max8998_charger_callbacks *charger_callbacks;
extern enum cable_type_t set_cable_status;
#endif
