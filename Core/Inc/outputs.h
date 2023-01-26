#ifndef _OUTPUTS_H
#define _OUTPUTS_H

#include "main.h"

void setOutLedRedCh_1(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_RED_CH_1
void setOutLedGreenCh_1(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_GREEN_CH_1
void setOutLedRedCh_2(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_RED_CH_2
void setOutLedGreenCh_2(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_GREEN_CH_2
void setOutLedRedCh_3(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_RED_CH_3
void setOutLedGreenCh_3(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_GREEN_CH_3
void setOutLedRedCh_4(uint8_t setStateOut); 	// Изменить состояние выхода  OUT_LED_RED_CH_4
void setOutLedGreenCh_4(uint8_t setStateOut);	// Изменить состояние выхода  OUT_LED_GREEN_CH_4
void setOutLedRedCh_5(uint8_t setStateOut);		// Изменить состояние выхода  OUT_LED_RED_CH_5
void setOutLedGreenCh_5(uint8_t setStateOut);	// Изменить состояние выхода  OUT_LED_GREEN_CH_5
void setOutLockCh_1(uint8_t setStateOut);		// Изменить состояние выхода  OUT_LOCK_1
void setOutLockCh_2(uint8_t setStateOut);		// Изменить состояние выхода  OUT_LOCK_2
void setOutLockCh_3(uint8_t setStateOut);		// Изменить состояние выхода  OUT_LOCK_3
void setOutLockCh_4(uint8_t setStateOut);		// Изменить состояние выхода  OUT_LOCK_4
void setOutLockCh_5(uint8_t setStateOut);		// Изменить состояние выхода  OUT_LOCK_5
void setOutChargeCh_1(uint8_t setStateOut);		// Изменить состояние выхода  OUT_CHARGE_EN_CH_1
void setOutChargeCh_2(uint8_t setStateOut);		// Изменить состояние выхода  OUT_CHARGE_EN_CH_2
void setOutChargeCh_3(uint8_t setStateOut);		// Изменить состояние выхода  OUT_CHARGE_EN_CH_3
void setOutChargeCh_4(uint8_t setStateOut);		// Изменить состояние выхода  OUT_CHARGE_EN_CH_4
void setOutChargeCh_5(uint8_t setStateOut);		// Изменить состояние выхода  OUT_CHARGE_EN_CH_5

void outputsTask(void); // Одроботка выходов

#endif
