#ifndef _INPUTS_H
#define _INPUTS_H

#include "main.h"

#define TIME_READ_INPUT (1)

uint8_t getStateCurrentSocket_1(void); // �������� ��������� �������� ����� ������ �������
uint8_t getStateCurrentSocket_2(void); // �������� ��������� �������� ����� ������ �������
uint8_t getStateCurrentSocket_3(void); // �������� ��������� �������� ����� ������� �������
uint8_t getStateCurrentSocket_4(void); // �������� ��������� �������� ����� ��������� �������
uint8_t getStateCurrentSocket_5(void); // �������� ��������� �������� ����� ����� �������

void inputsTask(void); //  ����� ������

#endif
