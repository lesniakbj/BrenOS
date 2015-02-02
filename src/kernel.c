#if !defined(__i386__)
	#error "Use ix86-elf compiler!"
#endif

#include <stdint.h>

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

int8_t create_color(enum SCREEN_COLOR fore, enum SCREEN_COLOR back)
{
	return fore | back << 4;
}

int main(struct multiboot *mboot_pointer)
{
	return 0xDEADBEBE;
	//shell_initialize();
	//shell_write_string("Hello, and welcome to BrenOS!");
}
