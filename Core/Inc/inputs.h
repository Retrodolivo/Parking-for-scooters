#ifndef _INPUTS_H
#define _INPUTS_H

#include "main.h"

#define TIME_READ_INPUT (1)

uint8_t getStateCurrentSocket_1(void); // Получить состояние токового входа первой розетки
uint8_t getStateCurrentSocket_2(void); // Получить состояние токового входа второй розетки
uint8_t getStateCurrentSocket_3(void); // Получить состояние токового входа третьей розетки
uint8_t getStateCurrentSocket_4(void); // Получить состояние токового входа четвертой розетки
uint8_t getStateCurrentSocket_5(void); // Получить состояние токового входа пятой розетки

void inputsTask(void); //  Опрос входов

#endif
