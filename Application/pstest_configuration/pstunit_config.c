/* Copyright 2023 The MathWorks, Inc. */
#include "pstunit.h"
#include "lcd_log.h"


static char bufferprintf[1000];
int	pst_printf (const char *__restrict format, ...)
{
	va_list args;
	va_start(args, format);
	int val = vsprintf(bufferprintf, format, args);
	va_end(args);
	LCD_LOG_Puts((uint8_t*)bufferprintf);
	return val;
}

void pst_write(const char * str,  unsigned long len) {
	LCD_LOG_Puts((uint8_t*)str);
}

void pst_flush() {
	LCD_LOG_UpdateDisplay();
}

