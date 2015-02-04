#if defined(__linux__)
	#error "Use a cross compiler!"
#endif

#if !defined(__i386__)
	#error "Use ix86-elf compiler!"
#endif

#include <stdint.h>
#include <stddef.h>

static const unsigned int SCREEN_WIDTH = 80;
static const unsigned int SCREEN_HEIGHT = 25;

unsigned int TERMINAL_ROW;
unsigned int TERMINAL_COLUMN;
uint8_t TERMINAL_COLOR;
uint16_t* TERMINAL_BUFFER;

enum SCREEN_COLOR
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
	COLOR_WHITE = 15
};

uint8_t create_color(enum SCREEN_COLOR fore, enum SCREEN_COLOR back)
{
	return fore | back << 4;
}

uint8_t create_character(char c, uint8_t color)
{
	uint16_t ch16 = c;
	uint16_t color16 = color;
	
	return ch16 | color16 << 8;
}

unsigned int strlen(const char* str)
{
	unsigned int size = 0;
	while(str[size] != 0)
		size++;
		
	return size;
}

// Fill the screen with the correct color...
void terminal_initialize()
{
	TERMINAL_ROW = 0;
	TERMINAL_COLUMN = 0;
	TERMINAL_COLOR = create_color(COLOR_CYAN, COLOR_RED);
	// Begin the buffer at the start of 
	// VGA Video Memory
	TERMINAL_BUFFER = (uint16_t*) 0xB8000; 
	
	for(int x = 0; x < SCREEN_WIDTH; x++)
	{
		for(int y = 0; y < SCREEN_HEIGHT; y++)
		{
			// Index is the spot in memory the character gets
			// written to
			const unsigned int index = y * SCREEN_WIDTH + x;  
			TERMINAL_BUFFER[index] = create_character(' ', TERMINAL_COLOR);
		}
	}
}

void terminal_set_color(uint8_t color)
{
	TERMINAL_COLOR = color;
}

void terminal_make_entry(char c, uint8_t color, unsigned int x, unsigned int y)
{
		const unsigned int index = y * SCREEN_WIDTH + x;
		TERMINAL_BUFFER[index] = create_character(c, color);
}

void terminal_put_char(char c)
{
	terminal_make_entry(c, TERMINAL_COLOR, TERMINAL_COLUMN, TERMINAL_ROW);
	
	if(++TERMINAL_COLUMN == SCREEN_WIDTH)
	{
		TERMINAL_COLUMN = 0;
		
		if(++TERMINAL_ROW == SCREEN_HEIGHT)
		{
			TERMINAL_ROW = 0;
		}
	}
}

void terminal_write(const char* str)
{
	unsigned int length = strlen(str);
	
	for(unsigned int i = 0; i < length; i++)
		terminal_put_char(str[i]);
}

#if defined(__cplusplus)
extern "C"
#endif
int main(struct multiboot *mboot_pointer)
{
	terminal_initialize();
	terminal_write("Hello, and welcome to BrenOS!");
}
