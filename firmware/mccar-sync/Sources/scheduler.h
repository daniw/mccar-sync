/*
 * scheduler.h
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef struct ShortRunningTaskStruct
{
	void (*execute)(void* pData);
	void* pData;
	struct ShortRunningTaskStruct* pNext;
} ShortRunningTask;

typedef struct
{
	ShortRunningTask* pNextTask;
} Scheduler;

void scheduler_init(Scheduler* pScheduler);
void scheduler_execute(Scheduler* pScheduler);
void scheduler_scheduleTask(Scheduler* pScheduler, void (*fnExecute)(void* pData), void* pData);
ShortRunningTask* scheduler_fetchTask(Scheduler* pScheduler);

#endif /* SCHEDULER_H_ */
