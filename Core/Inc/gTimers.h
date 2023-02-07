#ifndef __STM_GTIMERS_H
#define __STM_GTIMERS_H

#include <stdio.h>
#include "main.h"

/*************************** Распределение таймеров ***************************/
#define TIMER_READ_KEY			0 	// Таймер опроса клавиатуры
#define TIMER_READ_INPUTS		1 	// Таймер опроса входов
#define TIMER_WAITING_INPUT		2 	// Таймер ожидание ввода данных, по истичении времени устройство перейдет на главный экран
#define TIMER_DELAY_RUN			3 	// Таймер задержки для главного цикла "taskMainRun"
#define TIMER_LCD_EFFECTS		4 	// Таймер для эффектов LCD
#define TIMER_NFC				5 	// Таймер для Опроса NFC
#define TIMER_LOCK				6 	// Таймер для обработки замков
#define TIMER_LED				7 	// Тафмер для задачи управления светодиодами
#define TIMEDR_CHARGE			8 	// Таймер для задачи управление зарядом (розетками)
#define TIMER_CHARGE_DELAY		9 	// Таймер для формирование задержек задачи управление зарядом (розетками)
#define TIMER_SERVICE			10	// Таймер ля сервисного режима


typedef enum
{
	TIMER_STOPED = 0,
	TIMER_RUNNING = 1,
	TIMER_PAUSED = 2
}timerState;

#define MAXTIMER 11						//Количество таймеров

typedef enum
{
	fTrue = 1,
	fFalse = 0
}flagState;

typedef struct
{
	volatile uint32_t counter;					//Регистр счетчика
	volatile timerState state;					//Регистр состаяния
	volatile flagState stateFlag;				//Флаг состояния 1 счет закончен, 0 продолжается
}gTimers_t;

extern volatile gTimers_t gTimer[MAXTIMER];			//Массив таймеров

void initGTimer(void);										//Инициализация таймероа
void startGTimer(uint8_t gTimerID, uint32_t initTimer);		//Запуск таймера
void stopGTimer(uint8_t gTimerID);							//Остановка таймера
void restartGTimer(uint8_t gTimerID, uint32_t initTimer); 	//Перезапуск таймера с новым значением времени
void pausedGTime(uint8_t gTimerID);							//Приостановка работы таймера
void releaseGTimer(uint8_t gTimerID);						//Продолжения работы после паузы
gTimers_t getGTimer(uint8_t gTimerID);						//Получение значения таймера
void processTimers(void);									//Оброботка в прерывании таймера счетчика

void setFlagInterruptGTimer(void);	//Устанавливает флаг в обработке прерывания таймера
void processTimersMainCycle(void); //Оброботка таймера счетчика в основном цикле программы


#endif
