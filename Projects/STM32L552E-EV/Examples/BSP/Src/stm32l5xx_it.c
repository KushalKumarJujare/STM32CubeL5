/**
  ******************************************************************************
  * @file    stm32l5xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"
#include "stm32l5xx_it.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M33 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32L5xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l5xx.s).                                               */
/******************************************************************************/

void EXTI0_IRQHandler(void)
{
  BSP_JOY_IRQHandler(JOY1, JOY_ALL);
}

void EXTI10_IRQHandler(void)
{
  BSP_SD_DETECT_IRQHandler(0);
}

void EXTI13_IRQHandler(void)
{
  BSP_PB_IRQHandler(BUTTON_WAKEUP);
}

void EXTI15_IRQHandler(void)
{
  BSP_TS_IRQHandler(0);
}

void DMA1_Channel1_IRQHandler(void)
{
  BSP_SRAM_DMA_IRQHandler(0);
}

void DMA1_Channel2_IRQHandler(void)
{
  BSP_OSPI_RAM_DMA_IRQHandler(0);
}

void DMA1_Channel4_IRQHandler(void)
{ 
  BSP_AUDIO_IN_IRQHandler(1, AUDIO_IN_DIGITAL_MIC1);
}

void DMA1_Channel5_IRQHandler(void)
{ 
  BSP_AUDIO_IN_IRQHandler(1, AUDIO_IN_DIGITAL_MIC2);
}

void DMA2_Channel1_IRQHandler(void)
{ 
  BSP_AUDIO_OUT_IRQHandler(0, AUDIO_OUT_HEADPHONE);
}

void SDMMC1_IRQHandler(void)
{
  BSP_SD_IRQHandler(0);
}

void OCTOSPI1_IRQHandler(void)
{
  BSP_OSPI_RAM_IRQHandler(0);
}
