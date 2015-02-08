#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "includes/screen.h"
#include "includes/core.h"
#include "includes/shell.h"
#include "includes/libcfuncs.h"
#include "includes/keyboard.h"

void kern_main();

void kern_main()
{
	sh_initialize();	
	char countStr[32];
	
	/*
	for(int x = 0; x < 81; x++)
	{
		sh_write_string("Iteration: ");
		sh_write_string(int_to_string(SH_ROW, countStr, 10));
		sh_write_string(",");
		sh_write_string(int_to_string(x, countStr, 10));
		sh_write_string("\n");
	}
	*/
	sh_write_string("Escape Sequences:");
	sh_write_string(int_to_string(kb_control_status(), countStr, 2));

	/*
	sh_write_string("\a == slash a == Alarm (Beep, Bell)\n");
	sh_write_string("\b == slash b == Backspace\n");
	sh_write_string("\f == slash f == Formfeed\n");
	sh_write_string("\r == slash r == Carriage Return\n");
	sh_write_string("\t == slash t == Horizontal Tab\n");
	sh_write_string("\v == slash v == Vertical Tab\n");
	sh_write_string("\\ == slash b == Backslash\n");
	sh_write_string("\' == slash \' == Single quotation mark\n");
	sh_write_string("\" == slash \" == Double quotation mark\n");
	sh_write_string("\? == slash ? == Question mark\n");
	sh_write_string(">");
	*/
}