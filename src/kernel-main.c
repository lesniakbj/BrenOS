#if !defined(__cplusplus)
#include <stdbool.h> 
#endif

#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross compiler stupid!"
#endif

#if !defined(__i386__)
#error "You need to compile with ix86-elf compiler"
#endif

/* HARDWARE CONSTANTS */
static const size_t SCREEN_WIDTH = 80;
static const size_t SCREEN_HEIGHT = 25;

size_t SHELL_ROW;
size_t SHELL_COLUMN;
uint8_t SHELL_COLOR;
uint16_t* SHELL_BUFFER;

/* HARDWARE TEXT COLORS */
enum graphic_colors
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

uint8_t make_shell_color(enum gaphics_colors foreground, enum graphics_colors background)
{
	return foreground | background << 4;
}

uint16_t make_shell_entry(char character, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

uint8_t strlen(const char* str)
{
	size_t ret = 0;
	while( str[ret] != 0)
		ret++;
	
	return ret;
}

void shell_initialize()
{
	SHELL_ROW = 0;
	SHELL_COLUMN = 0;
	SHELL_COLOR = make_shell_color(COLOR_LIGHT_CYAN, COLOR_RED);
	SHELL_BUFFER = (uint16_t*) 0xB800;
	
	for(size_t y = 0; y < SCREEN_HEIGHT; y++)
	{
		for(size_t x = 0; x < SCREEN_WIDTH; x++)
		{
			const size_t index = y * SCREEN_WIDTH + x;
			SHELL_BUFFER[index] = make_shell_entry(' ', SHELL_COLOR);
		}
	}
}

void set_shell_color(uint8_t color)
{
	SHELL_COLOR = color;
}

void shell_put_entry_at(char c, unit8_t color, size_t x, size_t y)
{
	const size_t index = y * SCREEN_WIDTH + x;
	SHELL_BUFFER[index] = make_shell_entry(c, color);
}

void shell_put_char(char c)
{
	shell_put_entry_at(c, SHELL_COLOR, SHELL_COLUMN, SHELL_ROW);
	
	if(++SHELL_COLUMN == SCREEN_WIDTH)
	{
		SHELL_COLUMN = 0;
		
		if(++SHELL_ROW == SCREEN_HEIGHT)
		{
			SHELL_ROW = 0;
		}
	}
}

void shell_write_string(const char* str)
{
	size_t length = strlen(str);
	
	for(size_t i = 0; i < length; i++)
		shell_put_char(str[i]);
}

#if defined(__cplusplus)
extern "C"
#endif
void kernel_main()
{
	shell_initialize();
	shell_write_string("Hello, and welcome to BrenOS!");
}