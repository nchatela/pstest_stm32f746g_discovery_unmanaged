/* Copyright 2023 The MathWorks, Inc. */
#include "psprofile.h"
#include "stm32746g_discovery.h"
#include <string.h>

// In this file are implemented the required functions needed to implement the communication with the host in order to "stream"
// the profiling (coverage, execution or stack) datas. 
// In this example, the UART is used to communicate with the ST-Link COM Port on the computer


static UART_HandleTypeDef huart1;

// Implement the USART1 initialization
// return value: PSPROFILE_SUCCESS: init went well
//               PSPROFILE_ERROR: error occurred
int psprofile_sending_init(void) {
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	BSP_COM_Init(COM1, &huart1);
	return PSPROFILE_SUCCESS;
}

// This methods is called for each frame that is sent to the host. 
// Here, the data are sent directly to the UART
// return value: PSPROFILE_SUCCESS: sending went well
//               PSPROFILE_ERROR: error occurred
int psprofile_sending_data_async(const char* ptrData, uint32_T numData) {
	if (HAL_OK != HAL_UART_Transmit(&huart1, (const uint8_t*)ptrData, numData, HAL_MAX_DELAY)) {
		return PSPROFILE_ERROR;
	}
	return PSPROFILE_SUCCESS;
}

// This methods is needed in case psprofile_sending_data_async is asynchronous. In this case, this function is used to pull the result
// return value: PSPROFILE_SUCCESS: sending is over
//               PSPROFILE_ONGOING: sending is on going
//               PSPROFILE_ERROR: error occurred
int psprofile_sending_data_wait() {
		return PSPROFILE_SUCCESS;
}
int psprofile_sending_end() {
	return PSPROFILE_SUCCESS;
}


uint32_t psprofile_getstackptr(void)
{
	uint32_t tmp = 0;

    tmp = (uint32_t)&tmp;

    return tmp;
}
