#ifndef _LCD_H
#define _LCD_H

#include "main.h"
#include "mt12232d.h"
#include "taskMainRun.h"

typedef enum ScreenNumber{
	START_SCREEN = 0,
	SELECT_SCREEN,
	PASSWORD_SCREEN,
	GEN_PASSWORD_OK_SCREEN,
	SELECT_CELL_SCREEN,
	PASSWORD_CELL_SCREEN,
	NFC_READ_SCREEN,
	OPEN_SCREEN,
	CLOSE_SCREEN,
	PASSWORD_OK_SCREEN,
	SERVICE_MEIN,
	SERVICE_ENTER_GEN_PASSWORD_SCREEN,
	SERVICE_ENTER_HOUR_CHARGE_SCREEN,
	SERVICE_ENTER_NFC_MASTER_SCREEN,
	SERVICE_SAVED_SCREEN,
	SERVICE_NFC_SCREEN,
	ERROR_SCREEN = 100,
	ERROR_PASS_SCREEN
}screenNumber_t;

void setScreenNumber(screenNumber_t screenNumber);	// Установить какой экран будет отображаться LCD
uint8_t gerStateFlagEventOverLcd(void);				// Получить состояние флага о окончании анимации (эффекта)
void resetStateFlagEventOverLcd(void);				// Сбросит состояние флага о окончании анимации (эффекта)
void setSelectedEndPrevCell(uint8_t selectCall, uint8_t prevSelectCall); // Передать выбранную ячейку для анимации выбора

void lcdTask(void); // Вывод данных на LCD

#endif
