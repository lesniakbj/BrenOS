#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// TODO: Chnage vga.h to something more appropriate
#include <monolith/vga.h>

size_t TERMINAL_ROW;
size_t TERMINAL_COL;
uint8_t TERMINAL_COLOR;
uint16_t* TERMINAL_BUFFER;	// Generally, the VGA Buffer location

void terminal_initialize(void)
{
	TERMINAL_ROW = 0;
	TERMINAL_COL = 0;
	TERMINAL_COLOR = make_color(COLOR_LIGHT_CYAN, COLOR_RED);
	TERMINAL_BUFFER = VGA_MEMORY;
	
	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t memLoc = y * VGA_WIDTH + x;
			TERMINAL_BUFFER[memLoc] = make_terminal_character(' ', TERMINAL_COLOR);
		}
	}
};

void terminal_set_color(uint8_t color)
{
	TERMINAL_COLOR = color;
}

void terminal_put_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t memLoc = y * VGA_WIDTH + x;
	TERMINAL_BUFFER[memLoc] = make_terminal_character(c, color);
}

void terminal_put_char(char c)
{
	terminal_put_at(c, TERMINAL_COLOR, TERMINAL_COL, TERMINAL_ROW);
	
	if(++TERMINAL_COL == VGA_WIDTH)
	{
		TERMINAL_COL = 0;
		
		if(++TERMINAL_ROW == VGA_HEIGHT)
		{
			TERMINAL_ROW = 0;
		}
	}
}

void terminal_write(const char* str, size_t len)
{
	for(size_t i = 0; i < len; i++)
		terminal_put_char(str[i]);
}

void terminal_put_string(const char* str)
{
	terminal_write(str, strlen(data));
}

