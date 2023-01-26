#ifndef _MT12232D_H
#define _MT12232D_H

#include "main.h"
#include "stm32f3xx_hal.h"

void initLcd(void); // Инициализация LCD
void writeCodeL(uint8_t data); // Передать команду в левый кристалл индикатора
void writeCodeR(uint8_t data); // Передать команду в правый кристалл индикатора
void writeDataL(uint8_t data); // Передать данные в левую половину индикатора
void writeDataR(uint8_t data); // Передать данные в правую половину индикатора
void clearLcd(void); // Очистить LCD

#endif
