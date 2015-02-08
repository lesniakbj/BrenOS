#include <stdint.h>
#include <stddef.h>
#include "includes/screen.h"
#include "core.c"

uint8_t s_color(enum S_COLOR bg, enum S_COLOR fg)
{
	return fg | bg << 4;
}

uint16_t s_create(char c, uint8_t color)
{
	uint16_t ch16 = c;
	uint16_t color16 = color;
	
	return ch16 | color16 << 8;
}

void s_update_cursor(int y, int x)
{
	size_t index = (y * S_WIDTH) + x;
	
	out_byte(0x3d4, 0x0f);
	out_byte(0x3d5, (size_t)(index & 0xff));
	
	out_byte(0x3d4, 0x0e);
	out_byte(0x3d5, (size_t)((index >> 8) & 0xff));
}