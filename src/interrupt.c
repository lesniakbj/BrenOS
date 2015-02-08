#include <stddef.h>

#include "includes/interrupt.h"
#include "includes/libcfuncs.h"

void idt_set(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	uint16_t low = (uint16_t) base & 0x0000FFFF;
	uint16_t high = (uint16_t) ((base & 0xFFFF0000) >> 16);
	
	idt[num].baseLo = low;
	idt[num].selector = sel;
	idt[num].SET_ZERO = 0;
	idt[num].flags = flags;
	idt[num].baseHigh = high;
}

void idt_install()
{
	i_ptr.limit = (sizeof (struct idt_entry) * 256) - 1;
	i_ptr.base = &idt;
	
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
	
	idt_load();
}