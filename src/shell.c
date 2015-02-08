#include <stdint.h>
#include <stddef.h>
#include "includes/screen.h"
#include "includes/shell.h"
#include "includes/libcfuncs.h"

void sh_initialize()
{
	SH_ROW = 0;
	SH_COLUMN = 0;
	s_update_cursor(SH_ROW, SH_COLUMN);
	SH_COLOR = s_color(COLOR_LIGHT_CYAN, COLOR_RED);
	SH_BUFFER = (uint16_t*) 0xB8000;
	
	for ( size_t y = 0; y < S_HEIGHT; y++ )
		for ( size_t x = 0; x < S_WIDTH; x++ )
		{
			const size_t index = (y * S_WIDTH) + x;
			SH_BUFFER[index] = s_create(' ', SH_COLOR);
		}
}

void sh_color(uint8_t color)
{
	SH_COLOR = color;
}

void sh_put_char(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = (y * S_WIDTH) + x;	
	SH_BUFFER[index] = s_create(c, color);
	s_update_cursor(SH_ROW, SH_COLUMN);
}

void sh_write_char(char c)
{
	switch(c)
	{
		case '\n':
			// Soon to come... check for scrolling
			SH_COLUMN = 0;
			SH_ROW++;
			if(SH_ROW == S_HEIGHT)
			{
				sh_scroll_screen();
				SH_ROW = S_HEIGHT - 1;
				s_update_cursor(SH_ROW, SH_COLUMN);
			}
			return;
			
		case '\t':
			for(int i = 0; i < 4; i++)
				sh_write_char(' ');
			return;
			
		default:
			sh_put_char(c, SH_COLOR, SH_COLUMN, SH_ROW);
			
			if(++SH_COLUMN == S_WIDTH)
			{
				SH_COLUMN = 0;
				if(++SH_ROW == S_HEIGHT)
				{
					sh_scroll_screen();
					SH_ROW = S_HEIGHT - 1;
					s_update_cursor(SH_ROW, SH_COLUMN);
				}
			}
			
			s_update_cursor(SH_ROW, SH_COLUMN);
	}

	if(SH_ROW == S_HEIGHT)
		sh_scroll_screen();
	
	s_update_cursor(SH_ROW, SH_COLUMN);
}

void sh_write_string(const char* str)
{
	size_t strLen = str_length(str);
	for( size_t i = 0; i < strLen; i++)
		sh_write_char(str[i]);
}

void sh_scroll_screen()
{
	for(size_t x = 0; x < S_WIDTH; x++)
	{
		for(size_t y = 0; y < S_HEIGHT; y++)
		{
			const size_t index = (y * S_WIDTH) + x;
			SH_BUFFER[index - S_WIDTH] = SH_BUFFER[index];
			
			if(y == S_HEIGHT - 1)
			{
				SH_BUFFER[index] = s_create(' ', SH_COLOR);
			}
		}
	}
	
	s_update_cursor(SH_ROW, SH_COLUMN);
}