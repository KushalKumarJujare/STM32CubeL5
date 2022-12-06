/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    GTZC/GTZC_MPCWM_IllegalAccess_TrustZone/NonSecure/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for non-secure main.c module
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

#include "secure_nsc.h" /* For export Non-secure callable APIs */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_WAKEUP_Pin GPIO_PIN_13
#define BUTTON_WAKEUP_GPIO_Port GPIOC
#define BUTTON_WAKEUP_EXTI_IRQn EXTI13_IRQn
#define BUTTON_TAMPER_Pin GPIO_PIN_1
#define BUTTON_TAMPER_GPIO_Port GPIOA
#define BUTTON_TAMPER_EXTI_IRQn EXTI1_IRQn
#define LED4_Pin GPIO_PIN_3
#define LED4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LED5_Pin GPIO_PIN_3
#define LED5_GPIO_Port GPIOD

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
