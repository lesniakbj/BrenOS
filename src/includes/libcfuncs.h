#ifndef LIBC_FUNCS_HEADER
#define LIBC_FUNCS_HEADER

size_t str_length(const char* str);
char* int_to_string(int num, char* str, int base);
void memset(void* ptr, uint32_t value, size_t num);

#endif