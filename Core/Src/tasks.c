#include "tasks.h"

/*********************************************************************
 * �������� �����                                                    *
 *********************************************************************/
void tasks(void)
{
	inputsTask();
	taskMainRun();
	taskNfc();
	lcdTask();
	lockControlTask();
	chargeControlTask();
	outputsTask();
}
