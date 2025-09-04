/* Copyright 2023 The MathWorks, Inc. */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lcd_log.h"

/* Private function prototypes -----------------------------------------------*/
static void LCD_Config(void);
static void SystemClock_Config(void);

#include "pstunit.c"
#include "psprofile.h"


static TIM_HandleTypeDef TimHandle;

void init_TIM2_for_execprofiling ()
{
  /* Enable TIM6 clock */
  __HAL_RCC_TIM2_CLK_ENABLE();

  /* Initialize TIM6 */
  TimHandle.Instance = TIM2;
  TimHandle.Init.Period = 0xFFFFFFFF;
  TimHandle.Init.Prescaler = 0;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if(HAL_TIM_Base_Init(&TimHandle) == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    HAL_TIM_Base_Start(&TimHandle);
  }
}
uint32_t getTIM2Cnt() {
	return TIM2->CNT;
}


int main(void)
{

 HAL_Init();
  
  /* Configure the system clock to 200 MHz */
  SystemClock_Config();
  
  /* Configure LED1 */
  BSP_LED_Init(LED1);
  init_TIM2_for_execprofiling();

  /*##-1- Configure LCD ######################################################*/
  LCD_Config(); 
  
  /* Configure TAMPER Button */
  BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_EXTI);


  BSP_LCD_SetTextColor(LCD_COLOR_RED);
  LCD_LOG_Init();
  LCD_LOG_SetHeader((uint8_t*)"Polyspace Test 1.0");
  LCD_LOG_SetFooter((uint8_t*)"Copyright The Mathworks 2024");

  PST_REGFCN_CALL(registerTests);
  PST_MAIN(0, NULL);
  psprofile_stream();
  while(1)
  {     
  }
}

/**
  * @brief  LCD configuration
  * @param  None
  * @retval None
  */
static void LCD_Config(void)
{
  /* LCD Initialization */ 
  BSP_LCD_Init();

  /* LCD Initialization */ 
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS+(BSP_LCD_GetXSize()*BSP_LCD_GetYSize()*4));

  /* Enable the LCD */ 
  BSP_LCD_DisplayOn(); 
  
  /* Select the LCD Background Layer  */
  BSP_LCD_SelectLayer(0);

  /* Clear the Background Layer */ 
  BSP_LCD_Clear(LCD_COLOR_BLACK);  
  
  /* Select the LCD Foreground Layer  */
  BSP_LCD_SelectLayer(1);

  /* Clear the Foreground Layer */ 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Configure the transparency for foreground and background :
     Increase the transparency */
//  BSP_LCD_SetTransparency(0, 0);
//  BSP_LCD_SetTransparency(1, 100);
}



/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 200000000
  *            HCLK(Hz)                       = 200000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 400
  *            PLL_P                          = 2
  *            PLL_Q                          = 8
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 6
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 200 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}
