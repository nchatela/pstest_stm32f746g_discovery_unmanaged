/* Copyright 2023 The MathWorks, Inc. */

// this file is automatically included because PST_USER_CONFIG_FILE is defined (-D)
#include <stdint.h>
// we define the sending type as "user-defined". It means the user as to provide an implementation 
// for the 4 following sending macro (PSPROFILE_SENDING_XXXXX)
#define PSPROFILE_SENDING_TYPE 2

// Macro definition required by the PSPROFILE_SENDING_TYPE == 2.
#define PSPROFILE_SENDING_INIT()                         psprofile_sending_init()
#define PSPROFILE_SENDING_DATA_ASYNC(ptrData, numData)  psprofile_sending_data_async(ptrData, numData)
#define PSPROFILE_SENDING_DATA_WAIT()                     psprofile_sending_data_wait()
#define PSPROFILE_SENDING_END()                         psprofile_sending_end()

// prototypes needs to avoid warning
#define PSPROFILE_CONFIG_PROTOTYPES \
int psprofile_sending_init(void); \
int psprofile_sending_data_async(const char* ptrData, uint32_T numData);\
int psprofile_sending_data_wait(); \
int psprofile_sending_end();

// configuration execution-profiling
#define PSPROFILE_EXECPROF_AVAILABLE 		1
extern uint32_t getTIM2Cnt();
#define PSPROFILE_GET_TIMESTAMP() getTIM2Cnt()

// configuration stack-profiling
#define PSPROFILE_STACKPROF_AVAILABLE 		1
extern uint32_t psprofile_getstackptr();
#define PSPROFILE_GET_STACKPTR() psprofile_getstackptr()
