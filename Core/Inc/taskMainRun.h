#ifndef _TASKMAINRUN_H
#define _TASKMAINRUN_H

#include "main.h"
#include "bitOperations.h"
#include "gTimers.h"
#include "inputs.h"
#include "outputs.h"
#include "flashEEPROM.h"
#include "keyboard.h"

#define TIME_WAITING_INPUT 15000	//15 ���. ����� �������� �����-���� �������� �� �������������
#define TIME_PAUSE	2000			// 2 ���. ����� �������� ����� ���������� � ���������� ������

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

uint8_t getMaxChannels(void);		// �������� ������������ ���-�� ������� � ����������
uint32_t getStateCh_1(void);  		// �������� ��������� ������� ������ (����) 0 - ������; 1 - ������.
uint32_t getStateCh_2(void);  		// �������� ��������� ������� ������ (����) 0 - ������; 1 - ������.
uint32_t getStateCh_3(void);  		// �������� ��������� �������� ������ (����) 0 - ������; 1 - ������.
uint32_t getStateCh_4(void);  		// �������� ��������� ���������� ������ (����) 0 - ������; 1 - ������.
uint32_t getStateCh_5(void);  		// �������� ��������� ������ ������ (����) 0 - ������; 1 - ������.
uint32_t getKeyboardCode(void); 	// �������� ��� ��������� � ����������
uint8_t getChChoiseValue(void);		// �������� ����� ���������� ������
uint8_t getStateMainRun(void);		// �������� �������� ��������� ��������� �����
masterData_t getMasterData(void);	// �������� ��������� ���������

void taskMainRun(void); 		// �������� ������

#endif
