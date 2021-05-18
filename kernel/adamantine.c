/*
 *  File: kernel.c
 *  Author: Vincent Cupo
 *  
 *  This file is the initial startup point of the bootloader.
 *  It is responsible for calling on GRUB and the kernel for boot.
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

#if !defined(__AOS32__)
#define __AOS32__
#define __KERNEL	__AOS32__
#endif

#include <adamantine/adamantine.h>
#include <kernel/drivers/vga.h>
#include <kernel/system/terminal.h>
#include <kernel/x86/descriptor-tables.h>
#include <kernel/pit.h>
#include <kernel/cpu.h>
#include <kernel/system/io.h>
#include <kernel/memory/memory-util.h>
#include <kernel/memory/paging.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <adamantine/message-dispatcher.h>
#include <kernel/system/system.h>
#include <kernel/system/types.h>
#include <kernel/version.h>

#include <kernel/irq.h>

#include <stdlib.h>
#include <string.h>

extern uint32_t kernel_end;
static inline int32_t test_code(void);

kernel_t
kmain(void)
{
	terminal_init(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_CYAN);
	terminal_clear();  

	init_descriptor_tables();
	pit_init(60);
	mm_init((uint32_t)&kernel_end);
	initialize_paging();
    cpu_init();

	test_code();

	keyboard_init();
	system_init();
}

//==========================================================================//

static inline void 
putpixel(unsigned char *screen, int x, int y, int color)
{
	unsigned where = x * 4 + y * 3200;
	screen[where] = color & 255;
	screen[where + 1] = (color >> 8) & 255;
	screen[where + 2] = (color >> 16) & 255;
}

static inline int32_t
test_code(void)
{
	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, j, 0x007F7F);
		}
	}

	for (size_t i = 4; i < 12; i++)
	{
		putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, 4, 0xFFFFFF);
		putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, 5, 0xFFFFFF);

		putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, 7, 0xFFFFFF);
		putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, 8, 0xFFFFFF);

		putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, 10, 0xFFFFFF);
		putpixel((unsigned char *)VGA_GRAPHICS_MODE, i, 11, 0xFFFFFF);
	}
	return 0;
}
