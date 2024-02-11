// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2024
 * Andrey Skvortsov, <andrej.skvortzov@gmail.com>
 */

#include <dm.h>
#include <dm/ofnode.h>
#include <extension_board.h>
#include <i2c.h>
#include <malloc.h>

#ifdef CONFIG_CMD_EXTENSION
#ifdef CONFIG_PINEPHONE_DT_SELECTION

#define PINEPHONE_LIS3MDL_I2C_ADDR     0x1E
#define PINEPHONE_LIS3MDL_I2C_BUS      1 /* I2C1 */

int extension_board_scan(struct list_head *extension_list)
{
	struct extension *ext;
	bool af8133j_detected;
	ofnode node;
	struct udevice *bus, *dev;
	int num_capes = 0;

	printf("start extension board scan\n");
	node = ofnode_by_compatible(ofnode_null(), "pine64,pinephone-1.2");
	if (!ofnode_valid(node))
	       return num_capes;

	if (!uclass_get_device_by_seq(UCLASS_I2C, PINEPHONE_LIS3MDL_I2C_BUS, &bus)) {
		dm_i2c_probe(bus, PINEPHONE_LIS3MDL_I2C_ADDR, 0, &dev);
		af8133j_detected = dev ? false : true;
		printf("extentions: %d\n", af8133j_detected);
		af8133j_detected = true;
	}

	printf("extentions: %d\n", af8133j_detected);
	if (af8133j_detected) {
		ext = calloc(1, sizeof(struct extension));
		if (!ext) {
			printf("Error in memory allocation\n");
			return num_capes;
		}

		/* snprintf(ext->overlay, sizeof(ext->overlay), "sun50i-a64-pp-af8133j.dtbo"); */
		snprintf(ext->overlay, sizeof(ext->overlay), "sun50i-a64-pinephone-1.2-af8133j.dtbo");
		snprintf(ext->name, sizeof(ext->name), "af8133j");
		snprintf(ext->version, sizeof(ext->version), "1");
		snprintf(ext->owner, sizeof(ext->owner), "Pine64");
		list_add_tail(&ext->list, extension_list);
		num_capes++;
	}

	return num_capes;
}
#endif
#endif
