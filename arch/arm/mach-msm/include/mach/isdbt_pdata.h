/*
*
* arch/arm/mach-msm/include/mach/isdbt_pdata.h
*
* isdbt driver
*
* Copyright (C) (2011, Samsung Electronics)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation version 2.
*
* This program is distributed "as is" WITHOUT ANY WARRANTY of any
* kind, whether express or implied; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/

#ifndef _ISDBT_PDATA_H_
#define _ISDBT_PDATA_H_

#if defined(CONFIG_ISDBT)
struct isdbt_platform_data {
	void (*gpio_on) (void);
	void (*gpio_off)(void);
	int irq;
};
#endif
#endif

