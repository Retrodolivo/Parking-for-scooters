#include "keyboard.h"

keyPresedEnum_t keyPresed = UNKOW_KEY;

typedef struct ButtonsReg{
	uint32_t regFlagsStateKey;
	uint32_t regPrevStateKey;
	uint8_t countKey[14];
}buttonReg_t;

static buttonReg_t buttonReg = {0, 0, {0}};

/*********************************************************************
 * Получить значение нажатой кнопки клавиатуры                       *
 *********************************************************************/
uint32_t getPresedAllKeys(void)
{
	return buttonReg.regFlagsStateKey;
}

/*********************************************************************
 * Получмть какая кнопка нажата                                      *
 *********************************************************************/
keyPresedEnum_t getPresetKey(void)
{
	return keyPresed;
}

/*********************************************************************
 * Опрос клавиатуры                                                  *
 *********************************************************************/
void keyboardTask(void)
{
	if(getGTimer(TIMER_READ_KEY).state == TIMER_STOPED && getGTimer(TIMER_READ_KEY).stateFlag == fFalse)
	{
		startGTimer(TIMER_READ_KEY, TIME_READ_KEY_MS);
	}
	if(getGTimer(TIMER_READ_KEY).stateFlag == fTrue)
	{
		startGTimer(TIMER_READ_KEY, TIME_READ_KEY_MS);
		LL_GPIO_SetOutputPin(SCAN_KEY_1_GPIO_Port, SCAN_KEY_1_Pin);
		LL_GPIO_ResetOutputPin(SCAN_KEY_2_GPIO_Port, SCAN_KEY_2_Pin);
		__NOP();
		if(LL_GPIO_IsInputPinSet(KEY_A_GPIO_Port, KEY_A_Pin) && BitStatus(buttonReg.regPrevStateKey, RIGHT_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, RIGHT_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_A_GPIO_Port, KEY_A_Pin) && BitStatus(buttonReg.regPrevStateKey, RIGHT_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, RIGHT_KEY) == FALSE)
		{
			buttonReg.countKey[RIGHT_KEY]++;
			if(buttonReg.countKey[RIGHT_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[RIGHT_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, RIGHT_KEY);
				keyPresed = RIGHT_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_A_GPIO_Port, KEY_A_Pin))
		{
			buttonReg.countKey[RIGHT_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, RIGHT_KEY);
			BitCtr(buttonReg.regFlagsStateKey, RIGHT_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_B_GPIO_Port, KEY_B_Pin) && BitStatus(buttonReg.regPrevStateKey, SIX_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, SIX_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_B_GPIO_Port, KEY_B_Pin) && BitStatus(buttonReg.regPrevStateKey, SIX_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, SIX_KEY) == FALSE)
		{
			buttonReg.countKey[SIX_KEY]++;
			if(buttonReg.countKey[SIX_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[SIX_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, SIX_KEY);
				keyPresed = SIX_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_B_GPIO_Port, KEY_B_Pin))
		{
			buttonReg.countKey[SIX_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, SIX_KEY);
			BitCtr(buttonReg.regFlagsStateKey, SIX_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_C_GPIO_Port, KEY_C_Pin) && BitStatus(buttonReg.regPrevStateKey, FIVE_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, FIVE_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_C_GPIO_Port, KEY_C_Pin) && BitStatus(buttonReg.regPrevStateKey, FIVE_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, FIVE_KEY) == FALSE)
		{
			buttonReg.countKey[FIVE_KEY]++;
			if(buttonReg.countKey[FIVE_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[FIVE_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, FIVE_KEY);
				keyPresed = FIVE_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_C_GPIO_Port, KEY_C_Pin))
		{
			buttonReg.countKey[FIVE_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, FIVE_KEY);
			BitCtr(buttonReg.regFlagsStateKey, FIVE_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_D_GPIO_Port, KEY_D_Pin) && BitStatus(buttonReg.regPrevStateKey, FOUR_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, FOUR_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_D_GPIO_Port, KEY_D_Pin) && BitStatus(buttonReg.regPrevStateKey, FOUR_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, FOUR_KEY) == FALSE)
		{
			buttonReg.countKey[FOUR_KEY]++;
			if(buttonReg.countKey[FOUR_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[FOUR_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, FOUR_KEY);
				keyPresed = FOUR_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_D_GPIO_Port, KEY_D_Pin))
		{
			buttonReg.countKey[FOUR_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, FOUR_KEY);
			BitCtr(buttonReg.regFlagsStateKey, FOUR_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_E_GPIO_Port, KEY_E_Pin) && BitStatus(buttonReg.regPrevStateKey, ONE_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, ONE_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_E_GPIO_Port, KEY_E_Pin) && BitStatus(buttonReg.regPrevStateKey, ONE_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, ONE_KEY) == FALSE)
		{
			buttonReg.countKey[ONE_KEY]++;
			if(buttonReg.countKey[ONE_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[ONE_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, ONE_KEY);
				keyPresed = ONE_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_E_GPIO_Port, KEY_E_Pin))
		{
			buttonReg.countKey[ONE_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, ONE_KEY);
			BitCtr(buttonReg.regFlagsStateKey, ONE_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_F_GPIO_Port, KEY_F_Pin) && BitStatus(buttonReg.regPrevStateKey, TWO_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, TWO_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_F_GPIO_Port, KEY_F_Pin) && BitStatus(buttonReg.regPrevStateKey, TWO_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, TWO_KEY) == FALSE)
		{
			buttonReg.countKey[TWO_KEY]++;
			if(buttonReg.countKey[TWO_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[TWO_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, TWO_KEY);
				keyPresed = TWO_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_F_GPIO_Port, KEY_F_Pin))
		{
			buttonReg.countKey[TWO_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, TWO_KEY);
			BitCtr(buttonReg.regFlagsStateKey, TWO_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_G_GPIO_Port, KEY_G_Pin) && BitStatus(buttonReg.regPrevStateKey, THREE_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, THREE_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_G_GPIO_Port, KEY_G_Pin) && BitStatus(buttonReg.regPrevStateKey, THREE_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, THREE_KEY) == FALSE)
		{
			buttonReg.countKey[THREE_KEY]++;
			if(buttonReg.countKey[THREE_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[THREE_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, THREE_KEY);
				keyPresed = THREE_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_G_GPIO_Port, KEY_G_Pin))
		{
			buttonReg.countKey[THREE_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, THREE_KEY);
			BitCtr(buttonReg.regFlagsStateKey, THREE_KEY);
		}

		LL_GPIO_ResetOutputPin(SCAN_KEY_1_GPIO_Port, SCAN_KEY_1_Pin);
		LL_GPIO_SetOutputPin(SCAN_KEY_2_GPIO_Port, SCAN_KEY_2_Pin);
		__NOP();

		if(LL_GPIO_IsInputPinSet(KEY_A_GPIO_Port, KEY_A_Pin) && BitStatus(buttonReg.regPrevStateKey, LEFT_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, LEFT_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_A_GPIO_Port, KEY_A_Pin) && BitStatus(buttonReg.regPrevStateKey, LEFT_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, LEFT_KEY) == FALSE)
		{
			buttonReg.countKey[LEFT_KEY]++;
			if(buttonReg.countKey[LEFT_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[LEFT_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, LEFT_KEY);
				keyPresed = LEFT_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_A_GPIO_Port, KEY_A_Pin))
		{
			buttonReg.countKey[LEFT_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, LEFT_KEY);
			BitCtr(buttonReg.regFlagsStateKey, LEFT_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_B_GPIO_Port, KEY_B_Pin) && BitStatus(buttonReg.regPrevStateKey, ENTER_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, ENTER_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_B_GPIO_Port, KEY_B_Pin) && BitStatus(buttonReg.regPrevStateKey, ENTER_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, ENTER_KEY) == FALSE)
		{
			buttonReg.countKey[ENTER_KEY]++;
			if(buttonReg.countKey[ENTER_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[ENTER_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, ENTER_KEY);
				keyPresed = ENTER_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_B_GPIO_Port, KEY_B_Pin))
		{
			buttonReg.countKey[ENTER_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, ENTER_KEY);
			BitCtr(buttonReg.regFlagsStateKey, ENTER_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_C_GPIO_Port, KEY_C_Pin) && BitStatus(buttonReg.regPrevStateKey, ZERO_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, ZERO_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_C_GPIO_Port, KEY_C_Pin) && BitStatus(buttonReg.regPrevStateKey, ZERO_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, ZERO_KEY) == FALSE)
		{
			buttonReg.countKey[ZERO_KEY]++;
			if(buttonReg.countKey[ZERO_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[ZERO_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, ZERO_KEY);
				keyPresed = ZERO_KEY;
			}
		}
		if(!LL_GPIO_IsInputPinSet(KEY_C_GPIO_Port, KEY_C_Pin))
		{
			buttonReg.countKey[ZERO_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, ZERO_KEY);
			BitCtr(buttonReg.regFlagsStateKey, ZERO_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_D_GPIO_Port, KEY_D_Pin) && BitStatus(buttonReg.regPrevStateKey, CLEAR_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, CLEAR_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_D_GPIO_Port, KEY_D_Pin) && BitStatus(buttonReg.regPrevStateKey, CLEAR_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, CLEAR_KEY) == FALSE)
		{
			buttonReg.countKey[CLEAR_KEY]++;
			if(buttonReg.countKey[CLEAR_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[CLEAR_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, CLEAR_KEY);
				keyPresed = CLEAR_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_D_GPIO_Port, KEY_D_Pin))
		{
			buttonReg.countKey[CLEAR_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, CLEAR_KEY);
			BitCtr(buttonReg.regFlagsStateKey, CLEAR_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_E_GPIO_Port, KEY_E_Pin) && BitStatus(buttonReg.regPrevStateKey, SEVEN_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, SEVEN_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_E_GPIO_Port, KEY_E_Pin) && BitStatus(buttonReg.regPrevStateKey, SEVEN_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, SEVEN_KEY) == FALSE)
		{
			buttonReg.countKey[SEVEN_KEY]++;
			if(buttonReg.countKey[SEVEN_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[SEVEN_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, SEVEN_KEY);
				keyPresed = SEVEN_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_E_GPIO_Port, KEY_E_Pin))
		{
			buttonReg.countKey[SEVEN_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, SEVEN_KEY);
			BitCtr(buttonReg.regFlagsStateKey, SEVEN_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_F_GPIO_Port, KEY_F_Pin) && BitStatus(buttonReg.regPrevStateKey, EIGHT_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, EIGHT_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_F_GPIO_Port, KEY_F_Pin) && BitStatus(buttonReg.regPrevStateKey, EIGHT_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, EIGHT_KEY) == FALSE)
		{
			buttonReg.countKey[EIGHT_KEY]++;
			if(buttonReg.countKey[EIGHT_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[EIGHT_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, EIGHT_KEY);
				keyPresed = EIGHT_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_F_GPIO_Port, KEY_F_Pin))
		{
			buttonReg.countKey[EIGHT_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, EIGHT_KEY);
			BitCtr(buttonReg.regFlagsStateKey, EIGHT_KEY);
		}

		if(LL_GPIO_IsInputPinSet(KEY_G_GPIO_Port, KEY_G_Pin) && BitStatus(buttonReg.regPrevStateKey, NINE_KEY) == FALSE)
		{
			BitSet(buttonReg.regPrevStateKey, NINE_KEY);
		}
		else if(LL_GPIO_IsInputPinSet(KEY_G_GPIO_Port, KEY_G_Pin) && BitStatus(buttonReg.regPrevStateKey, NINE_KEY) != FALSE && BitStatus(buttonReg.regFlagsStateKey, NINE_KEY) == FALSE)
		{
			buttonReg.countKey[NINE_KEY]++;
			if(buttonReg.countKey[NINE_KEY] >= MAX_COUNT_BUTTONS)
			{
				buttonReg.countKey[NINE_KEY] = 0;
				BitSet(buttonReg.regFlagsStateKey, NINE_KEY);
				keyPresed = NINE_KEY;
			}
		}
		else if(!LL_GPIO_IsInputPinSet(KEY_G_GPIO_Port, KEY_G_Pin))
		{
			buttonReg.countKey[NINE_KEY] = 0;
			BitCtr(buttonReg.regPrevStateKey, NINE_KEY);
			BitCtr(buttonReg.regFlagsStateKey, NINE_KEY);
		}

		if(buttonReg.regFlagsStateKey == 0)
		{
			keyPresed = UNKOW_KEY;
		}
	}
}
