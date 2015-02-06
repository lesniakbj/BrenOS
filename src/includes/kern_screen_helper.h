#ifndef KERN_SCREEN_HELPER
#define KERN_SCREEN_HELPER

enum vga_color;
uint8_t make_color(enum vga_color bg, enum vga_color fg);
uint16_t make_vgaentry(char c, uint8_t color);

#endif