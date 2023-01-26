#include "lockControl.h"

static uint8_t countStep = 0;

/*********************************************************************
 * ”правление замками                                                *
 *********************************************************************/
void lockControlTask(void)
{
	switch(countStep)
	{
		case 0:
		{
			setOutLockCh_1(FALSE);
			setOutLockCh_2(FALSE);
			setOutLockCh_3(FALSE);
			setOutLockCh_4(FALSE);
			setOutLockCh_5(FALSE);
			if(getStateMainRun() >= 3 && getStateMainRun() < 13)
			{
				countStep++;
			}
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_LOCK).stateFlag == fTrue)
			{
				stopGTimer(TIMER_LOCK);
				countStep = 0;
				break;
			}
			if(getStateMainRun() < 3 && getGTimer(TIMER_LOCK).state == TIMER_STOPED)
			{
				startGTimer(TIMER_LOCK, TIME_PAUSE_CLOSE);
			}
			if(getStateMainRun() >= 3 && getGTimer(TIMER_LOCK).state != TIMER_STOPED)
			{
				stopGTimer(TIMER_LOCK);
			}
			if(getStateCh_1() == CH_CLOSE)
			{
				setOutLockCh_1(FALSE);
			}
			else
			{
				setOutLockCh_1(TRUE);
			}
			if(getStateCh_2() == CH_CLOSE)
			{
				setOutLockCh_2(FALSE);
			}
			else
			{
				setOutLockCh_2(TRUE);
			}
			if(getStateCh_3() == CH_CLOSE)
			{
				setOutLockCh_3(FALSE);
			}
			else
			{
				setOutLockCh_3(TRUE);
			}
			if(getStateCh_4() == CH_CLOSE)
			{
				setOutLockCh_4(FALSE);
			}
			else
			{
				setOutLockCh_4(TRUE);
			}
			if(getStateCh_5() == CH_CLOSE)
			{
				setOutLockCh_5(FALSE);
			}
			else
			{
				setOutLockCh_5(TRUE);
			}
			break;
		}
	}
}
