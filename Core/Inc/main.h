/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bitOperations.h"
#include "gTimers.h"
#include "flashMemory.h"
#include "flashEEPROM.h"
#include "startUpSystem.h"
#include "PN532.h"
#include "mt12232d.h"
#include "keyboard.h"
#include "tasks.h"
#include "inputs.h"
#include "outputs.h"
#include "taskMainRun.h"
#include "lcd.h"
#include "nfc.h"
#include "lockControl.h"
#include "ledControl.h"
#include "chargeControl.h"
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
#define LED_RED_1_Pin LL_GPIO_PIN_0
#define LED_RED_1_GPIO_Port GPIOC
#define LED_GREEN_1_Pin LL_GPIO_PIN_1
#define LED_GREEN_1_GPIO_Port GPIOC
#define LED_RED_2_Pin LL_GPIO_PIN_2
#define LED_RED_2_GPIO_Port GPIOC
#define LED_GREEN_2_Pin LL_GPIO_PIN_3
#define LED_GREEN_2_GPIO_Port GPIOC
#define SCAN_KEY_1_Pin LL_GPIO_PIN_0
#define SCAN_KEY_1_GPIO_Port GPIOA
#define SCAN_KEY_2_Pin LL_GPIO_PIN_1
#define SCAN_KEY_2_GPIO_Port GPIOA
#define KEY_A_Pin LL_GPIO_PIN_2
#define KEY_A_GPIO_Port GPIOA
#define KEY_B_Pin LL_GPIO_PIN_3
#define KEY_B_GPIO_Port GPIOA
#define IRQ_Pin LL_GPIO_PIN_4
#define IRQ_GPIO_Port GPIOF
#define KEY_F_Pin LL_GPIO_PIN_4
#define KEY_F_GPIO_Port GPIOA
#define KEY_E_Pin LL_GPIO_PIN_5
#define KEY_E_GPIO_Port GPIOA
#define KEY_D_Pin LL_GPIO_PIN_6
#define KEY_D_GPIO_Port GPIOA
#define KEY_C_Pin LL_GPIO_PIN_7
#define KEY_C_GPIO_Port GPIOA
#define LED_RED_3_Pin LL_GPIO_PIN_4
#define LED_RED_3_GPIO_Port GPIOC
#define LED_GREEN_3_Pin LL_GPIO_PIN_5
#define LED_GREEN_3_GPIO_Port GPIOC
#define LCD_DB0_Pin LL_GPIO_PIN_0
#define LCD_DB0_GPIO_Port GPIOB
#define LCD_DB1_Pin LL_GPIO_PIN_1
#define LCD_DB1_GPIO_Port GPIOB
#define LCD_DB2_Pin LL_GPIO_PIN_2
#define LCD_DB2_GPIO_Port GPIOB
#define LCD_ES_Pin LL_GPIO_PIN_10
#define LCD_ES_GPIO_Port GPIOB
#define LCD_RES_Pin LL_GPIO_PIN_11
#define LCD_RES_GPIO_Port GPIOB
#define LCD_CS_Pin LL_GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB
#define CHARGE_EN_1_Pin LL_GPIO_PIN_13
#define CHARGE_EN_1_GPIO_Port GPIOB
#define CLOSE_COVER_IN_1_Pin LL_GPIO_PIN_14
#define CLOSE_COVER_IN_1_GPIO_Port GPIOB
#define CURRENT_IN_1_Pin LL_GPIO_PIN_15
#define CURRENT_IN_1_GPIO_Port GPIOB
#define CHARGE_EN_2_Pin LL_GPIO_PIN_8
#define CHARGE_EN_2_GPIO_Port GPIOD
#define CLOSE_COVER_IN_2_Pin LL_GPIO_PIN_9
#define CLOSE_COVER_IN_2_GPIO_Port GPIOD
#define CURRENT_IN_2_Pin LL_GPIO_PIN_10
#define CURRENT_IN_2_GPIO_Port GPIOD
#define CHARGE_EN_3_Pin LL_GPIO_PIN_11
#define CHARGE_EN_3_GPIO_Port GPIOD
#define CLOSE_COVER_IN_3_Pin LL_GPIO_PIN_12
#define CLOSE_COVER_IN_3_GPIO_Port GPIOD
#define CURRENT_IN_3_Pin LL_GPIO_PIN_13
#define CURRENT_IN_3_GPIO_Port GPIOD
#define LED_RED_4_Pin LL_GPIO_PIN_6
#define LED_RED_4_GPIO_Port GPIOC
#define LED_GREEN_4_Pin LL_GPIO_PIN_7
#define LED_GREEN_4_GPIO_Port GPIOC
#define LED_RED_5_Pin LL_GPIO_PIN_8
#define LED_RED_5_GPIO_Port GPIOC
#define LED_GREEN_5_Pin LL_GPIO_PIN_9
#define LED_GREEN_5_GPIO_Port GPIOC
#define KEY_G_Pin LL_GPIO_PIN_8
#define KEY_G_GPIO_Port GPIOA
#define LOCK_1_Pin LL_GPIO_PIN_9
#define LOCK_1_GPIO_Port GPIOA
#define LOCK_2_Pin LL_GPIO_PIN_10
#define LOCK_2_GPIO_Port GPIOA
#define LOCK_3_Pin LL_GPIO_PIN_11
#define LOCK_3_GPIO_Port GPIOA
#define LOCK_4_Pin LL_GPIO_PIN_12
#define LOCK_4_GPIO_Port GPIOA
#define LOCK_5_Pin LL_GPIO_PIN_15
#define LOCK_5_GPIO_Port GPIOA
#define CHARGE_EN_4_Pin LL_GPIO_PIN_0
#define CHARGE_EN_4_GPIO_Port GPIOD
#define CLOSE_COVER_IN_4_Pin LL_GPIO_PIN_1
#define CLOSE_COVER_IN_4_GPIO_Port GPIOD
#define CURRENT_IN_4_Pin LL_GPIO_PIN_2
#define CURRENT_IN_4_GPIO_Port GPIOD
#define CHARGE_EN_5_Pin LL_GPIO_PIN_3
#define CHARGE_EN_5_GPIO_Port GPIOD
#define CLOSE_COVER_IN_5_Pin LL_GPIO_PIN_4
#define CLOSE_COVER_IN_5_GPIO_Port GPIOD
#define CURRENT_IN_5_Pin LL_GPIO_PIN_5
#define CURRENT_IN_5_GPIO_Port GPIOD
#define SW_3_5CH_Pin LL_GPIO_PIN_6
#define SW_3_5CH_GPIO_Port GPIOD
#define LCD_DB3_Pin LL_GPIO_PIN_3
#define LCD_DB3_GPIO_Port GPIOB
#define LCD_DB4_Pin LL_GPIO_PIN_4
#define LCD_DB4_GPIO_Port GPIOB
#define LCD_DB5_Pin LL_GPIO_PIN_5
#define LCD_DB5_GPIO_Port GPIOB
#define LCD_DB6_Pin LL_GPIO_PIN_6
#define LCD_DB6_GPIO_Port GPIOB
#define LCD_DB7_Pin LL_GPIO_PIN_7
#define LCD_DB7_GPIO_Port GPIOB
#define LCD_A0_Pin LL_GPIO_PIN_8
#define LCD_A0_GPIO_Port GPIOB
#define LCD_R_W_Pin LL_GPIO_PIN_9
#define LCD_R_W_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
