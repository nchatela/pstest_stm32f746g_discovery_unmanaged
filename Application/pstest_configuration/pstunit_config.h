/* Copyright 2023 The MathWorks, Inc. */

// this file is automatically included because PST_USER_CONFIG_FILE is defined (-D)

// we force the kind of output as "table" to get the Human readable format
#define PST_OUTPUT PST_OUTPUT_TABLE

// we deactivate the execution time as it requires some specific "host" functions
#define PST_ENABLE_EXECUTION_TIME   0



extern void pst_write(const char * str, unsigned long len);
extern void pst_flush();
extern int	pst_printf (const char *__restrict, ...);
#define PST_WRITE(str, len)       pst_write(str, len)
#define PST_FLUSH()         pst_flush()
#define PST_PRINTF			pst_printf
