#include "gTimers.h"

static uint8_t flagInterrupt = 0;

/************************************************************************/
/* ������������� ��������                                               */
/************************************************************************/
void initGTimer(void)
{
	for(uint8_t i = 0; i < MAXTIMER; i++)
	{
		gTimer[i].counter = 0;
		gTimer[i].state = TIMER_STOPED;
		gTimer[i].stateFlag = fFalse;
	}
}

/************************************************************************/
/* ������ �������                                                       */
/************************************************************************/
void startGTimer(uint8_t gTimerID, uint32_t initTimer)
{
	if(gTimer[gTimerID].state == TIMER_STOPED)//TIMER_STOPED
	{
		if(initTimer != 0)//������ �� �������� �������� �������
		{
			gTimer[gTimerID].counter = initTimer;
			gTimer[gTimerID].state = TIMER_RUNNING;
			gTimer[gTimerID].stateFlag = fFalse;
		}
		
	}
}

/************************************************************************/
/* ��������� �������                                                    */
/************************************************************************/
void stopGTimer(uint8_t gTimerID)
{
	gTimer[gTimerID].counter = 0;
	gTimer[gTimerID].state = TIMER_STOPED;
	gTimer[gTimerID].stateFlag = fFalse;
}

/************************************************************************/
/* ���������� ������� � ����� ��������� �������                         */
/************************************************************************/
void restartGTimer(uint8_t gTimerID, uint32_t initTimer)
{
	stopGTimer(gTimerID);
	startGTimer(gTimerID, initTimer);
}

/************************************************************************/
/* ������������ ������ �������                                          */
/************************************************************************/
void pausedGTime(uint8_t gTimerID)
{
	if(gTimer[gTimerID].state == TIMER_RUNNING)
	{
		gTimer[gTimerID].state = TIMER_PAUSED;
	}
}

/************************************************************************/
/* ����������� ������ ����� �����                                       */
/************************************************************************/
void releaseGTimer(uint8_t gTimerID)
{
	if(gTimer[gTimerID].state == TIMER_PAUSED)
	{
		gTimer[gTimerID].state = TIMER_RUNNING;
	}
}

/************************************************************************/
/* ��������� �������� �������                                           */
/************************************************************************/
gTimers_t getGTimer(uint8_t gTimerID)
{
	return gTimer[gTimerID];
}

/************************************************************************/
/* ��������� � ���������� ������� ��������                              */
/************************************************************************/
void processTimers(void)
{
	for(uint8_t i = 0; i < MAXTIMER; i++)
	{
		if((gTimer[i].state == TIMER_RUNNING) && (gTimer[i].stateFlag != fTrue))
		{
			gTimer[i].counter--;
			if(gTimer[i].counter == 0)
			{
				gTimer[i].stateFlag = fTrue;
				gTimer[i].state = TIMER_STOPED;
			}
		}
	}
}


/************************************************************************/
/* ������������� ���� � ��������� ���������� �������                    */
/************************************************************************/
void setFlagInterruptGTimer(void)
{
	flagInterrupt = 1;
}

uint32_t maxTimeCicle = 0;
/************************************************************************/
/* ��������� ������� �������� � �������� ����� ���������                */
/************************************************************************/
void processTimersMainCycle(void)
{
	if(flagInterrupt)
	{
		flagInterrupt = 0;
		processTimers();
	}
}
