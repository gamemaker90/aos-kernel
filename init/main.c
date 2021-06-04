#include <adamantine/tty.h>
#include <kernel/drivers/vga.h>
#include <i386/gdt.h>
#include <i386/ldt.h>
#include <i386/idt.h>
#include <kernel/irq.h>
#include <kernel/pit.h>
#include <kernel/cpu.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/system/system.h>
#include <kernel/memory/memory-util.h>
#include <kernel/memory/paging.h>
#include <kernel/kernel.h>

#include <math/math-util.h>

#include <compiler.h>
#include <string.h>

#include <stddef.h>

/* Define macros for the Text Mode cusror */
#define CURSOR_START	0x0								// Top=0
#define CURSOR_END		0xF								// Bottom=15

/* External references */
extern uint32_t kernel_end;								// The end of the kernel memory (defined in "linker.ld")
extern isr_t interrupt_handlers[MAX_INTERRUPTS];		// The interrupt handler (defined in "isr.c")

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_init(void)
{
	gdt_init();											// Defined in "gdt.c"
	ldt_init();											// Defined in "ldt.c"
	idt_init();											// Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t)*256);	// Clear the address of the interrupt handlers to zero
}

kernel_t
init(void)
{
	tty_init((uint16_t *)VGA_TEXT_MODE_COLOR);			// Initialize the teletype with color Text Mode enabled
	tty_set_foreground(SYSTEM_COLOR_LT_GREEN);			// Set the default text color to light green (the color of adamntine)
	tty_cursor_enable(CURSOR_START, CURSOR_END);		// Enable the Text Mode cursor as a block cursor
	tty_clear();										// Clear the teletype screen
	
	descriptor_tables_init();							// Call the function which initialized the GDT, LDT, and IDT
	pit_init(50);										// Initialize the PIT at 50Hz
	mm_init((uint32_t)&kernel_end);						// Initialize the kernel heap (to be replaced...)
	initialize_paging();								// Initialize memory paging
	cpu_init();											// Initialize the CPU

	keyboard_init();									// Initialize the keyboard
	system_init();										// Initialize the system
	
	return;
}

/* The entry point of the kernel (defined in "boot.S") */
HOT kernel_t
k_main(void)
{
	
}
