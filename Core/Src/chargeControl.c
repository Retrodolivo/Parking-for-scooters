#include "chargeControl.h"

static uint8_t countStep;

typedef struct ChardeVelue{
	uint32_t counter;
	uint8_t flagChargeEn;
	uint8_t flagChargeEnd;
}chargeValue_t;

chargeValue_t chargeValue[5] = {0};

/*********************************************************************
 * Управление зарядкой (розетками)                                   *
 *********************************************************************/
void chargeControlTask(void)
{
	if(getGTimer(TIMEDR_CHARGE).state == TIMER_STOPED && getGTimer(TIMEDR_CHARGE).stateFlag == fFalse)
	{
		startGTimer(TIMEDR_CHARGE, 1000);
	}
	switch(countStep)
	{
		case 0:
		{
			if(getStateCh_1() == CH_CLOSE && getStateCurrentSocket_1() && chargeValue[0].flagChargeEn == FALSE)
			{
				chargeValue[0].flagChargeEn = TRUE;
			}
			else if(getStateCh_1() == CH_OPEN)
			{
				chargeValue[0].flagChargeEn = FALSE;
				chargeValue[0].flagChargeEnd = FALSE;
				chargeValue[0].counter = 0;
				setOutChargeCh_1(FALSE);
			}
			if(chargeValue[0].flagChargeEnd == TRUE)
			{
				setOutChargeCh_1(FALSE);
			}

			if(getStateCh_2() == CH_CLOSE && getStateCurrentSocket_2() && chargeValue[1].flagChargeEn == FALSE)
			{
				chargeValue[1].flagChargeEn = TRUE;
			}
			else if(getStateCh_2() == CH_OPEN)
			{
				chargeValue[1].flagChargeEn = FALSE;
				chargeValue[1].flagChargeEnd = FALSE;
				chargeValue[1].counter = 0;
				setOutChargeCh_2(FALSE);
			}
			if(chargeValue[1].flagChargeEnd == TRUE)
			{
				setOutChargeCh_2(FALSE);
			}

			if(getStateCh_3() == CH_CLOSE && getStateCurrentSocket_3() && chargeValue[2].flagChargeEn == FALSE)
			{
				chargeValue[2].flagChargeEn = TRUE;
			}
			else if(getStateCh_3() == CH_OPEN)
			{
				chargeValue[2].flagChargeEn = FALSE;
				chargeValue[2].flagChargeEnd = FALSE;
				chargeValue[2].counter = 0;
				setOutChargeCh_3(FALSE);
			}
			if(chargeValue[2].flagChargeEnd == TRUE)
			{
				setOutChargeCh_3(FALSE);
			}

			if(getMaxChannels() > 3)
			{
				if(getStateCh_4() == CH_CLOSE && getStateCurrentSocket_4() && chargeValue[3].flagChargeEn == FALSE)
				{
					chargeValue[3].flagChargeEn = TRUE;
				}
				else if(getStateCh_4() == CH_OPEN)
				{
					chargeValue[3].flagChargeEn = FALSE;
					chargeValue[3].flagChargeEnd = FALSE;
					chargeValue[3].counter = 0;
					setOutChargeCh_4(FALSE);
				}
				if(chargeValue[3].flagChargeEnd == TRUE)
				{
					setOutChargeCh_4(FALSE);
				}

				if(getStateCh_5() == CH_CLOSE && getStateCurrentSocket_5() && chargeValue[4].flagChargeEn == FALSE)
				{
					chargeValue[4].flagChargeEn = TRUE;
				}
				else if(getStateCh_5() == CH_OPEN)
				{
					chargeValue[4].flagChargeEn = FALSE;
					chargeValue[4].flagChargeEnd = FALSE;
					chargeValue[4].counter = 0;
					setOutChargeCh_5(FALSE);
				}
				if(chargeValue[4].flagChargeEnd == TRUE)
				{
					setOutChargeCh_5(FALSE);
				}
			}

			if(getStateMainRun() >= 3 && getStateMainRun() < 13 )
			{
				countStep++;
			}
			break;
		}
		case 1:
		{
			if(getGTimer(TIMER_CHARGE_DELAY).stateFlag == fTrue)
			{
				stopGTimer(TIMER_CHARGE_DELAY);
				countStep = 0;
				break;
			}
			if(getStateMainRun() < 3 && getGTimer(TIMER_CHARGE_DELAY).state == TIMER_STOPED)
			{
				startGTimer(TIMER_CHARGE_DELAY, TIME_PAUSE_OFF_CHARGE);
			}
			setOutChargeCh_1(TRUE);
			setOutChargeCh_2(TRUE);
			setOutChargeCh_3(TRUE);
			if(getMaxChannels() > 3)
			{
				setOutChargeCh_4(TRUE);
				setOutChargeCh_5(TRUE);
			}
		}
	}
	if(getGTimer(TIMEDR_CHARGE).stateFlag == fTrue)
	{
		startGTimer(TIMEDR_CHARGE, 1000);
		for(uint8_t i = 0; i < getMaxChannels(); i++)
		{
			if(chargeValue[i].flagChargeEn && !chargeValue[i].flagChargeEnd)
			{
				chargeValue[i].counter++;
				if(chargeValue[i].counter >= (getMasterData().timeCharge * 3600))
				{
					chargeValue[i].flagChargeEnd = TRUE;
				}
			}
		}
	}
}
