/*
 * scheduler.h
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "taskQueue.h"

typedef struct
{
	TaskQueue taskQueue;
} Scheduler;

void scheduler_init(Scheduler* pScheduler);
void scheduler_execute(Scheduler* pScheduler);
void scheduler_scheduleTask(Scheduler* pScheduler, void (*fnExecute)(void* pData), void* pData);

#endif /* SCHEDULER_H_ */
