#include <stddef.h>
#include <stdint.h>

#include "includes/int_handlers.h"
#include "includes/interrupt.h"
#include "includes/core.h"
#include "includes/shell.h"
#include "includes/libcfuncs.h"

void int_hand_install()
{
	idt_set(0, (unsigned)isr0, 0x08, 0x8E);
	idt_set(1, (unsigned)isr1, 0x08, 0x8E);
	idt_set(2, (unsigned)isr2, 0x08, 0x8E);
	idt_set(3, (unsigned)isr3, 0x08, 0x8E);
	idt_set(4, (unsigned)isr4, 0x08, 0x8E);
	idt_set(5, (unsigned)isr5, 0x08, 0x8E);
	idt_set(6, (unsigned)isr0, 0x08, 0x8E);
	idt_set(7, (unsigned)isr1, 0x08, 0x8E);
	idt_set(8, (unsigned)isr2, 0x08, 0x8E);
	idt_set(9, (unsigned)isr3, 0x08, 0x8E);
	idt_set(10, (unsigned)isr4, 0x08, 0x8E);
	idt_set(11, (unsigned)isr5, 0x08, 0x8E);
	idt_set(12, (unsigned)isr0, 0x08, 0x8E);
	idt_set(13, (unsigned)isr1, 0x08, 0x8E);
	idt_set(14, (unsigned)isr2, 0x08, 0x8E);
	idt_set(15, (unsigned)isr3, 0x08, 0x8E);
	idt_set(16, (unsigned)isr4, 0x08, 0x8E);
	idt_set(17, (unsigned)isr5, 0x08, 0x8E);
	idt_set(18, (unsigned)isr0, 0x08, 0x8E);
	idt_set(19, (unsigned)isr1, 0x08, 0x8E);
	idt_set(20, (unsigned)isr2, 0x08, 0x8E);
	idt_set(21, (unsigned)isr3, 0x08, 0x8E);
	idt_set(22, (unsigned)isr4, 0x08, 0x8E);
	idt_set(23, (unsigned)isr5, 0x08, 0x8E);
	idt_set(24, (unsigned)isr0, 0x08, 0x8E);
	idt_set(25, (unsigned)isr1, 0x08, 0x8E);
	idt_set(26, (unsigned)isr2, 0x08, 0x8E);
	idt_set(27, (unsigned)isr3, 0x08, 0x8E);
	idt_set(28, (unsigned)isr4, 0x08, 0x8E);
	idt_set(29, (unsigned)isr5, 0x08, 0x8E);
	idt_set(30, (unsigned)isr4, 0x08, 0x8E);
	idt_set(31, (unsigned)isr5, 0x08, 0x8E);
}

void fault_handler(struct regs* r)
{
	if(r->int_no < 32)
	{
		sh_write_string("Exception! System Halted...\n");
	}
}