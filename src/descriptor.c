#include "includes/descriptor.h"

void gdt_set(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].baseLow = (base & 0x0000FFFF);
	gdt[num].baseMiddle = (base >> 16) & 0x00FF;
	gdt[num].baseHigh = (base >> 24) & 0x00FF;
	
	gdt[num].limitLow = (limit & 0x0000FFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);
	
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_install()
{
	g_ptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
	g_ptr.base = &gdt;
	
	// NULL Descriptior
	gdt_set(0, 0, 0, 0, 0);
	
	gdt_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	
	gdt_flush();
}