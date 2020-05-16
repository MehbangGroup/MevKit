/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOD
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOD
#define POT3_Pin GPIO_PIN_0
#define POT3_GPIO_Port GPIOA
#define POT2_Pin GPIO_PIN_1
#define POT2_GPIO_Port GPIOA
#define POT1_Pin GPIO_PIN_5
#define POT1_GPIO_Port GPIOA
#define Temp_Pin GPIO_PIN_6
#define Temp_GPIO_Port GPIOA
#define PWMG_Pin GPIO_PIN_7
#define PWMG_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_0
#define PWMB_GPIO_Port GPIOB
#define PWMR_Pin GPIO_PIN_1
#define PWMR_GPIO_Port GPIOB
#define CSN_Pin GPIO_PIN_12
#define CSN_GPIO_Port GPIOB
#define SCK_Pin GPIO_PIN_13
#define SCK_GPIO_Port GPIOB
#define MISO_Pin GPIO_PIN_14
#define MISO_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_15
#define MOSI_GPIO_Port GPIOB
#define CE_Pin GPIO_PIN_8
#define CE_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LD5_Pin GPIO_PIN_15
#define LD5_GPIO_Port GPIOA
#define LD6_Pin GPIO_PIN_3
#define LD6_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_5
#define SW1_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_6
#define SW2_GPIO_Port GPIOB
#define LAT_Pin GPIO_PIN_7
#define LAT_GPIO_Port GPIOB
#define CLK_Pin GPIO_PIN_8
#define CLK_GPIO_Port GPIOB
#define SDI_Pin GPIO_PIN_9
#define SDI_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
