#ifndef KERN_SHELL_HEADER
#define KERN_SHELL_HEADER

size_t SH_ROW;
size_t SH_COLUMN;
uint8_t SH_COLOR;
uint16_t* SH_BUFFER;

void sh_initialize();
void sh_set_color(uint8_t color);

void sh_write_char(char c);
void sh_write_string(const char* data);

void sh_put_char(char c, uint8_t color, size_t x, size_t y);

void sh_scroll_screen();

#endif