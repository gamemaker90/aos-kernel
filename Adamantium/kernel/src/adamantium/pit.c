/*
 *  File: pit.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#define __DEBUG__		1

#include <kernel/pit.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/cpu.h>
#include <kernel/rtc.h>
#include <drivers/tty.h>
#include <system/portio.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include <compiler.h>

extern unsigned char second;
extern unsigned char minute;
extern unsigned char hour;
extern unsigned char day;
extern unsigned char month;
extern unsigned char year;

static const char *month_names[12] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

/* Number of ticks since startup */
uint32_t tick = 0;

static void __unused
update_clock(void)
{
	long irq = irq_disable();
	
	//P_VGA vga = k_tty_get_vgahandle();
	printf("Current Time: ");
	if (hour < 10)		printf("0%d:", hour); else printf("%d:", hour);
	if (minute < 10)	printf("0%d:", minute); else printf("%d:", minute);
	if (second < 10)	printf("0%d - ", second); else printf("%d - ", second);

	printf("%s %d, %d\n", month_names[month - 1], day, year);
	read_rtc();
	irq_restore(irq);
}

static void __unused
play_sound(uint32_t _nfreq)
{
	uint32_t div;
	uint8_t tmp=0;

	div = PIT_BASE_FREQ / _nfreq;
	outb(0x43, 0xB6);
	outb(0x42, (uint8_t)div);
	outb(0x42, (uint8_t)(div >> 8));
	if (tmp != (tmp | 3))
	{
		outb(0x61, tmp | 3);
	}
}

void
pit_beep_start(uint32_t _freq)
{
	play_sound(_freq);
}

void
pit_beep_stop(void)
{
	uint8_t tmp = inb(0x61) & 0xFC;
	outb(0x61, tmp);
}

static void
timer_callback(registers_t _regs)
{
	/* Make sure we're not getting an error code */
	if (!_regs.err_code)
	{
		tick++;
		//task_switch();
		//update_clock();
	}
}

/* Initialize the Programmable Interval Timer */
void
pit_initialize(uint32_t _freq)
{
	cpu_set_interrupts();								// Make sure interrupts are enabled (won't work otherwise)
	register_interrupt_handler(IRQ0, &timer_callback);	// Assign IRQ0 to the PIT callback function
	uint32_t divisor = PIT_BASE_FREQ / _freq;			// Set the PIT divisor
	outb(PIT_CMD_PORT, 0x36);							// TODO: Figure this out...

	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

	outb(PIT_CHANNEL_0, l);
	outb(PIT_CHANNEL_0, h);
#if defined(VERBOSE_FLAGS)
	print_verbose_message("PIT is initialized!", INFO);
#endif
}
