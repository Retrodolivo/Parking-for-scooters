#include "inputs.h"

enum regInputEnum{
	CURRENT_SOCKET_1 = 0,
	CURRENT_SOCKET_2,
	CURRENT_SOCKET_3,
	CURRENT_SOCKET_4,
	CURRENT_SOCKET_5,
};

typedef struct InputsReg{
	uint32_t regFlagsStateInputs;
	uint32_t regPrevStateInputs;
	uint8_t countInputs[10];
}inputsReg_t;

inputsReg_t inputsReg = {0, 0, {0}};

/*********************************************************************
 * Получить состояние токового входа первой розетки                  *
 *********************************************************************/
uint8_t getStateCurrentSocket_1(void)
{
	if(BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_1) != FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************************
 * Получить состояние токового входа второй розетки                  *
 *********************************************************************/
uint8_t getStateCurrentSocket_2(void)
{
	if(BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2) != FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************************
 * Получить состояние токового входа третьей розетки                 *
 *********************************************************************/
uint8_t getStateCurrentSocket_3(void)
{
	if(BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_3) != FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************************
 * Получить состояние токового входа четвертой розетки               *
 *********************************************************************/
uint8_t getStateCurrentSocket_4(void)
{
	if(BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_4) != FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************************
 * Получить состояние токового входа пятой розетки                   *
 *********************************************************************/
uint8_t getStateCurrentSocket_5(void)
{
	if(BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_5) != FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************************
 * Опрос входов                                                      *
 *********************************************************************/
void inputsTask(void)
{
	if(getGTimer(TIMER_READ_INPUTS).state == TIMER_STOPED && getGTimer(TIMER_READ_INPUTS).stateFlag == fFalse)
	{
		startGTimer(TIMER_READ_INPUTS, TIME_READ_INPUT);
	}
	if(getGTimer(TIMER_READ_INPUTS).stateFlag == fTrue)
	{
		startGTimer(TIMER_READ_INPUTS, TIME_READ_INPUT);
		if(LL_GPIO_IsInputPinSet(CURRENT_IN_1_GPIO_Port, CURRENT_IN_1_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_1) == FALSE)
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_1);
		}
		else if(LL_GPIO_IsInputPinSet(CURRENT_IN_1_GPIO_Port, CURRENT_IN_1_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_1) != FALSE && BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_1) == FALSE)
		{
			inputsReg.countInputs[CURRENT_SOCKET_1]++;
			if(inputsReg.countInputs[CURRENT_SOCKET_1] >= TIME_READ_INPUT)
			{
				BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_1);
			}
		}

		else if(!LL_GPIO_IsInputPinSet(CURRENT_IN_1_GPIO_Port, CURRENT_IN_1_Pin))
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_1);
			BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_1);
			inputsReg.countInputs[CURRENT_SOCKET_1] = 0;
		}

		if(LL_GPIO_IsInputPinSet(CURRENT_IN_2_GPIO_Port, CURRENT_IN_2_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2) == FALSE)
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2);
		}
		else if(LL_GPIO_IsInputPinSet(CURRENT_IN_2_GPIO_Port, CURRENT_IN_2_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2) != FALSE && BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2) == FALSE)
		{
			inputsReg.countInputs[CURRENT_SOCKET_2]++;
			if(inputsReg.countInputs[CURRENT_SOCKET_2] >= TIME_READ_INPUT)
			{
				BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2);
			}
		}

		else if(!LL_GPIO_IsInputPinSet(CURRENT_IN_1_GPIO_Port, CURRENT_IN_1_Pin))
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2);
			BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2);
			inputsReg.countInputs[CURRENT_SOCKET_2] = 0;
		}

		if(LL_GPIO_IsInputPinSet(CURRENT_IN_2_GPIO_Port, CURRENT_IN_2_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2) == FALSE)
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2);
		}
		else if(LL_GPIO_IsInputPinSet(CURRENT_IN_2_GPIO_Port, CURRENT_IN_2_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2) != FALSE && BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2) == FALSE)
		{
			inputsReg.countInputs[CURRENT_SOCKET_2]++;
			if(inputsReg.countInputs[CURRENT_SOCKET_2] >= TIME_READ_INPUT)
			{
				BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2);
			}
		}

		else if(!LL_GPIO_IsInputPinSet(CURRENT_IN_2_GPIO_Port, CURRENT_IN_2_Pin))
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_2);
			BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_2);
			inputsReg.countInputs[CURRENT_SOCKET_2] = 0;
		}

		if(LL_GPIO_IsInputPinSet(CURRENT_IN_3_GPIO_Port, CURRENT_IN_3_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_3) == FALSE)
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_3);
		}
		else if(LL_GPIO_IsInputPinSet(CURRENT_IN_3_GPIO_Port, CURRENT_IN_3_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_3) != FALSE && BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_3) == FALSE)
		{
			inputsReg.countInputs[CURRENT_SOCKET_3]++;
			if(inputsReg.countInputs[CURRENT_SOCKET_3] >= TIME_READ_INPUT)
			{
				BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_3);
			}
		}

		else if(!LL_GPIO_IsInputPinSet(CURRENT_IN_3_GPIO_Port, CURRENT_IN_3_Pin))
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_3);
			BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_3);
			inputsReg.countInputs[CURRENT_SOCKET_3] = 0;
		}

		if(LL_GPIO_IsInputPinSet(CURRENT_IN_4_GPIO_Port, CURRENT_IN_4_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_4) == FALSE)
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_4);
		}
		else if(LL_GPIO_IsInputPinSet(CURRENT_IN_4_GPIO_Port, CURRENT_IN_4_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_4) != FALSE && BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_4) == FALSE)
		{
			inputsReg.countInputs[CURRENT_SOCKET_4]++;
			if(inputsReg.countInputs[CURRENT_SOCKET_4] >= TIME_READ_INPUT)
			{
				BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_4);
			}
		}

		else if(!LL_GPIO_IsInputPinSet(CURRENT_IN_4_GPIO_Port, CURRENT_IN_4_Pin))
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_4);
			BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_4);
			inputsReg.countInputs[CURRENT_SOCKET_4] = 0;
		}

		if(LL_GPIO_IsInputPinSet(CURRENT_IN_5_GPIO_Port, CURRENT_IN_5_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_5) == FALSE)
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_5);
		}
		else if(LL_GPIO_IsInputPinSet(CURRENT_IN_5_GPIO_Port, CURRENT_IN_5_Pin) == TRUE && BitStatus(inputsReg.regPrevStateInputs, CURRENT_SOCKET_5) != FALSE && BitStatus(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_5) == FALSE)
		{
			inputsReg.countInputs[CURRENT_SOCKET_5]++;
			if(inputsReg.countInputs[CURRENT_SOCKET_5] >= TIME_READ_INPUT)
			{
				BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_5);
			}
		}

		else if(!LL_GPIO_IsInputPinSet(CURRENT_IN_5_GPIO_Port, CURRENT_IN_5_Pin))
		{
			BitSet(inputsReg.regPrevStateInputs, CURRENT_SOCKET_5);
			BitSet(inputsReg.regFlagsStateInputs, CURRENT_SOCKET_5);
			inputsReg.countInputs[CURRENT_SOCKET_5] = 0;
		}
	}
}
