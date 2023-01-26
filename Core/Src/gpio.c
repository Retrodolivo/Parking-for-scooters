/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

  /**/
  LL_GPIO_ResetOutputPin(GPIOC, LED_RED_1_Pin|LED_GREEN_1_Pin|LED_RED_2_Pin|LED_GREEN_2_Pin
                          |LED_RED_3_Pin|LED_GREEN_3_Pin|LED_RED_4_Pin|LED_GREEN_4_Pin
                          |LED_RED_5_Pin|LED_GREEN_5_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, SCAN_KEY_1_Pin|SCAN_KEY_2_Pin|LOCK_1_Pin|LOCK_2_Pin
                          |LOCK_3_Pin|LOCK_4_Pin|LOCK_5_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_ES_Pin
                          |LCD_RES_Pin|LCD_CS_Pin|CHARGE_EN_1_Pin|LCD_DB3_Pin
                          |LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin|LCD_DB7_Pin
                          |LCD_A0_Pin|LCD_R_W_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOD, CHARGE_EN_2_Pin|CHARGE_EN_3_Pin|CHARGE_EN_4_Pin|CHARGE_EN_5_Pin);

  /**/
  GPIO_InitStruct.Pin = LED_RED_1_Pin|LED_GREEN_1_Pin|LED_RED_2_Pin|LED_GREEN_2_Pin
                          |LED_RED_3_Pin|LED_GREEN_3_Pin|LED_RED_4_Pin|LED_GREEN_4_Pin
                          |LED_RED_5_Pin|LED_GREEN_5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SCAN_KEY_1_Pin|SCAN_KEY_2_Pin|LOCK_1_Pin|LOCK_2_Pin
                          |LOCK_3_Pin|LOCK_4_Pin|LOCK_5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = KEY_A_Pin|KEY_B_Pin|KEY_F_Pin|KEY_E_Pin
                          |KEY_D_Pin|KEY_C_Pin|KEY_G_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = IRQ_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(IRQ_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_ES_Pin
                          |LCD_RES_Pin|LCD_CS_Pin|LCD_DB3_Pin|LCD_DB4_Pin
                          |LCD_DB5_Pin|LCD_DB6_Pin|LCD_DB7_Pin|LCD_A0_Pin
                          |LCD_R_W_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = CHARGE_EN_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(CHARGE_EN_1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = CLOSE_COVER_IN_1_Pin|CURRENT_IN_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = CHARGE_EN_2_Pin|CHARGE_EN_3_Pin|CHARGE_EN_4_Pin|CHARGE_EN_5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = CLOSE_COVER_IN_2_Pin|CURRENT_IN_2_Pin|CLOSE_COVER_IN_3_Pin|CURRENT_IN_3_Pin
                          |CLOSE_COVER_IN_4_Pin|CURRENT_IN_4_Pin|CLOSE_COVER_IN_5_Pin|CURRENT_IN_5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SW_3_5CH_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(SW_3_5CH_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
