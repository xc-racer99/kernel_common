/* arch/arm/plat-samsung/include/plat/regs-fb.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      http://armlinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Platform - new-style framebuffer register definitions
 *
 * This is the register set for the new style framebuffer interface
 * found from the S3C2443 onwards into the S3C2416, S3C2450 and the
 * S3C64XX series such as the S3C6400 and S3C6410.
 *
 * The file does not contain the cpu specific items which are based on
 * whichever architecture is selected, it only contains the core of the
 * register set. See <mach/regs-fb.h> to get the specifics.
 *
 * Note, we changed to using regs-fb.h as it avoids any clashes with
 * the original regs-lcd.h so out of the way of regs-lcd.h as well as
 * indicating the newer block is much more than just an LCD interface.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

/* Please do not include this file directly, use <mach/regs-fb.h> to
 * ensure all the localised SoC support is included as necessary.
*/

/* VIDCON0 */

#define VIDCON0					(0x00)
#define VIDCON0_INTERLACE			(1 << 29)
#define VIDCON0_VIDOUT_MASK			(0x3 << 26)
#define VIDCON0_VIDOUT_SHIFT			(26)
#define VIDCON0_VIDOUT_RGB			(0x0 << 26)
#define VIDCON0_VIDOUT_TV			(0x1 << 26)
#define VIDCON0_VIDOUT_I80_LDI0			(0x2 << 26)
#define VIDCON0_VIDOUT_I80_LDI1			(0x3 << 26)

#define VIDCON0_L1_DATA_MASK			(0x7 << 23)
#define VIDCON0_L1_DATA_SHIFT			(23)
#define VIDCON0_L1_DATA_16BPP			(0x0 << 23)
#define VIDCON0_L1_DATA_18BPP16			(0x1 << 23)
#define VIDCON0_L1_DATA_18BPP9			(0x2 << 23)
#define VIDCON0_L1_DATA_24BPP			(0x3 << 23)
#define VIDCON0_L1_DATA_18BPP			(0x4 << 23)
#define VIDCON0_L1_DATA_16BPP8			(0x5 << 23)

#define VIDCON0_L0_DATA_MASK			(0x7 << 20)
#define VIDCON0_L0_DATA_SHIFT			(20)
#define VIDCON0_L0_DATA_16BPP			(0x0 << 20)
#define VIDCON0_L0_DATA_18BPP16			(0x1 << 20)
#define VIDCON0_L0_DATA_18BPP9			(0x2 << 20)
#define VIDCON0_L0_DATA_24BPP			(0x3 << 20)
#define VIDCON0_L0_DATA_18BPP			(0x4 << 20)
#define VIDCON0_L0_DATA_16BPP8			(0x5 << 20)

#define VIDCON0_PNRMODE_MASK			(0x3 << 17)
#define VIDCON0_PNRMODE_SHIFT			(17)
#define VIDCON0_PNRMODE_RGB			(0x0 << 17)
#define VIDCON0_PNRMODE_BGR			(0x1 << 17)
#define VIDCON0_PNRMODE_SERIAL_RGB		(0x2 << 17)
#define VIDCON0_PNRMODE_SERIAL_BGR		(0x3 << 17)

#define VIDCON0_CLKVALUP			(1 << 16)
#define VIDCON0_CLKVAL_F_MASK			(0xff << 6)
#define VIDCON0_CLKVAL_F_SHIFT			(6)
#define VIDCON0_CLKVAL_F_LIMIT			(0xff)
#define VIDCON0_CLKVAL_F(_x)			((_x) << 6)
#define VIDCON0_VLCKFREE			(1 << 5)
#define VIDCON0_CLKDIR				(1 << 4)

#define VIDCON0_CLKSEL_MASK			(0x3 << 2)
#define VIDCON0_CLKSEL_SHIFT			(2)
#define VIDCON0_CLKSEL_HCLK			(0x0 << 2)
#define VIDCON0_CLKSEL_LCD			(0x1 << 2)
#define VIDCON0_CLKSEL_27M			(0x3 << 2)

#define VIDCON0_ENVID				(1 << 1)
#define VIDCON0_ENVID_F				(1 << 0)

#define VIDCON1					(0x04)
#define VIDCON1_LINECNT_MASK			(0x7ff << 16)
#define VIDCON1_LINECNT_SHIFT			(16)
#define VIDCON1_LINECNT_GET(_v)			(((_v) >> 16) & 0x7ff)
#define VIDCON1_VSTATUS_MASK			(0x3 << 13)
#define VIDCON1_VSTATUS_SHIFT			(13)
#define VIDCON1_VSTATUS_VSYNC			(0x0 << 13)
#define VIDCON1_VSTATUS_BACKPORCH		(0x1 << 13)
#define VIDCON1_VSTATUS_ACTIVE			(0x2 << 13)
#define VIDCON1_VSTATUS_FRONTPORCH		(0x0 << 13)
#define VIDCON1_VCLK_MASK			(0x3 << 9)
#define VIDCON1_VCLK_HOLD			(0x0 << 9)
#define VIDCON1_VCLK_RUN			(0x1 << 9)

#define VIDCON1_INV_VCLK			(1 << 7)
#define VIDCON1_INV_HSYNC			(1 << 6)
#define VIDCON1_INV_VSYNC			(1 << 5)
#define VIDCON1_INV_VDEN			(1 << 4)

/* VIDCON2 */

#define VIDCON2					(0x08)
#define VIDCON2_EN601				(1 << 23)
#define VIDCON2_TVFMTSEL_SW			(1 << 14)

#define VIDCON2_TVFMTSEL1_MASK			(0x3 << 12)
#define VIDCON2_TVFMTSEL1_SHIFT			(12)
#define VIDCON2_TVFMTSEL1_RGB			(0x0 << 12)
#define VIDCON2_TVFMTSEL1_YUV422		(0x1 << 12)
#define VIDCON2_TVFMTSEL1_YUV444		(0x2 << 12)

#define VIDCON2_ORGYCbCr			(1 << 8)
#define VIDCON2_YUVORDCrCb			(1 << 7)

/* PRTCON (S3C6410, S5PC100)
 * Might not be present in the S3C6410 documentation,
 * but tests prove it's there almost for sure; shouldn't hurt in any case.
 */
#define PRTCON					(0x0c)
#define PRTCON_PROTECT				(1 << 11)

/* VIDTCON0 */

#define VIDTCON0_VBPDE_MASK			(0xff << 24)
#define VIDTCON0_VBPDE_SHIFT			(24)
#define VIDTCON0_VBPDE_LIMIT			(0xff)
#define VIDTCON0_VBPDE(_x)			((_x) << 24)

#define VIDTCON0_VBPD_MASK			(0xff << 16)
#define VIDTCON0_VBPD_SHIFT			(16)
#define VIDTCON0_VBPD_LIMIT			(0xff)
#define VIDTCON0_VBPD(_x)			((_x) << 16)

#define VIDTCON0_VFPD_MASK			(0xff << 8)
#define VIDTCON0_VFPD_SHIFT			(8)
#define VIDTCON0_VFPD_LIMIT			(0xff)
#define VIDTCON0_VFPD(_x)			((_x) << 8)

#define VIDTCON0_VSPW_MASK			(0xff << 0)
#define VIDTCON0_VSPW_SHIFT			(0)
#define VIDTCON0_VSPW_LIMIT			(0xff)
#define VIDTCON0_VSPW(_x)			((_x) << 0)

/* VIDTCON1 */

#define VIDTCON1_VFPDE_MASK			(0xff << 24)
#define VIDTCON1_VFPDE_SHIFT			(24)
#define VIDTCON1_VFPDE_LIMIT			(0xff)
#define VIDTCON1_VFPDE(_x)			((_x) << 24)

#define VIDTCON1_HBPD_MASK			(0xff << 16)
#define VIDTCON1_HBPD_SHIFT			(16)
#define VIDTCON1_HBPD_LIMIT			(0xff)
#define VIDTCON1_HBPD(_x)			((_x) << 16)

#define VIDTCON1_HFPD_MASK			(0xff << 8)
#define VIDTCON1_HFPD_SHIFT			(8)
#define VIDTCON1_HFPD_LIMIT			(0xff)
#define VIDTCON1_HFPD(_x)			((_x) << 8)

#define VIDTCON1_HSPW_MASK			(0xff << 0)
#define VIDTCON1_HSPW_SHIFT			(0)
#define VIDTCON1_HSPW_LIMIT			(0xff)
#define VIDTCON1_HSPW(_x)			((_x) << 0)

#define VIDTCON2				(0x18)
#define VIDTCON2_LINEVAL_E(_x)			((((_x) & 0x800) >> 11) << 23)
#define VIDTCON2_LINEVAL_MASK			(0x7ff << 11)
#define VIDTCON2_LINEVAL_SHIFT			(11)
#define VIDTCON2_LINEVAL_LIMIT			(0x7ff)
#define VIDTCON2_LINEVAL(_x)			(((_x) & 0x7ff) << 11)

#define VIDTCON2_HOZVAL_E(_x)			((((_x) & 0x800) >> 11) << 22)
#define VIDTCON2_HOZVAL_MASK			(0x7ff << 0)
#define VIDTCON2_HOZVAL_SHIFT			(0)
#define VIDTCON2_HOZVAL_LIMIT			(0x7ff)
#define VIDTCON2_HOZVAL(_x)			(((_x) & 0x7ff) << 0)

/* WINCONx */


#define WINCONx_BITSWP				(1 << 18)
#define WINCONx_BYTSWP				(1 << 17)
#define WINCONx_HAWSWP				(1 << 16)
#define WINCONx_WSWP				(1 << 15)
#define WINCONx_BURSTLEN_MASK			(0x3 << 9)
#define WINCONx_BURSTLEN_SHIFT			(9)
#define WINCONx_BURSTLEN_16WORD			(0x0 << 9)
#define WINCONx_BURSTLEN_8WORD			(0x1 << 9)
#define WINCONx_BURSTLEN_4WORD			(0x2 << 9)

#define WINCONx_ENWIN				(1 << 0)
#define WINCON0_BPPMODE_MASK			(0xf << 2)
#define WINCON0_BPPMODE_SHIFT			(2)
#define WINCON0_BPPMODE_1BPP			(0x0 << 2)
#define WINCON0_BPPMODE_2BPP			(0x1 << 2)
#define WINCON0_BPPMODE_4BPP			(0x2 << 2)
#define WINCON0_BPPMODE_8BPP_PALETTE		(0x3 << 2)
#define WINCON0_BPPMODE_16BPP_565		(0x5 << 2)
#define WINCON0_BPPMODE_16BPP_1555		(0x7 << 2)
#define WINCON0_BPPMODE_18BPP_666		(0x8 << 2)
#define WINCON0_BPPMODE_24BPP_888		(0xb << 2)

#define WINCON1_BLD_PIX				(1 << 6)

#define WINCON1_ALPHA_SEL			(1 << 1)
#define WINCON1_BPPMODE_MASK			(0xf << 2)
#define WINCON1_BPPMODE_SHIFT			(2)
#define WINCON1_BPPMODE_1BPP			(0x0 << 2)
#define WINCON1_BPPMODE_2BPP			(0x1 << 2)
#define WINCON1_BPPMODE_4BPP			(0x2 << 2)
#define WINCON1_BPPMODE_8BPP_PALETTE		(0x3 << 2)
#define WINCON1_BPPMODE_8BPP_1232		(0x4 << 2)
#define WINCON1_BPPMODE_16BPP_565		(0x5 << 2)
#define WINCON1_BPPMODE_16BPP_A1555		(0x6 << 2)
#define WINCON1_BPPMODE_16BPP_I1555		(0x7 << 2)
#define WINCON1_BPPMODE_18BPP_666		(0x8 << 2)
#define WINCON1_BPPMODE_18BPP_A1665		(0x9 << 2)
#define WINCON1_BPPMODE_19BPP_A1666		(0xa << 2)
#define WINCON1_BPPMODE_24BPP_888		(0xb << 2)
#define WINCON1_BPPMODE_24BPP_A1887		(0xc << 2)
#define WINCON1_BPPMODE_25BPP_A1888		(0xd << 2)
#define WINCON1_BPPMODE_28BPP_A4888		(0xd << 2)

/* S5PV210 */
#define SHADOWCON				(0x34)
#define SHADOWCON_WINx_PROTECT(_win)		(1 << (10 + (_win)))
/* DMA channels (all windows) */
#define SHADOWCON_CHx_ENABLE(_win)		(1 << (_win))
/* Local input channels (windows 0-2) */
#define SHADOWCON_CHx_LOCAL_ENABLE(_win)	(1 << (5 + (_win)))

#define VIDOSDxA_TOPLEFT_X_E(_x)		((((_x) & 0x800) >> 11) << 23)
#define VIDOSDxA_TOPLEFT_X_MASK			(0x7ff << 11)
#define VIDOSDxA_TOPLEFT_X_SHIFT		(11)
#define VIDOSDxA_TOPLEFT_X_LIMIT		(0x7ff)
#define VIDOSDxA_TOPLEFT_X(_x)			(((_x) & 0x7ff) << 11)

#define VIDOSDxA_TOPLEFT_Y_E(_x)		((((_x) & 0x800) >> 11) << 22)
#define VIDOSDxA_TOPLEFT_Y_MASK			(0x7ff << 0)
#define VIDOSDxA_TOPLEFT_Y_SHIFT		(0)
#define VIDOSDxA_TOPLEFT_Y_LIMIT		(0x7ff)
#define VIDOSDxA_TOPLEFT_Y(_x)			(((_x) & 0x7ff) << 0)

#define VIDOSDxB_BOTRIGHT_X_E(_x)		((((_x) & 0x800) >> 11) << 23)
#define VIDOSDxB_BOTRIGHT_X_MASK		(0x7ff << 11)
#define VIDOSDxB_BOTRIGHT_X_SHIFT		(11)
#define VIDOSDxB_BOTRIGHT_X_LIMIT		(0x7ff)
#define VIDOSDxB_BOTRIGHT_X(_x)			(((_x) & 0x7ff) << 11)

#define VIDOSDxB_BOTRIGHT_Y_E(_x)		((((_x) & 0x800) >> 11) << 22)
#define VIDOSDxB_BOTRIGHT_Y_MASK		(0x7ff << 0)
#define VIDOSDxB_BOTRIGHT_Y_SHIFT		(0)
#define VIDOSDxB_BOTRIGHT_Y_LIMIT		(0x7ff)
#define VIDOSDxB_BOTRIGHT_Y(_x)			(((_x) & 0x7ff) << 0)

/* For VIDOSD[1..4]C */
#define VIDISD14C_ALPHA0_R(_x)			((_x) << 20)
#define VIDISD14C_ALPHA0_G_MASK			(0xf << 16)
#define VIDISD14C_ALPHA0_G_SHIFT		(16)
#define VIDISD14C_ALPHA0_G_LIMIT		(0xf)
#define VIDISD14C_ALPHA0_G(_x)			((_x) << 16)
#define VIDISD14C_ALPHA0_B_MASK			(0xf << 12)
#define VIDISD14C_ALPHA0_B_SHIFT		(12)
#define VIDISD14C_ALPHA0_B_LIMIT		(0xf)
#define VIDISD14C_ALPHA0_B(_x)			((_x) << 12)
#define VIDISD14C_ALPHA1_R_MASK			(0xf << 8)
#define VIDISD14C_ALPHA1_R_SHIFT		(8)
#define VIDISD14C_ALPHA1_R_LIMIT		(0xf)
#define VIDISD14C_ALPHA1_R(_x)			((_x) << 8)
#define VIDISD14C_ALPHA1_G_MASK			(0xf << 4)
#define VIDISD14C_ALPHA1_G_SHIFT		(4)
#define VIDISD14C_ALPHA1_G_LIMIT		(0xf)
#define VIDISD14C_ALPHA1_G(_x)			((_x) << 4)
#define VIDISD14C_ALPHA1_B_MASK			(0xf << 0)
#define VIDISD14C_ALPHA1_B_SHIFT		(0)
#define VIDISD14C_ALPHA1_B_LIMIT		(0xf)
#define VIDISD14C_ALPHA1_B(_x)			((_x) << 0)

/* Video buffer addresses */
#define VIDW_BUF_START(_buff)			(0xA0 + ((_buff) * 8))
#define VIDW_BUF_START1(_buff)			(0xA4 + ((_buff) * 8))
#define VIDW_BUF_END(_buff)			(0xD0 + ((_buff) * 8))
#define VIDW_BUF_END1(_buff)			(0xD4 + ((_buff) * 8))
#define VIDW_BUF_SIZE(_buff)			(0x100 + ((_buff) * 4))

#define VIDW_BUF_SIZE_OFFSET_E(_x)		((((_x) & 0x2000) >> 13) << 27)
#define VIDW_BUF_SIZE_OFFSET_MASK		(0x1fff << 13)
#define VIDW_BUF_SIZE_OFFSET_SHIFT		(13)
#define VIDW_BUF_SIZE_OFFSET_LIMIT		(0x1fff)
#define VIDW_BUF_SIZE_OFFSET(_x)		(((_x) & 0x1fff) << 13)

#define VIDW_BUF_SIZE_PAGEWIDTH_E(_x)		((((_x) & 0x2000) >> 13) << 26)
#define VIDW_BUF_SIZE_PAGEWIDTH_MASK		(0x1fff << 0)
#define VIDW_BUF_SIZE_PAGEWIDTH_SHIFT		(0)
#define VIDW_BUF_SIZE_PAGEWIDTH_LIMIT		(0x1fff)
#define VIDW_BUF_SIZE_PAGEWIDTH(_x)		(((_x) & 0x1fff) << 0)

/* Interrupt controls and status */

#define VIDINTCON0_FIFOINTERVAL_MASK		(0x3f << 20)
#define VIDINTCON0_FIFOINTERVAL_SHIFT		(20)
#define VIDINTCON0_FIFOINTERVAL_LIMIT		(0x3f)
#define VIDINTCON0_FIFOINTERVAL(_x)		((_x) << 20)

#define VIDINTCON0_INT_SYSMAINCON		(1 << 19)
#define VIDINTCON0_INT_SYSSUBCON		(1 << 18)
#define VIDINTCON0_INT_I80IFDONE		(1 << 17)

#define VIDINTCON0_FRAMESEL0_MASK		(0x3 << 15)
#define VIDINTCON0_FRAMESEL0_SHIFT		(15)
#define VIDINTCON0_FRAMESEL0_BACKPORCH		(0x0 << 15)
#define VIDINTCON0_FRAMESEL0_VSYNC		(0x1 << 15)
#define VIDINTCON0_FRAMESEL0_ACTIVE		(0x2 << 15)
#define VIDINTCON0_FRAMESEL0_FRONTPORCH		(0x3 << 15)

#define VIDINTCON0_FRAMESEL1			(1 << 13)
#define VIDINTCON0_FRAMESEL1_MASK		(0x3 << 13)
#define VIDINTCON0_FRAMESEL1_NONE		(0x0 << 13)
#define VIDINTCON0_FRAMESEL1_BACKPORCH		(0x1 << 13)
#define VIDINTCON0_FRAMESEL1_VSYNC		(0x2 << 13)
#define VIDINTCON0_FRAMESEL1_FRONTPORCH		(0x3 << 13)

#define VIDINTCON0_INT_FRAME			(1 << 12)
#define VIDINTCON0_FIFIOSEL_MASK		(0x7f << 5)
#define VIDINTCON0_FIFIOSEL_SHIFT		(5)
#define VIDINTCON0_FIFIOSEL_WINDOW0		(0x1 << 5)
#define VIDINTCON0_FIFIOSEL_WINDOW1		(0x2 << 5)

#define VIDINTCON0_FIFOLEVEL_MASK		(0x7 << 2)
#define VIDINTCON0_FIFOLEVEL_SHIFT		(2)
#define VIDINTCON0_FIFOLEVEL_TO25PC		(0x0 << 2)
#define VIDINTCON0_FIFOLEVEL_TO50PC		(0x1 << 2)
#define VIDINTCON0_FIFOLEVEL_TO75PC		(0x2 << 2)
#define VIDINTCON0_FIFOLEVEL_EMPTY		(0x3 << 2)
#define VIDINTCON0_FIFOLEVEL_FULL		(0x4 << 2)

#define VIDINTCON0_INT_FIFO_MASK		(0x3 << 0)
#define VIDINTCON0_INT_FIFO_SHIFT		(0)
#define VIDINTCON0_INT_ENABLE			(1 << 0)

#define VIDINTCON1				(0x134)
#define VIDINTCON1_INT_I180			(1 << 2)
#define VIDINTCON1_INT_FRAME			(1 << 1)
#define VIDINTCON1_INT_FIFO			(1 << 0)

/* Window colour-key control registers */
#define WKEYCON					(0x140)	/* 6410,V210 */

#define WKEYCON0				(0x00)
#define WKEYCON1				(0x04)

#define WxKEYCON0_KEYBL_EN			(1 << 26)
#define WxKEYCON0_KEYEN_F			(1 << 25)
#define WxKEYCON0_DIRCON			(1 << 24)
#define WxKEYCON0_COMPKEY_MASK			(0xffffff << 0)
#define WxKEYCON0_COMPKEY_SHIFT			(0)
#define WxKEYCON0_COMPKEY_LIMIT			(0xffffff)
#define WxKEYCON0_COMPKEY(_x)			((_x) << 0)
#define WxKEYCON1_COLVAL_MASK			(0xffffff << 0)
#define WxKEYCON1_COLVAL_SHIFT			(0)
#define WxKEYCON1_COLVAL_LIMIT			(0xffffff)
#define WxKEYCON1_COLVAL(_x)			((_x) << 0)


/* Window blanking (MAP) */

#define WINxMAP_MAP				(1 << 24)
#define WINxMAP_MAP_COLOUR_MASK			(0xffffff << 0)
#define WINxMAP_MAP_COLOUR_SHIFT		(0)
#define WINxMAP_MAP_COLOUR_LIMIT		(0xffffff)
#define WINxMAP_MAP_COLOUR(_x)			((_x) << 0)

#define WPALCON_PAL_UPDATE			(1 << 9)
#define WPALCON_W1PAL_MASK			(0x7 << 3)
#define WPALCON_W1PAL_SHIFT			(3)
#define WPALCON_W1PAL_25BPP_A888		(0x0 << 3)
#define WPALCON_W1PAL_24BPP			(0x1 << 3)
#define WPALCON_W1PAL_19BPP_A666		(0x2 << 3)
#define WPALCON_W1PAL_18BPP_A665		(0x3 << 3)
#define WPALCON_W1PAL_18BPP			(0x4 << 3)
#define WPALCON_W1PAL_16BPP_A555		(0x5 << 3)
#define WPALCON_W1PAL_16BPP_565			(0x6 << 3)

#define WPALCON_W0PAL_MASK			(0x7 << 0)
#define WPALCON_W0PAL_SHIFT			(0)
#define WPALCON_W0PAL_25BPP_A888		(0x0 << 0)
#define WPALCON_W0PAL_24BPP			(0x1 << 0)
#define WPALCON_W0PAL_19BPP_A666		(0x2 << 0)
#define WPALCON_W0PAL_18BPP_A665		(0x3 << 0)
#define WPALCON_W0PAL_18BPP			(0x4 << 0)
#define WPALCON_W0PAL_16BPP_A555		(0x5 << 0)
#define WPALCON_W0PAL_16BPP_565			(0x6 << 0)

/* Blending equation control */
#define BLENDCON				(0x260)
#define BLENDCON_NEW_MASK			(1 << 0)
#define BLENDCON_NEW_8BIT_ALPHA_VALUE		(1 << 0)
#define BLENDCON_NEW_4BIT_ALPHA_VALUE		(0 << 0)

#define S3C_LCDREG(x)		(x)
#define S3C_WINCON(x)		S3C_LCDREG(0x0020 + (x * 0x04))
#define S3C_VIDOSD_A(x)		S3C_LCDREG(0x0040 + (x * 0x10))
#define S3C_VIDOSD_B(x)		S3C_LCDREG(0x0044 + (x * 0x10))
#define S3C_VIDOSD_C(x)		S3C_LCDREG(0x0048 + (x * 0x10))
#define S3C_VIDOSD_D(x)		S3C_LCDREG(0x004C + (x * 0x10))
#define S3C_VIDADDR_START0(x)	S3C_LCDREG(0x00A0 + (x * 0x08))
#define S3C_VIDADDR_START1(x)	S3C_LCDREG(0x00A4 + (x * 0x08))
#define S3C_VIDADDR_END0(x)	S3C_LCDREG(0x00D0 + (x * 0x08))
#define S3C_VIDADDR_END1(x)	S3C_LCDREG(0x00D4 + (x * 0x08))
#define S3C_VIDADDR_SIZE(x)	S3C_LCDREG(0x0100 + (x * 0x04))
#define S3C_KEYCON(x)		S3C_LCDREG(0x0140 + ((x - 1) * 0x08))
#define S3C_KEYVAL(x)		S3C_LCDREG(0x0144 + ((x - 1) * 0x08))
#define S3C_WINMAP(x)		S3C_LCDREG(0x0180 + (x * 0x04))

/*
 * Register Map
*/
#define S3C_VIDCON0		S3C_LCDREG(0x0000)  	/* Video control 0 */
#define S3C_VIDCON1		S3C_LCDREG(0x0004)  	/* Video control 1 */
#define S3C_VIDCON2		S3C_LCDREG(0x0008)  	/* Video control 2 */
#define S3C_PRTCON		S3C_LCDREG(0x000C)  	/* Protect control */

#define S3C_VIDTCON0		S3C_LCDREG(0x0010)  	/* Video time control 0 */
#define S3C_VIDTCON1		S3C_LCDREG(0x0014)  	/* Video time control 1 */
#define S3C_VIDTCON2		S3C_LCDREG(0x0018)  	/* Video time control 2 */

#define S3C_WINCON0		S3C_LCDREG(0x0020)  	/* Window control 0 */
#define S3C_WINCON1		S3C_LCDREG(0x0024)  	/* Window control 1 */
#define S3C_WINCON2		S3C_LCDREG(0x0028)  	/* Window control 2 */
#define S3C_WINCON3		S3C_LCDREG(0x002C)  	/* Window control 3 */
#define S3C_WINCON4		S3C_LCDREG(0x0030)  	/* Window control 4 */

#define S3C_WINSHMAP		S3C_LCDREG(0x0034)  	/* Window Shadow control */

#define S3C_VIDOSD0A		S3C_LCDREG(0x0040)  	/* Video Window 0 position control */
#define S3C_VIDOSD0B		S3C_LCDREG(0x0044)  	/* Video Window 0 position control1 */
#define S3C_VIDOSD0C		S3C_LCDREG(0x0048)  	/* Video Window 0 position control */

#define S3C_VIDOSD1A		S3C_LCDREG(0x0050)  	/* Video Window 1 position control */
#define S3C_VIDOSD1B		S3C_LCDREG(0x0054)  	/* Video Window 1 position control */
#define S3C_VIDOSD1C		S3C_LCDREG(0x0058)  	/* Video Window 1 position control */
#define S3C_VIDOSD1D		S3C_LCDREG(0x005C)  	/* Video Window 1 position control */

#define S3C_VIDOSD2A		S3C_LCDREG(0x0060)  	/* Video Window 2 position control */
#define S3C_VIDOSD2B		S3C_LCDREG(0x0064)  	/* Video Window 2 position control */
#define S3C_VIDOSD2C		S3C_LCDREG(0x0068)  	/* Video Window 2 position control */
#define S3C_VIDOSD2D		S3C_LCDREG(0x006C)  	/* Video Window 2 position control */

#define S3C_VIDOSD3A		S3C_LCDREG(0x0070)  	/* Video Window 3 position control */
#define S3C_VIDOSD3B		S3C_LCDREG(0x0074)  	/* Video Window 3 position control */
#define S3C_VIDOSD3C		S3C_LCDREG(0x0078)  	/* Video Window 3 position control */

#define S3C_VIDOSD4A		S3C_LCDREG(0x0080)  	/* Video Window 4 position control */
#define S3C_VIDOSD4B		S3C_LCDREG(0x0084)  	/* Video Window 4 position control */
#define S3C_VIDOSD4C		S3C_LCDREG(0x0088)  	/* Video Window 4 position control */

#define S3C_VIDW00ADD0B0	S3C_LCDREG(0x00A0) 	/* Window 0 buffer start address, buffer 0 */
#define S3C_VIDW00ADD0B1	S3C_LCDREG(0x00A4) 	/* Window 0 buffer start address, buffer 1 */
#define S3C_VIDW01ADD0B0	S3C_LCDREG(0x00A8) 	/* Window 1 buffer start address, buffer 0 */
#define S3C_VIDW01ADD0B1	S3C_LCDREG(0x00AC) 	/* Window 1 buffer start address, buffer 1 */
#define S3C_VIDW02ADD0		S3C_LCDREG(0x00B0) 	/* Window 2 buffer start address, buffer 0 */
#define S3C_VIDW03ADD0		S3C_LCDREG(0x00B8) 	/* Window 3 buffer start address, buffer 0 */
#define S3C_VIDW04ADD0		S3C_LCDREG(0x00C0) 	/* Window 4 buffer start address, buffer 0 */
#define S3C_VIDW00ADD1B0	S3C_LCDREG(0x00D0) 	/* Window 0 buffer end address, buffer 0 */
#define S3C_VIDW00ADD1B1	S3C_LCDREG(0x00D4) 	/* Window 0 buffer end address, buffer 1 */
#define S3C_VIDW01ADD1B0	S3C_LCDREG(0x00D8) 	/* Window 1 buffer end address, buffer 0 */
#define S3C_VIDW01ADD1B1	S3C_LCDREG(0x00DC) 	/* Window 1 buffer end address, buffer 1 */
#define S3C_VIDW02ADD1		S3C_LCDREG(0x00E0) 	/* Window 2 buffer end address */
#define S3C_VIDW03ADD1		S3C_LCDREG(0x00E8) 	/* Window 3 buffer end address */
#define S3C_VIDW04ADD1		S3C_LCDREG(0x00F0) 	/* Window 4 buffer end address */
#define S3C_VIDW00ADD2		S3C_LCDREG(0x0100) 	/* Window 0 buffer size */
#define S3C_VIDW01ADD2		S3C_LCDREG(0x0104) 	/* Window 1 buffer size */
#define S3C_VIDW02ADD2		S3C_LCDREG(0x0108) 	/* Window 2 buffer size */
#define S3C_VIDW03ADD2		S3C_LCDREG(0x010C) 	/* Window 3 buffer size */
#define S3C_VIDW04ADD2		S3C_LCDREG(0x0110) 	/* Window 4 buffer size */

#define S3C_VP1TCON0		S3C_LCDREG(0x0118)	/* VP1 interface timing control 0 */
#define S3C_VP1TCON1		S3C_LCDREG(0x011C)	/* VP1 interface timing control 1 */

#define S3C_VIDINTCON0		S3C_LCDREG(0x0130)	/* Indicate the Video interrupt control */
#define S3C_VIDINTCON1		S3C_LCDREG(0x0134) 	/* Video Interrupt Pending */

#define S3C_W1KEYCON0		S3C_LCDREG(0x0140) 	/* Color key control */
#define S3C_W1KEYCON1		S3C_LCDREG(0x0144) 	/* Color key value (transparent value) */
#define S3C_W2KEYCON0		S3C_LCDREG(0x0148) 	/* Color key control */
#define S3C_W2KEYCON1		S3C_LCDREG(0x014C) 	/* Color key value (transparent value) */
#define S3C_W3KEYCON0		S3C_LCDREG(0x0150)	/* Color key control */
#define S3C_W3KEYCON1		S3C_LCDREG(0x0154)	/* Color key value (transparent value) */
#define S3C_W4KEYCON0		S3C_LCDREG(0x0158)	/* Color key control */
#define S3C_W4KEYCON1		S3C_LCDREG(0x015C)	/* Color key value (transparent value) */

#define S3C_W1KEYALPHA		S3C_LCDREG(0x0160)	/* Color key alpha value */
#define S3C_W2KEYALPHA		S3C_LCDREG(0x0164)	/* Color key alpha value */
#define S3C_W3KEYALPHA		S3C_LCDREG(0x0168)	/* Color key alpha value */
#define S3C_W4KEYALPHA		S3C_LCDREG(0x016C)	/* Color key alpha value */

#define S3C_DITHMODE		S3C_LCDREG(0x0170)	/* Dithering mode */

#define S3C_WIN0MAP		S3C_LCDREG(0x0180)	/* Window color control	*/
#define S3C_WIN1MAP		S3C_LCDREG(0x0184)	/* Window color control	*/
#define S3C_WIN2MAP		S3C_LCDREG(0x0188)	/* Window color control	*/
#define S3C_WIN3MAP		S3C_LCDREG(0x018C)	/* Window color control	*/
#define S3C_WIN4MAP		S3C_LCDREG(0x0190)	/* Window color control	*/

#define S3C_WPALCON_H		S3C_LCDREG(0x019C)	/* Window Palette control */
#define S3C_WPALCON_L		S3C_LCDREG(0x01A0)	/* Window Palette control */

#define S3C_VIDW0ALPHA0		S3C_LCDREG(0x0200)	/* Window 0 alpha value 0 */
#define S3C_VIDW0ALPHA1		S3C_LCDREG(0x0204)	/* Window 0 alpha value 1 */
#define S3C_VIDW1ALPHA0		S3C_LCDREG(0x0208)	/* Window 1 alpha value 0 */
#define S3C_VIDW1ALPHA1		S3C_LCDREG(0x020C)	/* Window 1 alpha value 1 */
#define S3C_VIDW2ALPHA0		S3C_LCDREG(0x0210)	/* Window 2 alpha value 0 */
#define S3C_VIDW2ALPHA1		S3C_LCDREG(0x0214)	/* Window 2 alpha value 1 */
#define S3C_VIDW3ALPHA0		S3C_LCDREG(0x0218)	/* Window 3 alpha value 0 */
#define S3C_VIDW3ALPHA1		S3C_LCDREG(0x021C)	/* Window 3 alpha value 1 */
#define S3C_VIDW4ALPHA0		S3C_LCDREG(0x0220)	/* Window 4 alpha value 0 */
#define S3C_VIDW4ALPHA1		S3C_LCDREG(0x0224)	/* Window 4 alpha value 1 */

#define S3C_BLENDEQ1		S3C_LCDREG(0x0244)	/* Window 1 blending equation control */
#define S3C_BLENDEQ2		S3C_LCDREG(0x0248)	/* Window 2 blending equation control */
#define S3C_BLENDEQ3		S3C_LCDREG(0x024C)	/* Window 3 blending equation control */
#define S3C_BLENDEQ4		S3C_LCDREG(0x0250)	/* Window 4 blending equation control */
#define S3C_BLENDCON		S3C_LCDREG(0x0260)	/* Blending control */

/*
 * Bit Definitions
*/

/* VIDCON0 */
#define S3C_VIDCON0_DSI_DISABLE			(0 << 30)
#define S3C_VIDCON0_DSI_ENABLE			(1 << 30)
#define S3C_VIDCON0_SCAN_PROGRESSIVE		(0 << 29)
#define S3C_VIDCON0_SCAN_INTERLACE		(1 << 29)
#define S3C_VIDCON0_SCAN_MASK			(1 << 29)
#define S3C_VIDCON0_VIDOUT_RGB			(0 << 26)
#define S3C_VIDCON0_VIDOUT_ITU			(1 << 26)
#define S3C_VIDCON0_VIDOUT_I80LDI0		(2 << 26)
#define S3C_VIDCON0_VIDOUT_I80LDI1		(3 << 26)
#define S3C_VIDCON0_VIDOUT_WB_RGB		(4 << 26)
#define S3C_VIDCON0_VIDOUT_WB_I80LDI0		(6 << 26)
#define S3C_VIDCON0_VIDOUT_WB_I80LDI1		(7 << 26)
#define S3C_VIDCON0_VIDOUT_MASK			(7 << 26)
#define S3C_VIDCON0_PNRMODE_RGB_P		(0 << 17)
#define S3C_VIDCON0_PNRMODE_BGR_P		(1 << 17)
#define S3C_VIDCON0_PNRMODE_RGB_S		(2 << 17)
#define S3C_VIDCON0_PNRMODE_BGR_S		(3 << 17)
#define S3C_VIDCON0_PNRMODE_MASK		(3 << 17)
#define S3C_VIDCON0_PNRMODE_SHIFT		(17)
#define S3C_VIDCON0_CLKVALUP_ALWAYS 		(0 << 16)
#define S3C_VIDCON0_CLKVALUP_START_FRAME 	(1 << 16)
#define S3C_VIDCON0_CLKVALUP_MASK 		(1 << 16)
#define S3C_VIDCON0_CLKVAL_F(x)			(((x) & 0xff) << 6)
#define S3C_VIDCON0_VCLKEN_NORMAL		(0 << 5)
#define S3C_VIDCON0_VCLKEN_FREERUN		(1 << 5)
#define S3C_VIDCON0_VCLKEN_MASK			(1 << 5)
#define S3C_VIDCON0_CLKDIR_DIRECTED  		(0 << 4)
#define S3C_VIDCON0_CLKDIR_DIVIDED   		(1 << 4)
#define S3C_VIDCON0_CLKDIR_MASK			(1 << 4)
#define S3C_VIDCON0_CLKSEL_HCLK	  		(0 << 2)
#define S3C_VIDCON0_CLKSEL_SCLK	  		(1 << 2)
#define S3C_VIDCON0_CLKSEL_MASK	  		(1 << 2)
#define S3C_VIDCON0_ENVID_ENABLE	    	(1 << 1)
#define S3C_VIDCON0_ENVID_DISABLE	    	(0 << 1)
#define S3C_VIDCON0_ENVID_F_ENABLE     		(1 << 0)
#define S3C_VIDCON0_ENVID_F_DISABLE     	(0 << 0)

/* VIDCON1 */
#define S3C_VIDCON1_IVCLK_FALLING_EDGE 		(0 << 7)
#define S3C_VIDCON1_IVCLK_RISING_EDGE 		(1 << 7)
#define S3C_VIDCON1_IHSYNC_NORMAL		(0 << 6)
#define S3C_VIDCON1_IHSYNC_INVERT		(1 << 6)
#define S3C_VIDCON1_IVSYNC_NORMAL		(0 << 5)
#define S3C_VIDCON1_IVSYNC_INVERT		(1 << 5)
#define S3C_VIDCON1_IVDEN_NORMAL		(0 << 4)
#define S3C_VIDCON1_IVDEN_INVERT		(1 << 4)

/* VIDCON2 */
#define S3C_VIDCON2_EN601_DISABLE		(0 << 23)
#define S3C_VIDCON2_EN601_ENABLE		(1 << 23)
#define S3C_VIDCON2_EN601_MASK			(1 << 23)
#define S3C_VIDCON2_WB_DISABLE			(0 << 15)
#define S3C_VIDCON2_WB_ENABLE			(1 << 15)
#define S3C_VIDCON2_WB_MASK			(1 << 15)
#define S3C_VIDCON2_TVFORMATSEL_HW		(0 << 14)
#define S3C_VIDCON2_TVFORMATSEL_SW		(1 << 14)
#define S3C_VIDCON2_TVFORMATSEL_MASK		(1 << 14)
#define S3C_VIDCON2_TVFORMATSEL_YUV422		(1 << 12)
#define S3C_VIDCON2_TVFORMATSEL_YUV444		(2 << 12)
#define S3C_VIDCON2_TVFORMATSEL_YUV_MASK	(3 << 12)
#define S3C_VIDCON2_ORGYUV_YCBCR		(0 << 8)
#define S3C_VIDCON2_ORGYUV_CBCRY		(1 << 8)
#define S3C_VIDCON2_ORGYUV_MASK			(1 << 8)
#define S3C_VIDCON2_YUVORD_CBCR			(0 << 7)
#define S3C_VIDCON2_YUVORD_CRCB			(1 << 7)
#define S3C_VIDCON2_YUVORD_MASK			(1 << 7)

/* PRTCON */
#define S3C_PRTCON_UPDATABLE			(0 << 11)
#define S3C_PRTCON_PROTECT			(1 << 11)

/* VIDTCON0 */
#define S3C_VIDTCON0_VBPDE(x)			(((x) & 0xff) << 24)
#define S3C_VIDTCON0_VBPD(x)			(((x) & 0xff) << 16)
#define S3C_VIDTCON0_VFPD(x) 			(((x) & 0xff) << 8)
#define S3C_VIDTCON0_VSPW(x) 			(((x) & 0xff) << 0)

/* VIDTCON1 */
#define S3C_VIDTCON1_VFPDE(x)			(((x) & 0xff) << 24)
#define S3C_VIDTCON1_HBPD(x) 			(((x) & 0xff) << 16)
#define S3C_VIDTCON1_HFPD(x) 			(((x) & 0xff) << 8)
#define S3C_VIDTCON1_HSPW(x) 			(((x) & 0xff) << 0)

/* VIDTCON2 */
#define S3C_VIDTCON2_LINEVAL(x)  		(((x) & 0x7ff) << 11)
#define S3C_VIDTCON2_HOZVAL(x)   		(((x) & 0x7ff) << 0)

/* Window 0~4 Control - WINCONx */
#define S3C_WINCON_DATAPATH_DMA			(0 << 22)
#define S3C_WINCON_DATAPATH_LOCAL		(1 << 22)
#define S3C_WINCON_DATAPATH_MASK		(1 << 22)
#define S3C_WINCON_BUFSEL_0			(0 << 20)
#define S3C_WINCON_BUFSEL_1			(1 << 20)
#define S3C_WINCON_BUFSEL_MASK			(1 << 20)
#define S3C_WINCON_BUFSEL_SHIFT			(20)
#define S3C_WINCON_BUFAUTO_DISABLE		(0 << 19)
#define S3C_WINCON_BUFAUTO_ENABLE		(1 << 19)
#define S3C_WINCON_BUFAUTO_MASK			(1 << 19)
#define S3C_WINCON_BITSWP_DISABLE		(0 << 18)
#define S3C_WINCON_BITSWP_ENABLE		(1 << 18)
#define S3C_WINCON_BITSWP_SHIFT			(18)
#define S3C_WINCON_BYTESWP_DISABLE		(0 << 17)
#define S3C_WINCON_BYTESWP_ENABLE		(1 << 17)
#define S3C_WINCON_BYTESWP_SHIFT		(17)
#define S3C_WINCON_HAWSWP_DISABLE		(0 << 16)
#define S3C_WINCON_HAWSWP_ENABLE		(1 << 16)
#define S3C_WINCON_HAWSWP_SHIFT			(16)
#define S3C_WINCON_WSWP_DISABLE			(0 << 15)
#define S3C_WINCON_WSWP_ENABLE			(1 << 15)
#define S3C_WINCON_WSWP_SHIFT			(15)
#define S3C_WINCON_INRGB_RGB	   		(0 << 13)
#define S3C_WINCON_INRGB_YUV	 		(1 << 13)
#define S3C_WINCON_INRGB_MASK			(1 << 13)
#define S3C_WINCON_BURSTLEN_16WORD		(0 << 9)
#define S3C_WINCON_BURSTLEN_8WORD		(1 << 9)
#define S3C_WINCON_BURSTLEN_4WORD		(2 << 9)
#define S3C_WINCON_BURSTLEN_MASK		(3 << 9)
#define S3C_WINCON_ALPHA_MULTI_DISABLE		(0 << 7)
#define S3C_WINCON_ALPHA_MULTI_ENABLE		(1 << 7)
#define S3C_WINCON_BLD_PLANE			(0 << 6)
#define S3C_WINCON_BLD_PIXEL			(1 << 6)
#define S3C_WINCON_BLD_MASK			(1 << 6)
#define S3C_WINCON_BPPMODE_1BPP			(0 << 2)
#define S3C_WINCON_BPPMODE_2BPP			(1 << 2)
#define S3C_WINCON_BPPMODE_4BPP			(2 << 2)
#define S3C_WINCON_BPPMODE_8BPP_PAL		(3 << 2)
#define S3C_WINCON_BPPMODE_8BPP			(4 << 2)
#define S3C_WINCON_BPPMODE_16BPP_565		(5 << 2)
#define S3C_WINCON_BPPMODE_16BPP_A555		(6 << 2)
#define S3C_WINCON_BPPMODE_18BPP_666		(8 << 2)
#define S3C_WINCON_BPPMODE_18BPP_A665		(9 << 2)
#define S3C_WINCON_BPPMODE_24BPP_888		(0xb << 2)
#define S3C_WINCON_BPPMODE_24BPP_A887		(0xc << 2)
#define S3C_WINCON_BPPMODE_32BPP		(0xd << 2)
#define S3C_WINCON_BPPMODE_16BPP_A444		(0xe << 2)
#define S3C_WINCON_BPPMODE_15BPP_555		(0xf << 2)
#define S3C_WINCON_BPPMODE_MASK			(0xf << 2)
#define S3C_WINCON_BPPMODE_SHIFT		(2)
#define S3C_WINCON_ALPHA0_SEL			(0 << 1)
#define S3C_WINCON_ALPHA1_SEL			(1 << 1)
#define S3C_WINCON_ALPHA_SEL_MASK		(1 << 1)
#define S3C_WINCON_ENWIN_DISABLE 		(0 << 0)
#define S3C_WINCON_ENWIN_ENABLE			(1 << 0)

/* WINCON1 special */
#define S3C_WINCON1_VP_DISABLE			(0 << 24)
#define S3C_WINCON1_VP_ENABLE			(1 << 24)
#define S3C_WINCON1_LOCALSEL_FIMC1		(0 << 23)
#define S3C_WINCON1_LOCALSEL_VP			(1 << 23)
#define S3C_WINCON1_LOCALSEL_MASK		(1 << 23)

/* WINSHMAP */
#define S3C_WINSHMAP_PROTECT(x)			(((x) & 0x1f) << 10)
#define S3C_WINSHMAP_CH_ENABLE(x)		(1 << (x))
#define S3C_WINSHMAP_CH_DISABLE(x)		(1 << (x))
#define S3C_WINSHMAP_LOCAL_ENABLE(x)		(0x20 << (x))
#define S3C_WINSHMAP_LOCAL_DISABLE(x)		(0x20 << (x))


/* VIDOSDxA, VIDOSDxB */
#define S3C_VIDOSD_LEFT_X(x)			(((x) & 0x7ff) << 11)
#define S3C_VIDOSD_TOP_Y(x)			(((x) & 0x7ff) << 0)
#define S3C_VIDOSD_RIGHT_X(x)			(((x) & 0x7ff) << 11)
#define S3C_VIDOSD_BOTTOM_Y(x)			(((x) & 0x7ff) << 0)

/* VIDOSD0C, VIDOSDxD */
#define S3C_VIDOSD_SIZE(x)			(((x) & 0xffffff) << 0)

/* VIDOSDxC (1~4) */
#define S3C_VIDOSD_ALPHA0_R(x)			(((x) & 0xf) << 20)
#define S3C_VIDOSD_ALPHA0_G(x)			(((x) & 0xf) << 16)
#define S3C_VIDOSD_ALPHA0_B(x)			(((x) & 0xf) << 12)
#define S3C_VIDOSD_ALPHA1_R(x)			(((x) & 0xf) << 8)
#define S3C_VIDOSD_ALPHA1_G(x)			(((x) & 0xf) << 4)
#define S3C_VIDOSD_ALPHA1_B(x)			(((x) & 0xf) << 0)
#define S3C_VIDOSD_ALPHA0_SHIFT			(12)
#define S3C_VIDOSD_ALPHA1_SHIFT			(0)

/* Start Address */
#define S3C_VIDADDR_START_VBANK(x) 		(((x) & 0xff) << 24)
#define S3C_VIDADDR_START_VBASEU(x)		(((x) & 0xffffff) << 0)

/* End Address */
#define S3C_VIDADDR_END_VBASEL(x) 		(((x) & 0xffffff) << 0)

/* Buffer Size */
#define S3C_VIDADDR_OFFSIZE(x)  		(((x) & 0x1fff) << 13)
#define S3C_VIDADDR_PAGEWIDTH(x)		(((x) & 0x1fff) << 0)

/* WIN Color Map */
#define S3C_WINMAP_COLOR(x)			((x) & 0xffffff)

/* VIDINTCON0 */
#define S3C_VIDINTCON0_SYSMAINCON_DISABLE	(0 << 19)
#define S3C_VIDINTCON0_SYSMAINCON_ENABLE	(1 << 19)
#define S3C_VIDINTCON0_SYSSUBCON_DISABLE	(0 << 18)
#define S3C_VIDINTCON0_SYSSUBCON_ENABLE		(1 << 18)
#define S3C_VIDINTCON0_SYSIFDONE_DISABLE	(0 << 17)
#define S3C_VIDINTCON0_SYSIFDONE_ENABLE		(1 << 17)
#define S3C_VIDINTCON0_FRAMESEL0_BACK		(0 << 15)
#define S3C_VIDINTCON0_FRAMESEL0_VSYNC 		(1 << 15)
#define S3C_VIDINTCON0_FRAMESEL0_ACTIVE		(2 << 15)
#define S3C_VIDINTCON0_FRAMESEL0_FRONT 		(3 << 15)
#define S3C_VIDINTCON0_FRAMESEL0_MASK 		(3 << 15)
#define S3C_VIDINTCON0_FRAMESEL1_NONE		(0 << 13)
#define S3C_VIDINTCON0_FRAMESEL1_BACK		(1 << 13)
#define S3C_VIDINTCON0_FRAMESEL1_VSYNC 		(2 << 13)
#define S3C_VIDINTCON0_FRAMESEL1_FRONT 		(3 << 13)
#define S3C_VIDINTCON0_INTFRMEN_DISABLE		(0 << 12)
#define S3C_VIDINTCON0_INTFRMEN_ENABLE 		(1 << 12)
#define S3C_VIDINTCON0_FIFOSEL_WIN4		(1 << 11)
#define S3C_VIDINTCON0_FIFOSEL_WIN3		(1 << 10)
#define S3C_VIDINTCON0_FIFOSEL_WIN2		(1 << 9)
#define S3C_VIDINTCON0_FIFOSEL_WIN1		(1 << 6)
#define S3C_VIDINTCON0_FIFOSEL_WIN0		(1 << 5)
#define S3C_VIDINTCON0_FIFOSEL_ALL		(0x73 << 5)
#define S3C_VIDINTCON0_FIFOSEL_MASK		(0x73 << 5)
#define S3C_VIDINTCON0_FIFOLEVEL_25		(0 << 2)
#define S3C_VIDINTCON0_FIFOLEVEL_50		(1 << 2)
#define S3C_VIDINTCON0_FIFOLEVEL_75		(2 << 2)
#define S3C_VIDINTCON0_FIFOLEVEL_EMPTY 		(3 << 2)
#define S3C_VIDINTCON0_FIFOLEVEL_FULL		(4 << 2)
#define S3C_VIDINTCON0_FIFOLEVEL_MASK		(7 << 2)
#define S3C_VIDINTCON0_INTFIFO_DISABLE		(0 << 1)
#define S3C_VIDINTCON0_INTFIFO_ENABLE		(1 << 1)
#define S3C_VIDINTCON0_INT_DISABLE		(0 << 0)
#define S3C_VIDINTCON0_INT_ENABLE		(1 << 0)
#define S3C_VIDINTCON0_INT_MASK			(1 << 0)

/* VIDINTCON1 */
#define S3C_VIDINTCON1_INTVPPEND		(1 << 5)
#define S3C_VIDINTCON1_INTI80PEND		(1 << 2)
#define S3C_VIDINTCON1_INTFRMPEND		(1 << 1)
#define S3C_VIDINTCON1_INTFIFOPEND		(1 << 0)

/* WINMAP */
#define S3C_WINMAP_ENABLE			(1 << 24)

/* WxKEYCON0 (1~4) */
#define S3C_KEYCON0_KEYBLEN_DISABLE 		(0 << 26)
#define S3C_KEYCON0_KEYBLEN_ENABLE		(1 << 26)
#define S3C_KEYCON0_KEY_DISABLE 		(0 << 25)
#define S3C_KEYCON0_KEY_ENABLE			(1 << 25)
#define S3C_KEYCON0_DIRCON_MATCH_FG		(0 << 24)
#define S3C_KEYCON0_DIRCON_MATCH_BG		(1 << 24)
#define S3C_KEYCON0_COMPKEY(x)			(((x) & 0xffffff) << 0)

/* WxKEYCON1 (1~4) */
#define S3C_KEYCON1_COLVAL(x)			(((x) & 0xffffff) << 0)
