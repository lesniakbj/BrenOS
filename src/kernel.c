#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "includes/kern_screen_helper.h"
#include "includes/kern_screen_functions.h"


size_t strlen(const char* str);
void kernel_main();

/* Hardware text mode color constants. */
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};
 
uint8_t make_color(enum vga_color bg, enum vga_color fg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_CYAN, COLOR_RED);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
	
	switch(c)
	{
		case '\n':
			terminal_row++;
			terminal_column = 0;
			return;
			
		case '\t':
			for(int i = 0; i < 4; i++)
				terminal_putchar(' ');
			return;
	}
	
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row = 0;
		}
	}
}
 
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

void terminal_put_string(const char* str, size_t x, size_t y)
{
	size_t xOrig = x;
	size_t len = strlen(str);
	for(size_t i = 0; i < len + 1; i++)
	{
		if(str[i] == '\n')
		{
			y++;
			x = xOrig;
			break;
		}
		terminal_putentryat(str[i], terminal_color, x++, y);
	}
}

void create_box()
{
	for(size_t x = 0; x < VGA_WIDTH; x++)
	{
		if(x == 0 || x == VGA_WIDTH - 1)
			terminal_putchar(' ');
		else
			terminal_putchar('=');
	}
	
	for(size_t num = 0; num < 10; num++)
	{
		for(size_t n = 0; n <= VGA_WIDTH - 1; n++)
		{
			if(n == 1 || n == VGA_WIDTH - 2)
				terminal_putchar('=');
			else
				terminal_putchar(' ');
		}
	}
	
	for(size_t x = 0; x < VGA_WIDTH; x++)
	{
		if(x == 0 || x == VGA_WIDTH - 1)
			terminal_putchar(' ');
		else
			terminal_putchar('=');
	}
}

void terminal_write_intro()
{
	terminal_writestring(" Hello, and Welcome to BrenOS! \n");
	create_box();
	terminal_put_string("| BrenOS - Current Known Commands |\n", 3, 2);
	terminal_put_string(" --------------------------------- \n", 3, 3);
	// Foreach command in list of known commands
	// print the name
	terminal_put_string("NONE!\n", 4, 4);
}
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
	terminal_initialize();
	/* Since there is no support for newlines in terminal_putchar yet, \n will
	   produce some VGA specific character instead. This is normal. */
	
	terminal_write_intro();
	
	/*
	terminal_writestring("Escape Sequences:\n");
	terminal_writestring("\a == slash a == Alarm (Beep, Bell)\n");
	terminal_writestring("\b == slash b == Backspace\n");
	terminal_writestring("\f == slash f == Formfeed\n");
	terminal_writestring("\r == slash r == Carriage Return\n");
	terminal_writestring("\t == slash t == Horizontal Tab\n");
	terminal_writestring("\v == slash v == Vertical Tab\n");
	terminal_writestring("\\ == slash b == Backslash\n");
	terminal_writestring("\' == slash \' == Single quotation mark\n");
	terminal_writestring("\" == slash \" == Double quotation mark\n");
	terminal_writestring("\? == slash ? == Question mark\n");
	*/
}