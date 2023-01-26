#ifndef _MT12232D_H
#define _MT12232D_H

#include "main.h"
#include "stm32f3xx_hal.h"

void initLcd(void); // ������������� LCD
void writeCodeL(uint8_t data); // �������� ������� � ����� �������� ����������
void writeCodeR(uint8_t data); // �������� ������� � ������ �������� ����������
void writeDataL(uint8_t data); // �������� ������ � ����� �������� ����������
void writeDataR(uint8_t data); // �������� ������ � ������ �������� ����������
void clearLcd(void); // �������� LCD

#endif
