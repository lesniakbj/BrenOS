#include <stdint.h>

static inline void out_byte(uint16_t address, uint8_t value)
{
	asm volatile("outb %0, %1" :: "a"(value), "Nd"(address));
}

static inline uint8_t in_byte(uint16_t address)
{
	uint8_t retVal;
	asm volatile("inb %1, %0" : "=a"(retVal) : "Nd"(address));

	return retVal;
}