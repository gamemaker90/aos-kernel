/*
 *  File: isr.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/isr.h>
#include <kernel/system/terminal.h>
#include <kernel/system/io.h>

MODULE("interrupt-service-routine", "0.01a");

isr_t interrupt_handlers[256];

string exception_messages[] = 
{
	"AOS_INTERRUPT Raised! : [Division By Zero Exception]",
	"AOS_INTERRUPT Raised! : [Debug Exception]",
	"AOS_INTERRUPT Raised! : [Non-Maskable Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Breakpoint Exception]",
	"AOS_INTERRUPT Raised! : [Into Detected Overflow Exception]",
	"AOS_INTERRUPT Raised! : [Out Of Bounds Exception]",
	"AOS_INTERRUPT Raised! : [Invalid Opcode Exception]",
	"AOS_INTERRUPT Raised! : [No Coprocessor exception]",
	"AOS_INTERRUPT Raised! : [Double Fault Exception]",
	"AOS_INTERRUPT Raised! : [Coprocessor Segment Overrun Exception]",
	"AOS_INTERRUPT Raised! : [Bad TSS Exception]",
	"AOS_INTERRUPT Raised! : [Segment Not Present Exception]",
	"AOS_INTERRUPT Raised! : [Stack Fault Exception]",
	"AOS_INTERRUPT Raised! : [General Protection Fault Exception]",
	"AOS_INTERRUPT Raised! : [Page Fault Exception]",
	"AOS_INTERRUPT Raised! : [Unknown Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Coprocessor Fault Exception]",
	"AOS_INTERRUPT Raised! : [Alignment Check Exception]",
	"AOS_INTERRUPT Raised! : [Machine Check Exception]",
};

DEPRECATED void
fault_handler(registers_t registers) 
{
	if (registers.INT_NO < 32) 
	{
		//_ERROR(exception_messages[registers.INT_NO]);
		//cpu_halt();
		//terminal_printf("System halted!");
	}
}

void 
register_interrupt_handler(ubyte n, isr_t handler) 
{
	interrupt_handlers[n] = handler;
}

void
isr_handler(registers_t registers) 
{
	terminal_printf("%s, Int No: 0x%X\n", exception_messages[registers.INT_NO], registers.INT_NO);
	if (interrupt_handlers[registers.INT_NO] != 0) 
	{
		isr_t handler = interrupt_handlers[registers.INT_NO];
		handler(registers);
	} 
}

void 
irq_handler(registers_t registers) 
{
	if (registers.INT_NO >= 40) 
	{
		write_portb(0xA0, 0x20);
	}
	write_portb(0x20, 0x20);	/* EOI */
	
	if (interrupt_handlers[registers.INT_NO] != 0) 
	{
		isr_t handler = interrupt_handlers[registers.INT_NO];
		handler(registers);
	}
}
