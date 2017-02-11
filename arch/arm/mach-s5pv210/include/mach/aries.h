/* linux/arch/arm/mach-s5pv210/include/mach/aries.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ARIES_H
#define __ARIES_H __FILE__

#define S5PV210_LCD_WIDTH	480
#define S5PV210_LCD_HEIGHT	800

/* inits */
void aries_display_init(void) __init;
void aries_gpio_init(void) __init;
void aries_mfd_init(void) __init;
void aries_onenand_init(void) __init;
void aries_sdhci_init(void) __init;
void aries_switch_init(void) __init;

/* devices */
extern struct s5p_panel_data aries_panel_data;

#endif
