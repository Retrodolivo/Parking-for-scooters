#include "taskMainRun.h"

#define ADDR_PAGE_MASTER_DATA 0x0803F800

static uint8_t countStep = 0;
static uint8_t maxCh = 5;
static chData_t chData[5];
static masterData_t masterData;
static keyPresedEnum_t valueKey = UNKOW_KEY;
static keyPresedEnum_t prevValueKey = UNKOW_KEY;
static uint32_t  keyboardKode = 0xFFFFFFFF;			// Хранит код введенный с клавиатуры
static uint8_t countDigEntered = 0;					// Счетчик кол-ва введенных цифр с клавиатуры
static uint8_t chChoiseValue = 0;					// Выбор канала который нужно открыть или закрыть



static void initVarMainRun(void);	// Инициализация переменных

/*********************************************************************
 * Получить получить состояние основного цикла                       *
 *********************************************************************/
uint8_t getStateMainRun(void)
{
	return countStep;
}

/*********************************************************************
 * Получить максимальное кол-во каналов в устройстве                 *
 *********************************************************************/
uint8_t getMaxChannels(void)
{
	return maxCh;
}

/*********************************************************************
 * Получить состояние первого канала (дока) 0 - открыт; 1 - закрыт.  *
 *********************************************************************/
uint32_t getStateCh_1(void)
{
	return chData[0].state;
}

/*********************************************************************
 * Получить состояние второго канала (дока) 0 - открыт; 1 - закрыт.  *
 *********************************************************************/
uint32_t getStateCh_2(void)
{
	return chData[1].state;
}

/*********************************************************************
 * Получить состояние третьего канала (дока) 0 - открыт; 1 - закрыт. *
 *********************************************************************/
uint32_t getStateCh_3(void)
{
	return chData[2].state;
}

/*********************************************************************
 * Получить состояние четвертого канала (дока) 0 - открыт; 1 - закрыт*
 *********************************************************************/
uint32_t getStateCh_4(void)
{
	return chData[3].state;
}

/*********************************************************************
 * Получить состояние пятого канала (дока) 0 - открыт; 1 - закрыт.   *
 *********************************************************************/
uint32_t getStateCh_5(void)
{
	return chData[4].state;
}

/*********************************************************************
 * Получить код введенный с клавиатуры                               *
 *********************************************************************/
uint32_t getKeyboardCode(void)
{
	return keyboardKode;
}

/*********************************************************************
 * Получить номер выбранного канала                                  *
 *********************************************************************/
uint8_t getChChoiseValue(void)
{
	return chChoiseValue + 1;
}

/*********************************************************************
 * Получить сервисные настройки                                      *
 *********************************************************************/
masterData_t getMasterData(void)
{
	return masterData;
}

/*********************************************************************
 * Основная задача                                                   *
 *********************************************************************/
void taskMainRun(void)
{
	valueKey = getPresetKey();
	if(valueKey == UNKOW_KEY)
	{
		valueKey = UNKOW_KEY;
		prevValueKey = UNKOW_KEY;
	}

	switch(countStep)
	{
		case 0: // Иницаализация переменных
		{
			if(!LL_GPIO_IsInputPinSet(SW_3_5CH_GPIO_Port, SW_3_5CH_Pin))//if(!LL_GPIO_IsInputPinSet(SW_3_5CH_GPIO_Port, SW_3_5CH_Pin))
			{
				maxCh = 3;
			}
			initVarMainRun();
			HAL_Delay(100);
			if((getPresedAllKeys() & (1 << ZERO_KEY)) != 0 && (getPresedAllKeys() & (1 << LEFT_KEY)) != 0 )
			{
				prevValueKey = valueKey;
				countStep = 13;
				break;
			}
			countStep++;
			break;
		}
		case 1: // Обработка начального экрана
		{
			if(valueKey != UNKOW_KEY && valueKey != prevValueKey)
			{
				restartGTimer(TIMER_WAITING_INPUT, TIME_WAITING_INPUT);
				prevValueKey = valueKey;
				if(valueKey >= ZERO_KEY && valueKey <= NINE_KEY)
				{
					keyboardKode &= ~(0xFF << countDigEntered * 8);
					keyboardKode |= (valueKey << countDigEntered * 8);
					countDigEntered++;
					if(countDigEntered >= 4)
					{
						if(keyboardKode == masterData.generalPassword)
						{
							setScreenNumber(GEN_PASSWORD_OK_SCREEN);
							countStep++;
						}
						else
						{
							setScreenNumber(ERROR_SCREEN);
							keyboardKode = 0xFFFFFFFF;
							countDigEntered = 0;
							countStep++;
						}
					}
				}
				else if(valueKey == CLEAR_KEY)
				{
					keyboardKode = 0xFFFFFFFF;
					countDigEntered = 0;
				}
			}
			if(getGTimer(TIMER_WAITING_INPUT).stateFlag == fTrue && valueKey == UNKOW_KEY)
			{
				stopGTimer(TIMER_WAITING_INPUT);
				keyboardKode = 0xFFFFFFFF;
				countDigEntered = 0;
			}
			break;
		}
		case 2: // Ожидаем окончание анимации GEN_PASSWORD_OK_SCREEN
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				if(keyboardKode == 0xFFFFFFFF)
				{
					setScreenNumber(START_SCREEN);
					countStep = 1;
				}
				else
				{
					keyboardKode = 0xFFFFFFFF;
					countDigEntered = 0;
					chChoiseValue = 0;
					setSelectedEndPrevCell(chChoiseValue + 1, 0);
					setScreenNumber(SELECT_SCREEN);
					countStep++;
				}
			}
			break;
		}
		case 3: // Обработка выбора ячейки для открытия или закрытия
		{
			if(!gerStateFlagEventOverLcd()) break;
			if(valueKey != UNKOW_KEY && valueKey != prevValueKey)
			{
				restartGTimer(TIMER_WAITING_INPUT, TIME_WAITING_INPUT);
				prevValueKey = valueKey;
				if(valueKey == LEFT_KEY)
				{
					if(chChoiseValue != 0)
					{
						chChoiseValue--;
						resetStateFlagEventOverLcd();
						setSelectedEndPrevCell(chChoiseValue+1, chChoiseValue+2);
					}
				}
				else if(valueKey == RIGHT_KEY)
				{
					if(chChoiseValue < maxCh - 1)
					{
						chChoiseValue++;
						resetStateFlagEventOverLcd();
						setSelectedEndPrevCell(chChoiseValue + 1, chChoiseValue);
					}
				}
				else if(valueKey == CLEAR_KEY)
				{
					resetStateFlagEventOverLcd();
					setSelectedEndPrevCell(0, chChoiseValue + 1);
					countStep = 4;

				}
				else if(valueKey == ENTER_KEY)
				{
					resetStateFlagEventOverLcd();
					setScreenNumber(SELECT_CELL_SCREEN);
					countStep = 5;
				}
			}
			if(getGTimer(TIMER_WAITING_INPUT).stateFlag == fTrue && valueKey == UNKOW_KEY)
			{
				stopGTimer(TIMER_WAITING_INPUT);
				keyboardKode = 0xFFFFFFFF;
				countDigEntered = 0;
				setSelectedEndPrevCell(0, chChoiseValue + 1);
				countStep = 4;
			}
			break;
		}
		case 4: // Ожидаем окончание анимации выбора ячейки
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(START_SCREEN);
				chChoiseValue = 0;
				countStep = 1;
			}
			break;
		}
		case 5: // Ожидаем окончание анимации подтверждения выбора ячейки
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(PASSWORD_CELL_SCREEN);
				nfcStartRun();
				countStep++;
			}
			break;
		}
		case 6: // Обработка ввода кода для выбраной ячейки
		{
			uint32_t tempIdCard = getCardID();
			if(tempIdCard != 0)
			{
				nfcStop();
				restartGTimer(TIMER_WAITING_INPUT, TIME_WAITING_INPUT);
				if(chData[chChoiseValue].state == CH_OPEN)
				{
					chData[chChoiseValue].passwordOrKey = tempIdCard;
					setScreenNumber(NFC_READ_SCREEN);
					stopGTimer(TIMER_WAITING_INPUT);
					chData[chChoiseValue].state = CH_CLOSE;
					flashEepromWriteData(chChoiseValue, (uint32_t *)&chData[chChoiseValue], sizeof(chData_t));
					countStep = 7;
				}
				else
				{
					if(chData[chChoiseValue].passwordOrKey == tempIdCard || masterData.masterKey == tempIdCard)
					{
						stopGTimer(TIMER_WAITING_INPUT);
						setScreenNumber(NFC_READ_SCREEN);
						chData[chChoiseValue].state = CH_OPEN;
						chData[chChoiseValue].passwordOrKey = 0xFFFFFFFF;
						flashEepromDeleteData(chChoiseValue);
						countStep = 8;
					}
					else
					{
						countStep = 11;
					}
				}
			}
			if(valueKey != UNKOW_KEY && valueKey != prevValueKey)
			{
				restartGTimer(TIMER_WAITING_INPUT, TIME_WAITING_INPUT);
				prevValueKey = valueKey;
				if(valueKey >= ZERO_KEY && valueKey <= NINE_KEY)
				{
					keyboardKode &= ~(0xFF << countDigEntered * 8);
					keyboardKode |= (valueKey << countDigEntered * 8);
					countDigEntered++;
					if(countDigEntered >= 4)
					{
						nfcStop();
						if(chData[chChoiseValue].state == CH_OPEN)
						{
							chData[chChoiseValue].passwordOrKey = keyboardKode;
							stopGTimer(TIMER_WAITING_INPUT);
							setScreenNumber(PASSWORD_OK_SCREEN);
							chData[chChoiseValue].state = CH_CLOSE;
							flashEepromWriteData(chChoiseValue, (uint32_t *)&chData[chChoiseValue], sizeof(chData_t));
							countStep = 7;
						}
						else
						{
							if(chData[chChoiseValue].passwordOrKey == keyboardKode)
							{
								stopGTimer(TIMER_WAITING_INPUT);
								setScreenNumber(PASSWORD_OK_SCREEN);
								chData[chChoiseValue].state = CH_OPEN;
								chData[chChoiseValue].passwordOrKey = 0xFFFFFFFF;
								flashEepromDeleteData(chChoiseValue);
								countStep = 8;
							}
							else
							{
								countStep = 11;
							}
						}
					}
				}
				else if(valueKey == CLEAR_KEY)
				{
					if(keyboardKode != 0xFFFFFFFF)
					{
						keyboardKode = 0xFFFFFFFF;
						countDigEntered = 0;
					}
					else
					{
						setScreenNumber(SELECT_SCREEN);
						setSelectedEndPrevCell(chChoiseValue + 1, 0);
						countStep = 3;
					}
				}
			}
			if(getGTimer(TIMER_WAITING_INPUT).stateFlag == fTrue && valueKey == UNKOW_KEY)
			{
				stopGTimer(TIMER_WAITING_INPUT);
				keyboardKode = 0xFFFFFFFF;
				countDigEntered = 0;
				countStep = 1;
				setScreenNumber(START_SCREEN);
			}
			break;
		}
		case 7: // Закрытие
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(CLOSE_SCREEN);
				countStep = 9;
			}
			break;
		}
		case 8: // Открытие
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(OPEN_SCREEN);
				countStep = 10;
			}
			break;
		}
		case 9:
		{
			if(gerStateFlagEventOverLcd())
			{
				chChoiseValue = 0;
				resetStateFlagEventOverLcd();
				keyboardKode = 0xFFFFFFFF;
				countDigEntered = 0;
				countStep = 1;
				setScreenNumber(START_SCREEN);
			}
			break;
		}
		case 10:
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				keyboardKode = 0xFFFFFFFF;
				countDigEntered = 0;
				countStep = 1;
				setScreenNumber(START_SCREEN);
			}
			break;
		}
		case 11:
		{
			restartGTimer(TIMER_WAITING_INPUT, TIME_WAITING_INPUT);
			setScreenNumber(ERROR_PASS_SCREEN);
			countStep = 12;
			break;
		}
		case 12:
		{
			if(gerStateFlagEventOverLcd())
			{
				restartGTimer(TIMER_WAITING_INPUT, TIME_WAITING_INPUT);
				resetStateFlagEventOverLcd();
				setScreenNumber(SELECT_SCREEN);
				setSelectedEndPrevCell(chChoiseValue + 1, 0);
				keyboardKode = 0xFFFFFFFF;
				countDigEntered = 0;
				countStep = 3;
			}
			break;
		}
		case 13: // Сервисное меню
		{
			setScreenNumber(SERVICE_MEIN);
			countStep++;
			break;
		}
		case 14:
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(SERVICE_ENTER_GEN_PASSWORD_SCREEN);
				keyboardKode = masterData.generalPassword;
				countDigEntered = 4;
				countStep++;
			}
			break;
		}
		case 15: // Ввод общего кода
		{
			if(getGTimer(TIMER_SERVICE).stateFlag == fTrue)
			{
				NVIC_SystemReset();
			}
			if(valueKey != UNKOW_KEY && valueKey != prevValueKey)
			{
				prevValueKey = valueKey;
				if(valueKey >= ZERO_KEY && valueKey <= NINE_KEY)
				{
					keyboardKode &= ~(0xFF << countDigEntered * 8);
					keyboardKode |= (valueKey << countDigEntered * 8);

					if(countDigEntered < 4)
					{
						countDigEntered++;
					}
				}
				else if(valueKey == ENTER_KEY)
				{
					if(countDigEntered >= 4)
					{
						setScreenNumber(SERVICE_SAVED_SCREEN);
						masterData.generalPassword = keyboardKode;
						flashErasePage(ADDR_PAGE_MASTER_DATA);
						flashWriteDataWord(ADDR_PAGE_MASTER_DATA, (uint32_t *)&masterData, sizeof(masterData) / sizeof(uint32_t));
						countStep++;
					}
				}
				else if(valueKey == CLEAR_KEY)
				{
					keyboardKode = 0xFFFFFFFF;
					countDigEntered = 0;
				}
				else if(valueKey == RIGHT_KEY)
				{
					setScreenNumber(SERVICE_ENTER_HOUR_CHARGE_SCREEN);
					keyboardKode = masterData.timeCharge;
					countStep = 17;
				}
				else if(valueKey == LEFT_KEY)
				{
					if(getGTimer(TIMER_SERVICE).state == TIMER_STOPED)
					{
						startGTimer(TIMER_SERVICE, 5000);
					}
				}
			}
			if(valueKey == UNKOW_KEY)
			{
				stopGTimer(TIMER_SERVICE);
			}
			break;
		}
		case 16: // Вывод сообщения о сохранении кода
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(SERVICE_ENTER_GEN_PASSWORD_SCREEN);
				countStep = 15;
			}
			break;
		}
		case 17: // Установка времени заряда
		{
			if(valueKey != UNKOW_KEY && valueKey != prevValueKey)
			{
				prevValueKey = valueKey;
				if(valueKey >= ONE_KEY && valueKey <= NINE_KEY)
				{
					if(keyboardKode == 0xFF)
					{
						keyboardKode = valueKey;
					}
				}
				else if(valueKey == ENTER_KEY)
				{
					if(keyboardKode != 0xFF)
					{
						setScreenNumber(SERVICE_SAVED_SCREEN);
						masterData.timeCharge = keyboardKode;
						flashErasePage(ADDR_PAGE_MASTER_DATA);
						flashWriteDataWord(ADDR_PAGE_MASTER_DATA, (uint32_t *)&masterData, sizeof(masterData) / sizeof(uint32_t));
						countStep = 18;
					}
				}
				else if(valueKey == CLEAR_KEY)
				{
					keyboardKode = 0xFF;
				}
				else if(valueKey == LEFT_KEY)
				{
					resetStateFlagEventOverLcd();
					setScreenNumber(SERVICE_ENTER_GEN_PASSWORD_SCREEN);
					keyboardKode = masterData.generalPassword;
					countDigEntered = 4;
					countStep = 15;
				}
				else if(valueKey == RIGHT_KEY)
				{
					setScreenNumber(SERVICE_ENTER_NFC_MASTER_SCREEN);
					keyboardKode = masterData.masterKey;
					nfcStartRun();
					countStep = 19;
				}
			}
			break;
		}
		case 18: // Вывод сообщения о сохранении времени заряда
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(SERVICE_ENTER_HOUR_CHARGE_SCREEN);
				keyboardKode = masterData.timeCharge;
				countStep = 17;
			}
			break;
		}
		case 19: // Сохранение нового мастер ключа
		{
			uint32_t tempIdCard = getCardID();
			if(tempIdCard != 0)
			{
				nfcStop();
				masterData.masterKey = tempIdCard;
				flashErasePage(ADDR_PAGE_MASTER_DATA);
				flashWriteDataWord(ADDR_PAGE_MASTER_DATA, (uint32_t *)&masterData, sizeof(masterData) / sizeof(uint32_t));
				setScreenNumber(SERVICE_NFC_SCREEN);
				countStep++;
			}
			if(valueKey != UNKOW_KEY && valueKey != prevValueKey)
			{
				prevValueKey = valueKey;
				if(valueKey == LEFT_KEY)
				{
					setScreenNumber(SERVICE_ENTER_HOUR_CHARGE_SCREEN);
					keyboardKode = masterData.timeCharge;
					nfcStop();
					countStep = 17;
				}
			}
			break;
		}
		case 20:
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(SERVICE_SAVED_SCREEN);
				countStep++;
			}
			break;
		}
		case 21:
		{
			if(gerStateFlagEventOverLcd())
			{
				resetStateFlagEventOverLcd();
				setScreenNumber(SERVICE_ENTER_NFC_MASTER_SCREEN);
				keyboardKode = masterData.masterKey;
				nfcStartRun();
				countStep = 19;
			}
			break;
		}
	}
}

/*********************************************************************
 * Инициализация переменных                                          *
 *********************************************************************/
static void initVarMainRun(void)
{
	for(uint8_t i = 0; i < maxCh; i++)
	{
		if(!flashEepromReadData(i, (uint32_t *)&chData[i]))
		{
			chData[i].state = CH_OPEN;
			chData[i].passwordOrKey = 0xFFFFFFFF;
		}
	}
	flashReadDataWord(ADDR_PAGE_MASTER_DATA, (uint32_t *)&masterData, sizeof(masterData) / sizeof(uint32_t));
	if(masterData.generalPassword == 0xFFFFFFFF && masterData.masterKey == 0xFFFFFFFF)
	{
		masterData.generalPassword = 0x00000000;
		masterData.timeCharge = 5;
		flashWriteDataWord(ADDR_PAGE_MASTER_DATA, (uint32_t *)&masterData, sizeof(masterData) / sizeof(uint32_t));
	}
}
