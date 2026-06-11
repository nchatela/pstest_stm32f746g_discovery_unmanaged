/* Copyright 2023 The MathWorks, Inc. */
#include "pstunit.h"
#include "lcd_log.h"


void pst_write(const char * str,  unsigned long len) {
	LCD_LOG_Puts((uint8_t*)str, len);
}

void pst_flush() {
	LCD_LOG_UpdateDisplay();
}

