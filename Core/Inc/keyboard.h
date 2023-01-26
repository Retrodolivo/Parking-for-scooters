#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "main.h"
#include "bitOperations.h"
#include "gTimers.h"

#define TIME_READ_KEY_MS (5)
#define MAX_COUNT_BUTTONS (5)

typedef enum KeyPresedEnum{
	ZERO_KEY = 0,
	ONE_KEY,
	TWO_KEY,
	THREE_KEY,
	FOUR_KEY,
	FIVE_KEY,
	SIX_KEY,
	SEVEN_KEY,
	EIGHT_KEY,
	NINE_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	CLEAR_KEY,
	ENTER_KEY,
	UNKOW_KEY = 0xFF
}keyPresedEnum_t;

uint32_t getPresedAllKeys(void); // Получить значение нажатых кнопки клавиатуры
keyPresedEnum_t getPresetKey(void); // Получмть какая кнопка нажата
void keyboardTask(void); // Опрос клавиатуры

#endif
