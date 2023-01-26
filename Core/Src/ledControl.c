#include "ledControl.h"

#define LED1_RED LL_GPIO_SetOutputPin(LED_RED_1_GPIO_Port, LED_RED_1_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
#define LED1_GREEN LL_GPIO_SetOutputPin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin); LL_GPIO_ResetOutputPin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
#define LED2_RED LL_GPIO_SetOutputPin(LED_RED_2_GPIO_Port, LED_RED_2_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
#define LED2_GREEN LL_GPIO_SetOutputPin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin); LL_GPIO_ResetOutputPin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
#define LED3_RED LL_GPIO_SetOutputPin(LED_RED_3_GPIO_Port, LED_RED_3_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin);
#define LED3_GREEN LL_GPIO_SetOutputPin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin); LL_GPIO_ResetOutputPin(LED_RED_3_GPIO_Port, LED_RED_3_Pin);
#define LED4_RED LL_GPIO_SetOutputPin(LED_RED_4_GPIO_Port, LED_RED_4_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin);
#define LED4_GREEN LL_GPIO_SetOutputPin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin); LL_GPIO_ResetOutputPin(LED_RED_4_GPIO_Port, LED_RED_4_Pin);
#define LED5_RED LL_GPIO_SetOutputPin(LED_RED_5_GPIO_Port, LED_RED_5_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_5_GPIO_Port, LED_GREEN_5_Pin);
#define LED5_GREEN LL_GPIO_SetOutputPin(LED_GREEN_5_GPIO_Port, LED_GREEN_5_Pin); LL_GPIO_ResetOutputPin(LED_RED_5_GPIO_Port, LED_RED_5_Pin);

#define LED1_RED_TOGGLE LL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
#define LED1_GREEN_TOGGLE LL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin); LL_GPIO_ResetOutputPin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
#define LED2_RED_TOGGLE LL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
#define LED2_GREEN_TOGGLE LL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin); LL_GPIO_ResetOutputPin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
#define LED3_RED_TOGGLE LL_GPIO_TogglePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin);
#define LED3_GREEN_TOGGLE LL_GPIO_TogglePin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin); LL_GPIO_ResetOutputPin(LED_RED_3_GPIO_Port, LED_RED_3_Pin);
#define LED4_RED_TOGGLE LL_GPIO_TogglePin(LED_RED_4_GPIO_Port, LED_RED_4_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin);
#define LED4_GREEN_TOGGLE LL_GPIO_TogglePin(LED_GREEN_4_GPIO_Port, LED_GREEN_4_Pin); LL_GPIO_ResetOutputPin(LED_RED_4_GPIO_Port, LED_RED_4_Pin);
#define LED5_RED_TOGGLE LL_GPIO_TogglePin(LED_RED_5_GPIO_Port, LED_RED_5_Pin); LL_GPIO_ResetOutputPin(LED_GREEN_5_GPIO_Port, LED_GREEN_5_Pin);
#define LED5_GREEN_TOGGLE LL_GPIO_TogglePin(LED_GREEN_5_GPIO_Port, LED_GREEN_5_Pin); LL_GPIO_ResetOutputPin(LED_RED_5_GPIO_Port, LED_RED_5_Pin);

static uint8_t countStep = 0;

/*********************************************************************
 * Управление светодиодами                                           *
 *********************************************************************/
void ledControlTask(void)
{
	switch(countStep)
	{
		case 0:
		{
			if(getStateCh_1() == CH_CLOSE)
			{
				LED1_RED;
			}
			else
			{
				LED1_GREEN
			}

			if(getStateCh_2() == CH_CLOSE)
			{
				LED2_RED;
			}
			else
			{
				LED2_GREEN
			}

			if(getStateCh_3() == CH_CLOSE)
			{
				LED3_RED;
			}
			else
			{
				LED3_GREEN
			}

			if(getMaxChannels() > 3)
			{
				if(getStateCh_4() == CH_CLOSE)
				{
					LED4_RED;
				}
				else
				{
					LED4_GREEN
				}

				if(getStateCh_5() == CH_CLOSE)
				{
					LED5_RED;
				}
				else
				{
					LED5_GREEN
				}
			}
			if(getStateMainRun() == 3)
			{
				countStep++;
			}
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LED).state == TIMER_STOPED && getGTimer(TIMER_LED).stateFlag == fFalse)
			{
				startGTimer(TIMER_LED, TIME_BLINK);
			}
			if(getGTimer(TIMER_LED).stateFlag == fTrue)
			{
				startGTimer(TIMER_LED, TIME_BLINK);
				if(getChChoiseValue() == 1)
				{
					if(getStateCh_1() == CH_CLOSE)
					{
						LED1_RED_TOGGLE;
					}
					else
					{
						LED1_GREEN_TOGGLE;
					}
				}
				else
				{
					if(getStateCh_1() == CH_CLOSE)
					{
						LED1_RED;
					}
					else
					{
						LED1_GREEN;
					}
				}

				if(getChChoiseValue() == 2)
				{
					if(getStateCh_2() == CH_CLOSE)
					{
						LED2_RED_TOGGLE;
					}
					else
					{
						LED2_GREEN_TOGGLE;
					}
				}
				else
				{
					if(getStateCh_2() == CH_CLOSE)
					{
						LED2_RED;
					}
					else
					{
						LED2_GREEN;
					}
				}

				if(getChChoiseValue() == 3)
				{
					if(getStateCh_3() == CH_CLOSE)
					{
						LED3_RED_TOGGLE;
					}
					else
					{
						LED3_GREEN_TOGGLE;
					}
				}
				else
				{
					if(getStateCh_3() == CH_CLOSE)
					{
						LED3_RED;
					}
					else
					{
						LED3_GREEN;
					}
				}

				if(getMaxChannels() > 3)
				{
					if(getChChoiseValue() == 4)
					{
						if(getStateCh_4() == CH_CLOSE)
						{
							LED4_RED_TOGGLE;
						}
						else
						{
							LED4_GREEN_TOGGLE;
						}
					}
					else
					{
						if(getStateCh_4() == CH_CLOSE)
						{
							LED4_RED;
						}
						else
						{
							LED4_GREEN;
						}
					}

					if(getChChoiseValue() == 5)
					{
						if(getStateCh_5() == CH_CLOSE)
						{
							LED5_RED_TOGGLE;
						}
						else
						{
							LED5_GREEN_TOGGLE;
						}
					}
					else
					{
						if(getStateCh_5() == CH_CLOSE)
						{
							LED5_RED;
						}
						else
						{
							LED5_GREEN;
						}
					}
				}

			}
			if(getStateMainRun() != 3)
			{
				stopGTimer(TIMER_LED);
				countStep = 0;
			}
			break;
		}
	}
}
