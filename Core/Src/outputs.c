#include "outputs.h"

static uint32_t regOutputs = 0;

enum RegOutputsEnum{
	OUT_LED_RED_CH_1 = 0,
	OUT_LED_GREEN_CH_1,
	OUT_LED_RED_CH_2,
	OUT_LED_GREEN_CH_2,
	OUT_LED_RED_CH_3,
	OUT_LED_GREEN_CH_3,
	OUT_LED_RED_CH_4,
	OUT_LED_GREEN_CH_4,
	OUT_LED_RED_CH_5,
	OUT_LED_GREEN_CH_5,
	OUT_LOCK_1,
	OUT_LOCK_2,
	OUT_LOCK_3,
	OUT_LOCK_4,
	OUT_LOCK_5,
	OUT_CHARGE_EN_CH_1,
	OUT_CHARGE_EN_CH_2,
	OUT_CHARGE_EN_CH_3,
	OUT_CHARGE_EN_CH_4,
	OUT_CHARGE_EN_CH_5
};

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_RED_CH_1                      *
 *********************************************************************/
void setOutLedRedCh_1(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_RED_CH_1);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_RED_CH_1);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_GREEN_CH_1                    *
 *********************************************************************/
void setOutLedGreenCh_1(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_GREEN_CH_1);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_GREEN_CH_1);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_RED_CH_2                      *
 *********************************************************************/
void setOutLedRedCh_2(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_RED_CH_2);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_RED_CH_2);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_GREEN_CH_2                    *
 *********************************************************************/
void setOutLedGreenCh_2(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_GREEN_CH_2);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_GREEN_CH_2);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_RED_CH_3                      *
 *********************************************************************/
void setOutLedRedCh_3(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_RED_CH_3);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_RED_CH_3);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_GREEN_CH_3                    *
 *********************************************************************/
void setOutLedGreenCh_3(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_GREEN_CH_3);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_GREEN_CH_3);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_RED_CH_4                      *
 *********************************************************************/
void setOutLedRedCh_4(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_RED_CH_4);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_RED_CH_4);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_GREEN_CH_4                    *
 *********************************************************************/
void setOutLedGreenCh_4(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_GREEN_CH_4);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_GREEN_CH_4);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_RED_CH_5                      *
 *********************************************************************/
void setOutLedRedCh_5(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_RED_CH_5);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_RED_CH_5);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LED_GREEN_CH_5                    *
 *********************************************************************/
void setOutLedGreenCh_5(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LED_GREEN_CH_5);
	}
	else
	{
		BitSet(regOutputs, OUT_LED_GREEN_CH_5);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LOCK_1                            *
 *********************************************************************/
void setOutLockCh_1(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LOCK_1);
	}
	else
	{
		BitSet(regOutputs, OUT_LOCK_1);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LOCK_2                            *
 *********************************************************************/
void setOutLockCh_2(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LOCK_2);
	}
	else
	{
		BitSet(regOutputs, OUT_LOCK_2);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LOCK_3                            *
 *********************************************************************/
void setOutLockCh_3(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LOCK_3);
	}
	else
	{
		BitSet(regOutputs, OUT_LOCK_3);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LOCK_4                            *
 *********************************************************************/
void setOutLockCh_4(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LOCK_4);
	}
	else
	{
		BitSet(regOutputs, OUT_LOCK_4);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_LOCK_5                            *
 *********************************************************************/
void setOutLockCh_5(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_LOCK_5);
	}
	else
	{
		BitSet(regOutputs, OUT_LOCK_5);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_CHARGE_EN_CH_1                    *
 *********************************************************************/
void setOutChargeCh_1(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_CHARGE_EN_CH_1);
	}
	else
	{
		BitSet(regOutputs, OUT_CHARGE_EN_CH_1);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_CHARGE_EN_CH_2                    *
 *********************************************************************/
void setOutChargeCh_2(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_CHARGE_EN_CH_2);
	}
	else
	{
		BitSet(regOutputs, OUT_CHARGE_EN_CH_2);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_CHARGE_EN_CH_3                    *
 *********************************************************************/
void setOutChargeCh_3(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_CHARGE_EN_CH_3);
	}
	else
	{
		BitSet(regOutputs, OUT_CHARGE_EN_CH_3);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_CHARGE_EN_CH_4                    *
 *********************************************************************/
void setOutChargeCh_4(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_CHARGE_EN_CH_4);
	}
	else
	{
		BitSet(regOutputs, OUT_CHARGE_EN_CH_4);
	}
}

/*********************************************************************
 * Изменить состояние выххода  OUT_CHARGE_EN_CH_5                    *
 *********************************************************************/
void setOutChargeCh_5(uint8_t setStateOut)
{
	if(setStateOut == FALSE)
	{
		BitCtr(regOutputs, OUT_CHARGE_EN_CH_5);
	}
	else
	{
		BitSet(regOutputs, OUT_CHARGE_EN_CH_5);
	}
}

/*********************************************************************
 * Обработка выходов                                                 *
 *********************************************************************/
void outputsTask(void)
{
	/*if(BitStatus(regOutputs, OUT_LED_RED_CH_1) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
	}
	if(BitStatus(regOutputs, OUT_LED_GREEN_CH_1) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
	}

	if(BitStatus(regOutputs, OUT_LED_RED_CH_2) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
	}
	if(BitStatus(regOutputs, OUT_LED_GREEN_CH_2) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
	}

	if(BitStatus(regOutputs, OUT_LED_RED_CH_3) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_RED_3_GPIO_Port, LED_RED_3_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_RED_3_GPIO_Port, LED_RED_3_Pin);
	}
	if(BitStatus(regOutputs, OUT_LED_GREEN_CH_3) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin);
	}

	if(BitStatus(regOutputs, OUT_LED_RED_CH_4) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_RED_4_GPIO_Port, LED_RED_4_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_RED_4_GPIO_Port, LED_RED_4_Pin);
	}
	if(BitStatus(regOutputs, OUT_LED_GREEN_CH_4) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin);
	}

	if(BitStatus(regOutputs, OUT_LED_RED_CH_5) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_RED_5_GPIO_Port, LED_RED_5_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_RED_5_GPIO_Port, LED_RED_5_Pin);
	}
	if(BitStatus(regOutputs, OUT_LED_GREEN_CH_5) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LED_GREEN_5_GPIO_Port, LED_GREEN_5_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LED_GREEN_5_GPIO_Port, LED_GREEN_5_Pin);
	}*/

	if(BitStatus(regOutputs, OUT_LOCK_1) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LOCK_1_GPIO_Port, LOCK_1_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LOCK_1_GPIO_Port, LOCK_1_Pin);
	}

	if(BitStatus(regOutputs, OUT_LOCK_2) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LOCK_2_GPIO_Port, LOCK_2_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LOCK_2_GPIO_Port, LOCK_2_Pin);
	}

	if(BitStatus(regOutputs, OUT_LOCK_3) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LOCK_3_GPIO_Port, LOCK_3_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LOCK_3_GPIO_Port, LOCK_3_Pin);
	}

	if(BitStatus(regOutputs, OUT_LOCK_4) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LOCK_4_GPIO_Port, LOCK_4_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LOCK_4_GPIO_Port, LOCK_4_Pin);
	}

	if(BitStatus(regOutputs, OUT_LOCK_5) == FALSE)
	{
		LL_GPIO_ResetOutputPin(LOCK_5_GPIO_Port, LOCK_5_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(LOCK_5_GPIO_Port, LOCK_5_Pin);
	}

	if(BitStatus(regOutputs, OUT_CHARGE_EN_CH_1) == FALSE)
	{
		LL_GPIO_ResetOutputPin(CHARGE_EN_1_GPIO_Port, CHARGE_EN_1_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(CHARGE_EN_1_GPIO_Port, CHARGE_EN_1_Pin);
	}

	if(BitStatus(regOutputs, OUT_CHARGE_EN_CH_2) == FALSE)
	{
		LL_GPIO_ResetOutputPin(CHARGE_EN_2_GPIO_Port, CHARGE_EN_2_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(CHARGE_EN_2_GPIO_Port, CHARGE_EN_2_Pin);
	}

	if(BitStatus(regOutputs, OUT_CHARGE_EN_CH_3) == FALSE)
	{
		LL_GPIO_ResetOutputPin(CHARGE_EN_3_GPIO_Port, CHARGE_EN_3_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(CHARGE_EN_3_GPIO_Port, CHARGE_EN_3_Pin);
	}

	if(BitStatus(regOutputs, OUT_CHARGE_EN_CH_4) == FALSE)
	{
		LL_GPIO_ResetOutputPin(CHARGE_EN_4_GPIO_Port, CHARGE_EN_4_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(CHARGE_EN_4_GPIO_Port, CHARGE_EN_4_Pin);
	}

	if(BitStatus(regOutputs, OUT_CHARGE_EN_CH_5) == FALSE)
	{
		LL_GPIO_ResetOutputPin(CHARGE_EN_5_GPIO_Port, CHARGE_EN_5_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(CHARGE_EN_5_GPIO_Port, CHARGE_EN_5_Pin);
	}
}
