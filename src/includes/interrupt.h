#ifndef KERN_INT_HEADER
#define KERN_INT_HEADER

#include <stdint.h>

struct idt_entry
{
	uint16_t baseLo;
	uint16_t selector;
	uint8_t SET_ZERO;
	uint8_t flags;
	uint16_t baseHigh;
	
}__attribute__((packed));

struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));


struct idt_entry idt[256];
struct idt_ptr i_ptr;

extern void idt_load();

void idt_set(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_install();

#endif