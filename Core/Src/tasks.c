#include "tasks.h"

/*********************************************************************
 * Оработка задач                                                    *
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
