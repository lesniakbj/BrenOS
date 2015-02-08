#ifndef KERN_SCREEN_HEADER
#define KERN_SCREEN_HEADER

static const size_t S_WIDTH = 80;
static const size_t S_HEIGHT = 25;

enum S_COLOR
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

uint8_t s_color(enum S_COLOR bg, enum S_COLOR fg);
uint16_t s_create(char c, uint8_t color);

void s_update_cursor(int x, int y);

#endif