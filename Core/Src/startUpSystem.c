#include "startUpSystem.h"

/*********************************************************************
 * ������������� ����� ���������                                     *
 *********************************************************************/
void startUpSystem(void)
{
	initGTimer();
	flashEepromInit();
	initLcd();
	nfcInit();
	LL_TIM_EnableIT_UPDATE(TIM3);
	LL_TIM_EnableCounter(TIM3);
}
