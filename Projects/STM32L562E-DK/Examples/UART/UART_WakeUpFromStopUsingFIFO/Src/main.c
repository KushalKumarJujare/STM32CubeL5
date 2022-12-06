/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    UART/UART_WakeUpFromStopUsingFIFO/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use UART HAL API (UART instance)
  *          to wake up the MCU from STOP mode using the UART FIFO level.
  *          Two boards are used, one which enters STOP mode and the second
  *          one which sends the wake-up stimuli.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32l562e_discovery.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define HAL_TIMEOUT_VALUE 0xFFFFFFFF
#define countof(a) (sizeof(a) / sizeof(*(a)))
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t HeaderTxBuffer[] = "\r\nUSART1 WakeUp from stop mode using FIFO\r\n";
uint8_t Part1TxBuffer[] = "\r\n\t Part 1: RXFIFO threshold interrupt\r\n   Waiting for characters reception until RX FIFO threshold is reached\r\n   Please send 2 bytes\r\n";
uint8_t WakeupRXFTBuffer[] = "\r\n   Proper wakeup based on RXFIFO threshold interrupt detection.\r\n";
uint8_t Part2TxBuffer[] = "\r\n\t Part 2: RXFIFO full interrupt\r\n   Waiting for characters reception until RX FIFO is Full \r\n   Please send 8 bytes\r\n";
uint8_t WakeupRXFFBuffer[] = "\r\n   Proper wakeup based on RXFIFO full interrupt detection.\r\n";
uint8_t FooterTxBuffer[] = "\r\nExample finished successfully\r\n";

uint8_t RxBuffer[8];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ICACHE_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

void SystemClock_Config_fromSTOP(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* Initialize BSP LED */
  BSP_LED_Init(LED10);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ICACHE_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* Turn LED10 on */
  BSP_LED_On(LED10);

  /* Specify HSI as the clock source used after wake up from stop mode */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);

  /*##########################################################################*/
  /*##-1- Wakeup first step RXFT #############################################*/
  /*##########################################################################*/

  /* Output message on hyperterminal */
  HAL_UART_Transmit(&huart1, (uint8_t*)&HeaderTxBuffer, countof(HeaderTxBuffer)-1, HAL_TIMEOUT_VALUE);

  /* Enable MCU wakeup by USART1 */
  HAL_UARTEx_EnableStopMode(&huart1);

  /* Enable the USART1 RX FIFO threshold interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXFT);

  /* Enable the USART1 wakeup from stop mode interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_WUF);

  /* Output message on hyperterminal */
  HAL_UART_Transmit(&huart1, (uint8_t*)&Part1TxBuffer, countof(Part1TxBuffer)-1, HAL_TIMEOUT_VALUE);

  /* Put USART1 peripheral in reception process */
  HAL_UART_Receive_IT(&huart1, (uint8_t*)&RxBuffer, 2);

  /* Turn LED10 off */
  BSP_LED_Off(LED10);

  /* Enter STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON,PWR_STOPENTRY_WFI);

  /* ... STOP Mode ... */

  /* Call SystemClock_Config for the wake up from stop clock */
  SystemClock_Config_fromSTOP();

  /* Turn LED10 on */
  BSP_LED_On(LED10);


  while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)
  {
  }

  /* Disable the USART1 wakeup from stop mode interrupt */
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_WUF);

  /* Disable the USART1 RX FIFO threshold interrupt */
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_RXFT);

  /* Disable USART1 Stop Mode */
  HAL_UARTEx_DisableStopMode(&huart1);

  /* Output message on hyperterminal */
  HAL_UART_Transmit(&huart1, (uint8_t*)&WakeupRXFTBuffer, countof(WakeupRXFTBuffer)-1, HAL_TIMEOUT_VALUE);

  /*##########################################################################*/
  /*##-2- Wakeup second step RXFF ############################################*/
  /*##########################################################################*/

  /* Update Rx FIFO threshold */
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_8_8) != HAL_OK)
  {
    Error_Handler();
  }

  /* Enable MCU wakeup by USART1 */
  HAL_UARTEx_EnableStopMode(&huart1);

  /* Enable the USART1 RX FIFO full interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXFF);

  /* Enable the USART1 wakeup from stop mode interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_WUF);

  /* Output message on hyperterminal */
  HAL_UART_Transmit(&huart1, (uint8_t*)&Part2TxBuffer, countof(Part2TxBuffer)-1, HAL_TIMEOUT_VALUE);

  /* Put USART1 peripheral in reception process */
  HAL_UART_Receive_IT(&huart1, (uint8_t*)&RxBuffer, 8);

  /* Turn LED10 off */
  BSP_LED_Off(LED10);

  /* Enter STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON,PWR_STOPENTRY_WFI);

  /* ... STOP Mode ... */

  /* Turn LED10 on */
  BSP_LED_On(LED10);
  
  /* Call SystemClock_Config for the wake up from stop clock */
  SystemClock_Config_fromSTOP();

  while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)
  {
  }

  /* Disable the USART1 wakeup from stop mode interrupt */
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_WUF);

  /* Disable the USART1 RX FIFO full interrupt */
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_RXFF);

  /* Disable USART1 Stop Mode */
  HAL_UARTEx_DisableStopMode(&huart1);

  /* Output message on hyperterminal */
  HAL_UART_Transmit(&huart1, (uint8_t*)&WakeupRXFFBuffer, countof(WakeupRXFFBuffer)-1, HAL_TIMEOUT_VALUE);

  /*##########################################################################*/
  /*##-3- Successful test ####################################################*/
  /*##########################################################################*/

  /* Output message on hyperterminal */
  HAL_UART_Transmit(&huart1, (uint8_t*)&FooterTxBuffer, countof(FooterTxBuffer)-1, HAL_TIMEOUT_VALUE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 55;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_ODD;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_EnableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void SystemClock_Config_fromSTOP(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  uint32_t pFLatency = 0;
  /* Get the Oscillators configuration from the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);
  /* Wake up on HSI, re-enable PLL with HSI as source */
  /* Oscillator configuration unchanged */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* Get the clock prescalers configuration from the internal RCC registers */
  HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &pFLatency);
  /* Select PLL as system clock source */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, pFLatency) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while (1)
  {
    /* In case of error, LED10 transmits a sequence of three dots, three dashes, three dots */
    BSP_LED_On(LED10);
    HAL_Delay(300);
    BSP_LED_Off(LED10);
    HAL_Delay(300);
    BSP_LED_On(LED10);
    HAL_Delay(300);
    BSP_LED_Off(LED10);
    HAL_Delay(300);
    BSP_LED_On(LED10);
    HAL_Delay(300);
    BSP_LED_Off(LED10);
    HAL_Delay(300);
    BSP_LED_On(LED10);
    HAL_Delay(700);
    BSP_LED_Off(LED10);
    HAL_Delay(700);
    BSP_LED_On(LED10);
    HAL_Delay(700);
    BSP_LED_Off(LED10);
    HAL_Delay(700);
    BSP_LED_On(LED10);
    HAL_Delay(700);
    BSP_LED_Off(LED10);
    HAL_Delay(700);
    BSP_LED_On(LED10);
    HAL_Delay(300);
    BSP_LED_Off(LED10);
    HAL_Delay(300);
    BSP_LED_On(LED10);
    HAL_Delay(300);
    BSP_LED_Off(LED10);
    HAL_Delay(300);
    BSP_LED_On(LED10);
    HAL_Delay(300);
    BSP_LED_Off(LED10);
    HAL_Delay(800);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {}
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
