/*
 * max8998_charger.c - Power supply consumer driver for the Maxim 8998/LP3974
 *
 *  Copyright (C) 2009-2010 Samsung Electronics
 *  MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/err.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/mfd/max8998.h>
#include <linux/mfd/max8998-private.h>

struct max8998_battery_data {
	struct device *dev;
	struct max8998_dev *iodev;
	struct power_supply psy_ac;
	struct power_supply psy_usb;
	enum cable_type_t cable_status;
	struct max8998_charger_callbacks callbacks;
};

static enum power_supply_property max8998_battery_props[] = {
	POWER_SUPPLY_PROP_STATUS, /* Full or not full only */
	POWER_SUPPLY_PROP_PRESENT, /* the presence of the power supply */
	POWER_SUPPLY_PROP_ONLINE, /* charger is active or not */
};

static void max8998_set_cable(struct max8998_charger_callbacks *ptr,
	enum cable_type_t status)
{
	int ret;
	struct i2c_client *i2c;

	struct max8998_battery_data *max8998 = container_of(ptr, struct max8998_battery_data, callbacks);

	i2c = max8998->iodev->i2c;
	max8998->cable_status = status;

	if (status == CABLE_TYPE_NONE) {
		/* disable charging */
		ret = max8998_update_reg(i2c, MAX8998_REG_CHGR2,
			(1 << MAX8998_SHIFT_CHGEN), MAX8998_MASK_CHGEN);
		if (ret < 0)
			goto err;
	} else {
		if (status == CABLE_TYPE_USB) {
			/* usb charging - set eoc */
			ret = max8998_write_reg(i2c, MAX8998_REG_CHGR1,
						(6 << MAX8998_SHIFT_TOPOFF) |
						(3 << MAX8998_SHIFT_RSTR) |
						(2 << MAX8998_SHIFT_ICHG));
			if (ret < 0)
				goto err;
		} else {
			/* ac charging - set eoc */
			ret = max8998_write_reg(i2c, MAX8998_REG_CHGR1,
						(2 << MAX8998_SHIFT_TOPOFF) |
						(3 << MAX8998_SHIFT_RSTR) |
						(5 << MAX8998_SHIFT_ICHG));
			if (ret < 0)
				goto err;
		}

		/* enable charging */
		ret = max8998_write_reg(i2c, MAX8998_REG_CHGR2,
					(2 << MAX8998_SHIFT_ESAFEOUT) |
					(2 << MAX8998_SHIFT_FT) |
					(0 << MAX8998_SHIFT_CHGEN));
		if (ret < 0)
			goto err;
}

	power_supply_changed(&max8998->psy_ac);
	power_supply_changed(&max8998->psy_usb);
	return;

err:
	pr_err("max8998_read_reg error\n");
}

static int max8998_battery_get_property(struct power_supply *psy,
		enum power_supply_property psp,
		union power_supply_propval *val)
{
	struct max8998_battery_data *max8998;
	struct i2c_client *i2c;
	int ret;
	u8 reg;
	enum cable_type_t cable_status;

	if (psy->type == POWER_SUPPLY_TYPE_MAINS) {
		max8998 = container_of(psy, struct max8998_battery_data, psy_ac);
	} else {
		max8998 = container_of(psy, struct max8998_battery_data, psy_usb);
	}

	i2c = max8998->iodev->i2c;
	cable_status = max8998->cable_status;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = max8998_read_reg(i2c, MAX8998_REG_IRQ1, &reg);
		if (ret < 0)
			return ret;

		ret = max8998_read_reg(i2c, MAX8998_REG_IRQ3, &reg);
		if (ret < 0)
			return ret;

		val->intval = (reg & 0x4) || (ret != 0);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		if (psy->type == POWER_SUPPLY_TYPE_MAINS && cable_status == CABLE_TYPE_AC) {
			val->intval = 1;
		} else if (psy->type == POWER_SUPPLY_TYPE_USB && cable_status == CABLE_TYPE_USB) {
			val->intval = 1;
		} else {
			val->intval = 0;
		}
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		/* Check if we're present */
		if ((psy->type == POWER_SUPPLY_TYPE_MAINS && cable_status == CABLE_TYPE_AC)
					|| (psy->type == POWER_SUPPLY_TYPE_USB && cable_status == CABLE_TYPE_USB)) {
			/* Check charging status */
			ret = max8998_read_reg(i2c, MAX8998_REG_STATUS2, &reg);
			if (ret)
				return ret;

			val->intval = reg & MAX8998_MASK_VDCIN;
		} else {
			val->intval = 0;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static __devinit int max8998_battery_probe(struct platform_device *pdev)
{
	struct max8998_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct max8998_platform_data *pdata = dev_get_platdata(iodev->dev);
	struct max8998_battery_data *max8998;
	struct i2c_client *i2c;
	int ret = 0;

	if (!pdata) {
		dev_err(pdev->dev.parent, "No platform init data supplied\n");
		return -ENODEV;
	}

	max8998 = kzalloc(sizeof(struct max8998_battery_data), GFP_KERNEL);
	if (!max8998)
		return -ENOMEM;

	max8998->dev = &pdev->dev;
	max8998->iodev = iodev;
	platform_set_drvdata(pdev, max8998);
	i2c = max8998->iodev->i2c;

	/* Setup "End of Charge" */
	/* If EOC value equals 0,
	 * remain value set from bootloader or default value */
	if (pdata->eoc >= 10 && pdata->eoc <= 45) {
		max8998_update_reg(i2c, MAX8998_REG_CHGR1,
				(pdata->eoc / 5 - 2) << 5, 0x7 << 5);
	} else if (pdata->eoc == 0) {
		dev_dbg(max8998->dev,
			"EOC value not set: leave it unchanged.\n");
	} else {
		dev_err(max8998->dev, "Invalid EOC value\n");
		ret = -EINVAL;
		goto err;
	}

	/* Setup Charge Restart Level */
	switch (pdata->restart) {
	case 100:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x1 << 3, 0x3 << 3);
		break;
	case 150:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x0 << 3, 0x3 << 3);
		break;
	case 200:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x2 << 3, 0x3 << 3);
		break;
	case -1:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x3 << 3, 0x3 << 3);
		break;
	case 0:
		dev_dbg(max8998->dev,
			"Restart Level not set: leave it unchanged.\n");
		break;
	default:
		dev_err(max8998->dev, "Invalid Restart Level\n");
		ret = -EINVAL;
		goto err;
	}

	/* Setup Charge Full Timeout */
	switch (pdata->timeout) {
	case 5:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x0 << 4, 0x3 << 4);
		break;
	case 6:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x1 << 4, 0x3 << 4);
		break;
	case 7:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x2 << 4, 0x3 << 4);
		break;
	case -1:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x3 << 4, 0x3 << 4);
		break;
	case 0:
		dev_dbg(max8998->dev,
			"Full Timeout not set: leave it unchanged.\n");
		break;
	default:
		dev_err(max8998->dev, "Invalid Full Timeout value\n");
		ret = -EINVAL;
		goto err;
	}

	max8998->psy_ac.name = "max8998_ac";
	max8998->psy_ac.type = POWER_SUPPLY_TYPE_MAINS;
	max8998->psy_ac.get_property = max8998_battery_get_property;
	max8998->psy_ac.properties = max8998_battery_props;
	max8998->psy_ac.num_properties = ARRAY_SIZE(max8998_battery_props);

	ret = power_supply_register(max8998->dev, &max8998->psy_ac);
	if (ret) {
		dev_err(max8998->dev, "failed: power supply register (ac)\n");
		goto err;
	}

	max8998->psy_usb.name = "max8998_usb";
	max8998->psy_usb.type = POWER_SUPPLY_TYPE_USB;
	max8998->psy_usb.get_property = max8998_battery_get_property;
	max8998->psy_usb.properties = max8998_battery_props;
	max8998->psy_usb.num_properties = ARRAY_SIZE(max8998_battery_props);

	ret = power_supply_register(max8998->dev, &max8998->psy_usb);
	if (ret) {
		dev_err(max8998->dev, "failed: power supply register (usb)\n");
		goto err2;
	}

	max8998->callbacks.set_cable = max8998_set_cable;
	if (pdata->register_callbacks)
		pdata->register_callbacks(&max8998->callbacks);

	return 0;
err2:
	power_supply_unregister(&max8998->psy_ac);
err:
	kfree(max8998);
	return ret;
}

static int __devexit max8998_battery_remove(struct platform_device *pdev)
{
	struct max8998_battery_data *max8998 = platform_get_drvdata(pdev);

	power_supply_unregister(&max8998->psy_ac);
	power_supply_unregister(&max8998->psy_usb);
	kfree(max8998);

	return 0;
}

static const struct platform_device_id max8998_battery_id[] = {
	{ "max8998-battery", TYPE_MAX8998 },
	{ }
};

static struct platform_driver max8998_battery_driver = {
	.driver = {
		.name = "max8998-battery",
		.owner = THIS_MODULE,
	},
	.probe = max8998_battery_probe,
	.remove = __devexit_p(max8998_battery_remove),
	.id_table = max8998_battery_id,
};

module_platform_driver(max8998_battery_driver);

MODULE_DESCRIPTION("MAXIM 8998 battery control driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max8998-battery");
