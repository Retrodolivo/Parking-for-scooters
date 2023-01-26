#ifndef _CHARGECONTROL_H
#define _CHARGECONTROL_H

#define TIME_PAUSE_OFF_CHARGE 30000 //30 сек.

#include "main.h"
#include "taskMainRun.h"
#include "outputs.h"
#include "gTimers.h"

void chargeControlTask(void); // Управление зарядкой (розетками)

#endif
