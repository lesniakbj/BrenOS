#include <stddef.h>

size_t str_length(const char* str)
{
	size_t size = 0;
	while ( str[size] != 0 )
		size++;
	
	return size;
}

char* int_to_string(int num, char* str, int base)
{
	if(base < 2 || base > 36)
	{
		*str = '\0';
		return str;
	}
	
	char* ptr1 = str;
	char* ptr2 = str;
	char temp_char;
	int temp_value;
	
	do {
		temp_value = num;
		num /= base;
		*ptr1++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (temp_value - num * base)];
	} while(num);
	
	if(temp_value < 0)
		*ptr1++ = '-';
	
	*ptr1-- = '\0';
	while(ptr2 < ptr1)
	{
		temp_char = *ptr1;
		*ptr1-- = *ptr2;
		*ptr2++ = temp_char;
	}
	
	return str;
}