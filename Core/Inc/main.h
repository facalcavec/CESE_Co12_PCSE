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
#include "_miBoolean.h"
#include "_eeprom.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
I2C_HandleTypeDef hi2c1;
RTC_HandleTypeDef hrtc;

RTC_TimeTypeDef sTime1;
RTC_DateTypeDef sDate1;

bool_t flagReportes;
bool_t flagPausa;
bool_t flagConfiguracion;

uint16_t lastReport;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

//#define ADD_CONT	1			// direccion del contador de reportes
#define INI_BLOCK_REPORTER 32	// direccion del primer bloque de memoria de los reportes

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void teclado( void );

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ESCAPE_Pin GPIO_PIN_8
#define ESCAPE_GPIO_Port GPIOA
#define ENTER_Pin GPIO_PIN_9
#define ENTER_GPIO_Port GPIOA
#define DOWN_Pin GPIO_PIN_10
#define DOWN_GPIO_Port GPIOA
#define UP_Pin GPIO_PIN_11
#define UP_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
