#include <linux/gfp.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/string.h>

#include <asm-generic/sizes.h>

#include <plat/fb.h>
#include <plat/media.h>

#include <mach/irqs.h>
#include <mach/map.h>
#include <mach/media.h>

#include <../../../drivers/video/samsung/s3cfb.h>

/* G3D */
struct platform_device s3c_device_g3d = {
	.name		= "pvrsrvkm",
	.id		= -1,
};

struct platform_device s3c_device_lcd = {
	.name		= "s3c_lcd",
	.id		= -1,
};

#if defined(CONFIG_S5P_DEV_FB)
static struct resource s3cfb_resource[] = {
	[0] = {
		.start = S5PV210_PA_FB,
		.end   = S5PV210_PA_FB + SZ_1M - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_LCD1,
		.end   = IRQ_LCD1,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_LCD0,
		.end   = IRQ_LCD0,
		.flags = IORESOURCE_IRQ,
	},
};

static u64 fb_dma_mask = 0xffffffffUL;

struct platform_device s3c_device_fb = {
	.name		  = "s3cfb",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s3cfb_resource),
	.resource	  = s3cfb_resource,
	.dev		  = {
		.dma_mask		= &fb_dma_mask,
		.coherent_dma_mask	= 0xffffffffUL
	}
};

static struct s3c_platform_fb default_fb_data __initdata = {
	.hw_ver	= 0x62,
	.nr_wins = 5,
	.default_win = CONFIG_FB_S3C_DEFAULT_WINDOW,
	.swap = FB_SWAP_WORD | FB_SWAP_HWORD,
};

void __init s3cfb_set_platdata(struct s3c_platform_fb *pd)
{
	struct s3c_platform_fb *npd;
	struct s3cfb_lcd *lcd;
	phys_addr_t pmem_start;
	int i, default_win, num_overlay_win;
	int frame_size;

	if (!pd)
		pd = &default_fb_data;

	npd = kmemdup(pd, sizeof(struct s3c_platform_fb), GFP_KERNEL);
	if (!npd)
		printk(KERN_ERR "%s: no memory for platform data\n", __func__);
	else {
		for (i = 0; i < npd->nr_wins; i++)
			npd->nr_buffers[i] = 1;

		default_win = npd->default_win;
		num_overlay_win = CONFIG_FB_S3C_NUM_OVLY_WIN;

		if (num_overlay_win >= default_win) {
			printk(KERN_WARNING "%s: NUM_OVLY_WIN should be less than default \
					window number. set to 0.\n", __func__);
			num_overlay_win = 0;
		}

		for (i = 0; i < num_overlay_win; i++)
			npd->nr_buffers[i] = CONFIG_FB_S3C_NUM_BUF_OVLY_WIN;
		npd->nr_buffers[default_win] = CONFIG_FB_S3C_NR_BUFFERS;

		lcd = (struct s3cfb_lcd *)npd->lcd;
		frame_size = (lcd->width * lcd->height * 4);

		s3cfb_get_clk_name(npd->clk_name);
		npd->backlight_onoff = NULL;
		npd->clk_on = s3cfb_clk_on;
		npd->clk_off = s3cfb_clk_off;

		/* set starting physical address & size of memory region for overlay
		 * window */
		pmem_start = s5p_get_media_memory_bank(S5P_MDEV_FIMD, 1);
		for (i = 0; i < num_overlay_win; i++) {
			npd->pmem_start[i] = pmem_start;
			npd->pmem_size[i] = frame_size * npd->nr_buffers[i];
			pmem_start += npd->pmem_size[i];
		}

		/* set starting physical address & size of memory region for default
		 * window */
		npd->pmem_start[default_win] = pmem_start;
		npd->pmem_size[default_win] = frame_size * npd->nr_buffers[default_win];

		s3c_device_fb.dev.platform_data = npd;
	}
}
#endif
