#include <linux/gpio_event.h>
#include <linux/platform_device.h>

#include <mach/gpio.h>

#include <mach/aries.h>

static struct gpio_event_direct_entry aries_keypad_key_map[] = {
	{
		.gpio	= S5PV210_GPH2(6),
		.code	= KEY_POWER,
	}, {
		.gpio	= S5PV210_GPH3(2),
		.code	= KEY_VOLUMEDOWN,
	}, {
		.gpio	= S5PV210_GPH3(1),
		.code	= KEY_VOLUMEUP,
	}
};

static struct gpio_event_input_info aries_keypad_key_info = {
	.info.func = gpio_event_input_func,
	.info.no_suspend = true,
	.debounce_time.tv64 = 5 * NSEC_PER_MSEC,
	.type = EV_KEY,
	.keymap = aries_keypad_key_map,
	.keymap_size = ARRAY_SIZE(aries_keypad_key_map)
};

static struct gpio_event_info *aries_input_info[] = {
	&aries_keypad_key_info.info,
};


static struct gpio_event_platform_data aries_input_data = {
	.names = {
		"aries-keypad",
		NULL,
	},
	.info = aries_input_info,
	.info_count = ARRAY_SIZE(aries_input_info),
};

static struct platform_device aries_input_device = {
	.name = GPIO_EVENT_DEV_NAME,
	.id = 0,
	.dev = {
		.platform_data = &aries_input_data,
	},
};

static struct platform_device *aries_devices[] __initdata = {
	&aries_input_device,
};

void __init aries_input_init(void)
{
	/* register devices */
	platform_add_devices(aries_devices, ARRAY_SIZE(aries_devices));
}
