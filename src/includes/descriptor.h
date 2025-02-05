#ifndef KERN_GDT_HEADER
#define KERN_GDT_HEADER

#include <stdint.h>

struct gdt_entry
{
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t baseMiddle;
	uint8_t access;
	uint8_t granularity;
	uint8_t baseHigh;
}__attribute__((packed));

struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr g_ptr;

extern void gdt_flush();

void gdt_set(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_install();

#endif