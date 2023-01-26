#ifndef _TASKMAINRUN_H
#define _TASKMAINRUN_H

#include "main.h"
#include "bitOperations.h"
#include "gTimers.h"
#include "inputs.h"
#include "outputs.h"
#include "flashEEPROM.h"
#include "keyboard.h"

#define TIME_WAITING_INPUT 15000	//15 сек. врем€ ожидани€ каких-либо действий от поользовател€
#define TIME_PAUSE	2000			// 2 сек. врем€ задержки между переходами к следующему экрану

typedef struct ChData{
	uint32_t state;
	uint32_t passwordOrKey;
}chData_t;

typedef struct MasterData{
	uint32_t generalPassword;
	uint32_t masterKey;
	uint32_t timeCharge;
}masterData_t;

enum StateCh{
	CH_OPEN = 0,
	CH_CLOSE
};

enum MaxChennels{
	THREE_CH = 3,
	FIVE_CH = 5
};

uint8_t getMaxChannels(void);		// ѕолучить максимальное кол-во каналов в устройстве
uint32_t getStateCh_1(void);  		// ѕолучить состо€ние первого канала (дока) 0 - открыт; 1 - закрыт.
uint32_t getStateCh_2(void);  		// ѕолучить состо€ние второго канала (дока) 0 - открыт; 1 - закрыт.
uint32_t getStateCh_3(void);  		// ѕолучить состо€ние третьего канала (дока) 0 - открыт; 1 - закрыт.
uint32_t getStateCh_4(void);  		// ѕолучить состо€ние четвертого канала (дока) 0 - открыт; 1 - закрыт.
uint32_t getStateCh_5(void);  		// ѕолучить состо€ние п€того канала (дока) 0 - открыт; 1 - закрыт.
uint32_t getKeyboardCode(void); 	// ѕолучить код введенный с клавиатуры
uint8_t getChChoiseValue(void);		// ѕолучить номер выбранного канала
uint8_t getStateMainRun(void);		// ѕолучить получить состо€ние основного цикла
masterData_t getMasterData(void);	// ѕолучить сервисные настройки

void taskMainRun(void); 		// ќсновна€ задача

#endif
