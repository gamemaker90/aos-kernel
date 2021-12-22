/*
 *  File: cpu.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/cpu.h>
#include <kernel/cpuid.h>
#include <adamantine/aos-defs.h>
#include <adamantine/tty.h>
#include <kernel/kernel.h>
#include <stdbool.h>

/* Grab external references */
extern uint32_t cpuid_supported(void);					// Checks if CPUID is supported
extern uint32_t cpuid_get_property(uint32_t);			// Gets CPUID properties?
extern system_info_t *system_info;						// Defined in init/main.c

/* Initialize the CPU */
void
cpu_init(void)
{
	bool is_supported = (cpuid_supported() > 0);		// Check if CPUID is supported with this CPU
	if (!is_supported)									// If not, return breaking flow
		return;
	tty_puts("[INFO]: CPU is initialized!\n");			// TODO: Change these to the message dispatcher...
	tty_puts("[INFO]: CPU Manufacturer: ");				// TODO: Change these to the message dispatcher...
	tty_puts(cpu_vendor_string());						// TODO: Change these to the message dispatcher...
	tty_puts("\n");										// TODO: Change these to the message dispatcher...
}

/* Halt the CPU */
inline void
cpu_halt(void) 
{
	/* We have to print this before theCPU halts for obvious reasons */
	tty_puts("System halted...\n");
	__asm__ (
		"cli\n\t"	
		"hlt\n\t"
	);
}

/* Suspend the CPU */
inline void
cpu_suspend(void) 
{
	__asm__ ( "hlt\n\t" );
}

/* Sets the interrupt flag (IF) to 0. */
void
cpu_clear_interrupts(void)
{
	__asm__ ( "cli\n\t" );
}

/* Sets the interrupt flag (IF) to 1. */
void
cpu_set_interrupts(void)
{
	__asm__ ( "sti\n\t" );
}

/* Return CPUID */
inline uint32_t
cpuid(void)
{
	/* Check if it's even supported */
	uint32_t x = cpuid_supported();
	asm volatile
	(
		"mov $0x0, %eax\n\t"
		"cpuid\n\t"
	);
	return (x);
}

/* Get the CPU string */
inline uint32_t 
cpuid_string(uint32_t _code, uint32_t *_location) 
{
	__asm__ volatile(
		"cpuid":
		"=a"(*_location), 
		"=b"(*(_location + 0)), 
		"=d"(*(_location + 1)), 
		"=c"(*(_location + 2)):
		"a"(_code)
	);
	return ((uint32_t)_location[0]);
}

/* Get the CPU vendor string */
inline char *
cpu_vendor_string(void)
{
	static char Str[16];
	cpuid_string(0x00000000, (uint32_t *)(Str));
	system_info->cpu_name = Str;

	return (Str);
}

/* Checks if CPUID is even supported for this model */
inline uint32_t
cpu_check_is_supported(void)
{
	bool result = cpuid_supported();
	if (result == false)
		tty_puts("[ERROR]: CPUID is not supported!\n");
	return (result);
}
