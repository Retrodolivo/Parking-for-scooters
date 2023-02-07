#ifndef __STM_GTIMERS_H
#define __STM_GTIMERS_H

#include <stdio.h>
#include "main.h"

/*************************** ������������� �������� ***************************/
#define TIMER_READ_KEY			0 	// ������ ������ ����������
#define TIMER_READ_INPUTS		1 	// ������ ������ ������
#define TIMER_WAITING_INPUT		2 	// ������ �������� ����� ������, �� ��������� ������� ���������� �������� �� ������� �����
#define TIMER_DELAY_RUN			3 	// ������ �������� ��� �������� ����� "taskMainRun"
#define TIMER_LCD_EFFECTS		4 	// ������ ��� �������� LCD
#define TIMER_NFC				5 	// ������ ��� ������ NFC
#define TIMER_LOCK				6 	// ������ ��� ��������� ������
#define TIMER_LED				7 	// ������ ��� ������ ���������� ������������
#define TIMEDR_CHARGE			8 	// ������ ��� ������ ���������� ������� (���������)
#define TIMER_CHARGE_DELAY		9 	// ������ ��� ������������ �������� ������ ���������� ������� (���������)
#define TIMER_SERVICE			10	// ������ �� ���������� ������


typedef enum
{
	TIMER_STOPED = 0,
	TIMER_RUNNING = 1,
	TIMER_PAUSED = 2
}timerState;

#define MAXTIMER 11						//���������� ��������

typedef enum
{
	fTrue = 1,
	fFalse = 0
}flagState;

typedef struct
{
	volatile uint32_t counter;					//������� ��������
	volatile timerState state;					//������� ���������
	volatile flagState stateFlag;				//���� ��������� 1 ���� ��������, 0 ������������
}gTimers_t;

extern volatile gTimers_t gTimer[MAXTIMER];			//������ ��������

void initGTimer(void);										//������������� ��������
void startGTimer(uint8_t gTimerID, uint32_t initTimer);		//������ �������
void stopGTimer(uint8_t gTimerID);							//��������� �������
void restartGTimer(uint8_t gTimerID, uint32_t initTimer); 	//���������� ������� � ����� ��������� �������
void pausedGTime(uint8_t gTimerID);							//������������ ������ �������
void releaseGTimer(uint8_t gTimerID);						//����������� ������ ����� �����
gTimers_t getGTimer(uint8_t gTimerID);						//��������� �������� �������
void processTimers(void);									//��������� � ���������� ������� ��������

void setFlagInterruptGTimer(void);	//������������� ���� � ��������� ���������� �������
void processTimersMainCycle(void); //��������� ������� �������� � �������� ����� ���������


#endif
