/* arch/arm/mach-s5pv210/aries-gpio.c
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/gpio.h>

#include <mach/gpio.h>
#include <mach/gpio-aries.h>

#include <plat/cpu.h>
#include <plat/gpio-cfg.h>

#include <mach/aries.h>

#define S3C_GPIO_SETPIN_ZERO	0
#define S3C_GPIO_SETPIN_ONE	1
#define S3C_GPIO_SETPIN_NONE	2

struct gpio_init_data {
	uint num;
	uint cfg;
	uint val;
	uint pud;
	s5p_gpio_drvstr_t drv;
};

static struct gpio_init_data aries_init_gpios[] __initdata = {

    // GPB -----------------------------
	{
		 .num	= S5PV210_GPB(0), // GPIO_CAM_VGA_nSTBY
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(1), // GPIO_MSENSE_nRST
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(2), // GPIO_CAM_VGA_nRST
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(3), // GPIO_BT_nRST
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(4), // GPIO_BOOT_MODE
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(5), // GPIO_WLAN_BT_EN	
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(6),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPB(7),
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPC0 ----------------------------
	{
		 .num	= S5PV210_GPC0(0), // GPIO_REC_PCM_CLK
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC0(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC0(2), // GPIO_REC_PCM_SYNC
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC0(3), // GPIO_REC_PCM_IN
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC0(4), // GPIO_REC_PCM_OUT
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPC1 ----------------------------
	{
		 .num	= S5PV210_GPC1(0), // BLOW_PCM_CLK
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC1(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC1(2),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC1(3),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPC1(4),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPD0 ----------------------------
	{
		 .num	= S5PV210_GPD0(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD0(1), // GPIO_VIBTONE_PWM
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD0(2),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD0(3),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPD1 ----------------------------
	{
		 .num	= S5PV210_GPD1(0), // GPIO_CAM_SDA_29V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD1(1), // GPIO_CAM_SCL_29V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD1(2), // GPIO_FM_SDA_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD1(3), // GPIO_FM_SCL_28V	
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD1(4), // GPIO_TSP_SDA_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPD1(5), // GPIO_TSP_SCL_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPE0 ----------------------------
	{
		 .num	= S5PV210_GPE0(0), // GPIO_CAM_PCLK
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(1), // GPIO_CAM_VSYNC
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(2), // GPIO_CAM_HSYNC
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(3), // GPIO_CAM_D0
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(4), // GPIO_CAM_D1
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(5), // GPIO_CAM_D2
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(6), // GPIO_CAM_D3
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE0(7), // GPIO_CAM_D4
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPE1 ----------------------------
	{
		 .num	= S5PV210_GPE1(0), // GPIO_CAM_D5
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE1(1), // GPIO_CAM_D6
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE1(2), // GPIO_CAM_D7
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE1(3), // GPIO_CAM_MCLK
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPE1(4),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPF3 ----------------------------
	{
		 .num	= S5PV210_GPF3(4), // GPIO_CODEC_LDO_EN
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPF3(5),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPG0 ----------------------------
	{
		 .num	= S5PV210_GPG0(0), // GPIO_NAND_CLK
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG0(1), // GPIO_NAND_CMD
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG0(2), // GPIO_ALS_SCL_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG0(3), // GPIO_NAND_D0
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG0(4), // GPIO_NAND_D1
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG0(5), // GPIO_NAND_D2
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG0(6), // GPIO_NAND_D3
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPG1 ----------------------------
	{
		 .num	= S5PV210_GPG1(0), // GPIO_WLAN_SDIO_CLK
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG1(1), // GPIO_WLAN_SDIO_CMD
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG1(2), // GPIO_WLAN_nRST
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG1(3), // GPIO_WLAN_SDIO_D0
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG1(4), // GPIO_WLAN_SDIO_D1 
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG1(5), // GPIO_WLAN_SDIO_D2 
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG1(6), // GPIO_WLAN_SDIO_D3
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPG2 ----------------------------
	{
		 .num	= S5PV210_GPG2(0), // GPIO_T_FLASH_CLK
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG2(1), // GPIO_T_FLASH_CMD
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG2(2), // GPIO_ALS_SDA_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG2(3), // GPIO_T_FLASH_D0
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG2(4), // GPIO_T_FLASH_D1
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG2(5), // GPIO_T_FLASH_D2
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG2(6), // GPIO_T_FLASH_D3
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPG3 ----------------------------
	{
		.num	= S5PV210_GPG3(0), //CG2900 :nReset
		.cfg	= S3C_GPIO_OUTPUT,
		.val	= S3C_GPIO_SETPIN_ZERO,
		.pud	= S3C_GPIO_PULL_UP,
		.drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		.num	= S5PV210_GPG3(1), //CG2900 :PWR
		.cfg	= S3C_GPIO_OUTPUT,
		.val	= S3C_GPIO_SETPIN_ZERO,
		.pud	= S3C_GPIO_PULL_UP,
		.drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG3(2), // GPIO_GPS_CLK_INT
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG3(3), // GPIO_TA_CURRENT_SEL_AP
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG3(4), // GPIO_BT_WAKE
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG3(5), // GPIO_WLAN_WAKE
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPG3(6),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPH0 ----------------------------
	{
		 .num	= S5PV210_GPH0(0), // GPIO_AP_PS_HOLD
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH0(1), // GPIO_ACC_INT
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH0(2), // GPIO_PS_VOUT
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH0(3), // GPIO_BUCK_1_EN_A
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH0(4), // GPIO_BUCK_1_EN_B
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH0(5), // GPIO_BUCK_2_EN
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* GPIO_DET_35 - 3.5" ear jack */
		 .num	= S5PV210_GPH0(6), // GPIO_DET_35
		 .cfg	= S3C_GPIO_SFN(GPIO_DET_35_AF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH0(7), // GPIO_AP_PMIC_IRQ
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPH1 ----------------------------
	{
		 .num	= S5PV210_GPH1(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH1(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH1(2),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH1(3),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* NFC_IRQ */
		 .num	= S5PV210_GPH1(4),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* NFC_EN */
		 .num	= S5PV210_GPH1(5),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* NFC_FIRM */
		 .num	= S5PV210_GPH1(6),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH1(7), // GPIO_PHONE_ACTIVE
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPH2 ----------------------------
	{
		 .num	= S5PV210_GPH2(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH2(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* GPIO_EAR_SEND_END_35 */
		 .num	= S5PV210_GPH2(2), // GPIO_EAR_SEND_END35, GPIO_KBC2
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH2(3),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH2(4), // GPIO_WLAN_HOST_WAKE
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH2(5), // GPIO_BT_HOST_WAKE
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH2(6), // GPIO_nPOWER
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH2(7), // GPIO_JACK_nINT
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPH3 ----------------------------
	{
		 .num	= S5PV210_GPH3(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH3(1),
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH3(2),
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH3(3),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH3(4), // GPIO_T_FLASH_DETECT
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH3(5), // GPIO_MSENSE_IRQ
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* GPIO_EAR_SEND_END */
		 .num	= S5PV210_GPH3(6), // GPIO_EAR_SEND_END
		 .cfg	= S3C_GPIO_SFN(GPIO_EAR_SEND_END_AF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPH3(7), // GPIO_CP_RST
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPI ----------------------------
	{
		 .num	= S5PV210_GPI(0), // GPIO_CODEC_I2S_CLK
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPI(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPI(2), // GPIO_CODEC_I2S_WS
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPI(3), // GPIO_CODEC_I3S_DI
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPI(4), // GPIO_CODEC_I3S_DO
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPI(5),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPI(6),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPJ0 ----------------------------
	{
		 .num	= S5PV210_GPJ0(0), // GPIO_MSENSE_SCL_28V	
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(2), // GPIO_HWREV_MODE0
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(3), // GPIO_HWREV_MODE1
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(4), // GPIO_HWREV_MODE2
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(5), // GPIO_TOUCH_INT
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(6), // GPIO_CAM_MEGA_EN
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ0(7), // GPIO_HWREV_MODE3
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPJ1 ----------------------------
	{
		 .num	= S5PV210_GPJ1(0), // GPIO_PHONE_ON
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ1(1), // GPIO_VIBTONE_EN1
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ1(2),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ1(3), // GPIO_TOUCH_EN
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ1(4), // GPIO_PS_ON
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ1(5), // GPIO_CAM_MEGA_nRST
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPJ2 ----------------------------
	{
		 .num	= S5PV210_GPJ2(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(2), // GPIO_OLED_DET
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(3), // GPIO_CODEC_XTAL_EN
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(4), // GPIO_FM_INT
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(5), // GPIO_FM_RST	
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(6), // GPIO_EARPATH_SEL
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ2(7), // GPIO_MASSMEMORY_EN
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPJ3 ----------------------------
	{
		 .num	= S5PV210_GPJ3(0), // _3_TOUCH_SDA_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ3(1), // _3_TOUCH_SCL_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ3(2), // _3_GPIO_TOUCH_EN
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, { /* GPIO_EAR_ADC_SEL */
		 .num	= S5PV210_GPJ3(3), // _3_GPIO_TOUCH_CE
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ3(4), // GPIO_USB_SDA_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ3(5), // GPIO_USB_SCL_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ3(6), // GPIO_AP_SDA_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ3(7), // GPIO_AP_SCL_28V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// GPJ4 ----------------------------
	{
		 .num	= S5PV210_GPJ4(0), // GPIO_AP_PMIC_SDA
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ4(1), // _3_GPIO_TOUCH_INT
		 .cfg	= S3C_GPIO_SFN(0xF),
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ4(2), // GPIO_MICBIAS_EN
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ4(3), // GPIO_AP_PMIC_SCL
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_GPJ4(4), // GPIO_TV_EN, GPIO_EAR_MICBIAS_EN
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// MP01 ----------------------------
	{
		 .num	= S5PV210_MP01(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP01(2), // GPIO_SUB_DISPLAY_CS
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP01(5), // GPIO_DIC_ID
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// MP02 ----------------------------
	{
		 .num	= S5PV210_MP02(0),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP02(1),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP02(3),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// MP03 ----------------------------
	{
		 .num	= S5PV210_MP03(3), // GPIO_PDA_ACTIVE
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP03(5), // GPIO_CP_nRST
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP03(6),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP03(7), // GPIO_PCM_SEL
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// MP04 ----------------------------
	{
		 .num	= S5PV210_MP04(0), // GPIO_USB_SEL
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP04(2),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP04(4), // GPIO_A1026_SCL
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP04(5), // GPIO_A1026_SDA
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP04(6),
		 .cfg	= S3C_GPIO_OUTPUT,
		 .val	= S3C_GPIO_SETPIN_ZERO,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP04(7),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
		// MP05 ----------------------------
	{
		 .num	= S5PV210_MP05(0), // FUEL_SCL_18V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP05(1), // FUEL_SDA_18V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP05(2), // GPIO_AP_SCL_18V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP05(3), // GPIO_AP_SDA_18V
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_NONE,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP05(4),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	}, {
		 .num	= S5PV210_MP05(6),
		 .cfg	= S3C_GPIO_INPUT,
		 .val	= S3C_GPIO_SETPIN_NONE,
		 .pud	= S3C_GPIO_PULL_DOWN,
		 .drv	= S5P_GPIO_DRVSTR_LV1,
	},
};

static unsigned int aries_sleep_gpio_table[][3] __initdata = {

	// GPA0 ---------------------------------------------------
	{ S5PV210_GPA0(0), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_BT_UART_RXD
	{ S5PV210_GPA0(1), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_BT_UART_TXD
	{ S5PV210_GPA0(2), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_BT_UART_CTS
	{ S5PV210_GPA0(3), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_BT_UART_RTS
	{ S5PV210_GPA0(4), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPA0(5), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPA0(6), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPA0(7), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},

	// GPA1 ---------------------------------------------------
	{ S5PV210_GPA1(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPA1(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPA1(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPA1(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPB ----------------------------------------------------
	{ S5PV210_GPB(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_CAM_VGA_nSTBY
	{ S5PV210_GPB(1), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_MSENSE_nRST
	{ S5PV210_GPB(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_CAM_VGA_nRST
	{ S5PV210_GPB(3), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPB(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPB(5), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPB(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPB(7), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPC0 ---------------------------------------------------
	{ S5PV210_GPC0(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPC0(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPC0(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPC0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPC0(4), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPC1 ---------------------------------------------------
	{ S5PV210_GPC1(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPC10
	{ S5PV210_GPC1(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPC1(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPC12
	{ S5PV210_GPC1(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPC1(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPD0 ---------------------------------------------------
	{ S5PV210_GPD0(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPD0(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPD0(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPD0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPD1 ---------------------------------------------------
	{ S5PV210_GPD1(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPD1(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPD1(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPD12
	{ S5PV210_GPD1(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPD13
	{ S5PV210_GPD1(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPD1(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPE0 ---------------------------------------------------
	{ S5PV210_GPE0(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE0(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPE1 ---------------------------------------------------
	{ S5PV210_GPE1(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE1(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE1(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPE1(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPE1(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPF0 ---------------------------------------------------
	{ S5PV210_GPF0(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(4), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(6), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF0(7), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPF1 ---------------------------------------------------
	{ S5PV210_GPF1(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(4), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(6), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF1(7), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPF2 ---------------------------------------------------
	{ S5PV210_GPF2(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(4), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(6), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF2(7), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPF3 ---------------------------------------------------
	{ S5PV210_GPF3(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF3(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF3(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF3(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF3(4), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPF3(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPG0 ---------------------------------------------------
	{ S5PV210_GPG0(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPG0(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPG0(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, // GPIO_ALS_SCL_28V
	{ S5PV210_GPG0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPG0(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPG0(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPG0(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// GPG1 ---------------------------------------------------
	{ S5PV210_GPG1(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_SDIO_CLK
	{ S5PV210_GPG1(1), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_SDIO_CMD
	{ S5PV210_GPG1(2), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_nRST
	{ S5PV210_GPG1(3), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_SDIO_D0
	{ S5PV210_GPG1(4), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_SDIO_D1
	{ S5PV210_GPG1(5), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_SDIO_D2
	{ S5PV210_GPG1(6), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_WLAN_SDIO_D3

	// GPG2 ---------------------------------------------------
	{ S5PV210_GPG2(0), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_T_FLASH_CLK
	{ S5PV210_GPG2(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_T_FLASH_CMD
	{ S5PV210_GPG2(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_ALS_SDA_28V
	{ S5PV210_GPG2(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_T_FLASH_D0
	{ S5PV210_GPG2(4), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_T_FLASH_D1
	{ S5PV210_GPG2(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_T_FLASH_D2
	{ S5PV210_GPG2(6), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_T_FLASH_D3

	// GPG3 ---------------------------------------------------
	{ S5PV210_GPG3(0), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_UP}, //GPIO_GPS_nRST dig
	{ S5PV210_GPG3(1), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_UP}, //GPIO_GPS_EN : MIDAS[2010.09.04] temporary out0 for sleep
	{ S5PV210_GPG3(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPG3(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP}, //GPIO_TA_CURRENT_SEL_AP
	{ S5PV210_GPG3(4), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_BT_WAKE
	{ S5PV210_GPG3(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_WLAN_WAKE
	{ S5PV210_GPG3(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPG36

	/* Alive part ending and off part start*/
	// GPI ----------------------------------------------------
	{ S5PV210_GPI(0), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_CODEC_I2S_CLK
	{ S5PV210_GPI(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPI1
	{ S5PV210_GPI(2), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_CODEC_I2S_WS
	{ S5PV210_GPI(3), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_CODEC_I3S_DI
	{ S5PV210_GPI(4), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_CODEC_I3S_DO
	{ S5PV210_GPI(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPI5
	{ S5PV210_GPI(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPI6

	// GPJ0 ---------------------------------------------------
	{ S5PV210_GPJ0(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ0(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ0(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ0(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ0(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ0(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPJ0(6), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ0(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},

	// GPJ1 ---------------------------------------------------
	{ S5PV210_GPJ1(0), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_PHONE_ON
	{ S5PV210_GPJ1(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ1(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPJ12
	{ S5PV210_GPJ1(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ1(4), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ1(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},

	// GPJ2 ---------------------------------------------------
	{ S5PV210_GPJ2(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPJ20
	{ S5PV210_GPJ2(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPJ21
	{ S5PV210_GPJ2(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_OLED_DET
	{ S5PV210_GPJ2(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPJ23
	{ S5PV210_GPJ2(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //NC
	{ S5PV210_GPJ2(5), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_SUB_MICBIAS_EN
	{ S5PV210_GPJ2(6), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_EARPATH_SEL
	{ S5PV210_GPJ2(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_MASSMEMORY_EN

	// GPJ3 ---------------------------------------------------
	{ S5PV210_GPJ3(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //_3_TOUCH_SDA_28V
	{ S5PV210_GPJ3(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //_3_TOUCH_SCL_28V
	{ S5PV210_GPJ3(2), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //_3_GPIO_TOUCH_EN
	{ S5PV210_GPJ3(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPJ33
	{ S5PV210_GPJ3(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //GPIO_USB_SDA_28V
	{ S5PV210_GPJ3(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //GPIO_USB_SCL_28V
	{ S5PV210_GPJ3(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //GPIO_AP_SDA_28V
	{ S5PV210_GPJ3(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //GPIO_AP_SCL_28V

	// GPJ4 ---------------------------------------------------
	{ S5PV210_GPJ4(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ4(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_GPJ4(2), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ4(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_GPJ4(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_GPJ44

	/* memory part */
	// MP01 ---------------------------------------------------
	{ S5PV210_MP01(0), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP01(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP01(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP01(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP01(4), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP01(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP01(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP01(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// MP02 ---------------------------------------------------
	{ S5PV210_MP02(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP02(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP02(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP02(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// MP03 ---------------------------------------------------
	{ S5PV210_MP03(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP03(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP03(2), S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, //GPIO_MP032
	{ S5PV210_MP03(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP03(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP03(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP03(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP03(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// MP04 ---------------------------------------------------
	{ S5PV210_MP04(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP04(1), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP04(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP04(3), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP04(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_MP044
	{ S5PV210_MP04(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_MP045
	{ S5PV210_MP04(6), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE},
	{ S5PV210_MP04(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// MP05 ---------------------------------------------------
	{ S5PV210_MP05(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //FUEL_SCL_18V
	{ S5PV210_MP05(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //FUEL_SDA_18V
	{ S5PV210_MP05(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //GPIO_AP_SCL_18V
	{ S5PV210_MP05(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, //GPIO_AP_SDA_18V
	{ S5PV210_MP05(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_MP054
	{ S5PV210_MP05(5), S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, //GPIO_MLCD_RST
	{ S5PV210_MP05(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, //GPIO_MP056
	{ S5PV210_MP05(7), S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, //GPIO_UART_SEL

	// MP06 ---------------------------------------------------
	{ S5PV210_MP06(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP06(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	// MP07 ---------------------------------------------------
	{ S5PV210_MP07(0), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(1), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(2), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(3), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(4), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(5), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(6), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},
	{ S5PV210_MP07(7), S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN},

	/* Memory part ending and off part ending */
};

static unsigned int aries_sleep_alive_gpio_table[][4] =
{
	{S5PV210_GPH0(1), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},
	{S5PV210_GPH0(3), S3C_GPIO_OUTPUT,	S3C_GPIO_SETPIN_ZERO, S3C_GPIO_PULL_NONE},	//GPIO_BUCK_1_EN_A
	{S5PV210_GPH0(4), S3C_GPIO_OUTPUT,	S3C_GPIO_SETPIN_ZERO, S3C_GPIO_PULL_NONE},	//GPIO_BUCK_1_EN_B
	{S5PV210_GPH0(5), S3C_GPIO_OUTPUT,	S3C_GPIO_SETPIN_ZERO, S3C_GPIO_PULL_NONE},	//GPIO_BUCK_2_EN

	{S5PV210_GPH1(0), S3C_GPIO_OUTPUT,	S3C_GPIO_SETPIN_ZERO, S3C_GPIO_PULL_NONE},	  // modi park
	{S5PV210_GPH1(1), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//GPIO_GPH11
	{S5PV210_GPH1(2), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_DOWN},	//GPIO_GPH11
	{S5PV210_GPH1(5), S3C_GPIO_OUTPUT,	S3C_GPIO_SETPIN_ZERO, S3C_GPIO_PULL_NONE},	//GPIO_GPH15
	{S5PV210_GPH1(6), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_DOWN},	//GPIO_GPH16
	{S5PV210_GPH1(7), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},

	{S5PV210_GPH2(0), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_DOWN},	//GPIO_GPH20
	{S5PV210_GPH2(1), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_DOWN},	//GPIO_KBC1
	{S5PV210_GPH2(2), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE},	//GPIO_KBC2
	{S5PV210_GPH2(3), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_DOWN},

	{S5PV210_GPH3(0), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_DOWN},	//GPIO_KBR0
	{S5PV210_GPH3(5), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE, S3C_GPIO_PULL_NONE}, // L4 (REV_05)
	{S5PV210_GPH3(7), S3C_GPIO_INPUT,	S3C_GPIO_SETPIN_NONE,  S3C_GPIO_PULL_DOWN},	// NC
};

void __init aries_gpio_init(void)
{
	u32 i, gpio;

	for (i = 0; i < ARRAY_SIZE(aries_init_gpios); i++) {
		gpio = aries_init_gpios[i].num;
		s3c_gpio_cfgpin(gpio, aries_init_gpios[i].cfg);
		s3c_gpio_setpull(gpio, aries_init_gpios[i].pud);

		if (aries_init_gpios[i].val != S3C_GPIO_SETPIN_NONE)
			gpio_set_value(gpio, aries_init_gpios[i].val);

		s5p_gpio_set_drvstr(gpio, aries_init_gpios[i].drv);
	}

	for (i = 0; i < ARRAY_SIZE(aries_sleep_gpio_table); i++) {
		gpio = aries_sleep_gpio_table[i][0];
		s3c_gpio_slp_cfgpin(gpio, aries_sleep_gpio_table[i][1]);
		s3c_gpio_slp_setpull_updown(gpio, aries_sleep_gpio_table[i][2]);
	}
}

void config_sleep_alive_gpio(void)
{
	u32 i, gpio;

	for (i = 0; i < ARRAY_SIZE(aries_sleep_alive_gpio_table); i++) {
		gpio = aries_sleep_alive_gpio_table[i][0];
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(aries_sleep_alive_gpio_table[i][1]));
		if (aries_sleep_alive_gpio_table[i][2] != S3C_GPIO_SETPIN_NONE)
			gpio_set_value(gpio, aries_sleep_alive_gpio_table[i][2]);
		s3c_gpio_setpull(gpio, aries_sleep_alive_gpio_table[i][3]);
	}

	if (gpio_get_value(GPIO_PS_ON)) {
		s3c_gpio_slp_setpull_updown(GPIO_ALS_SDA_28V, S3C_GPIO_PULL_NONE);
		s3c_gpio_slp_setpull_updown(GPIO_ALS_SCL_28V, S3C_GPIO_PULL_NONE);
	} else {
		s3c_gpio_setpull(GPIO_PS_VOUT, S3C_GPIO_PULL_DOWN);
	}
}
