/*
 * scheduler.c
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#include "scheduler.h"
#include "util.h"
#include "malloc.h"

void scheduler_init(Scheduler* pScheduler)
{
	pScheduler->pNextTask = 0;
}

void scheduler_execute(Scheduler* pScheduler)
{
	for (;;)
	{
		ShortRunningTask* pTask = scheduler_fetchTask(pScheduler);
		if (pTask)
		{
			pTask->execute(pTask->pData);
			_free(pTask);
		}
	}
}

void scheduler_scheduleTask(Scheduler* pScheduler, void (*fnExecute)(void* pData), void* pData)
{
	ShortRunningTask* pNewTask;
	DisableInterrupts;
	pNewTask = _malloc(sizeof(ShortRunningTask));
	if (!pNewTask)
		FATAL_ERROR();
	
	pNewTask->execute = fnExecute;
	pNewTask->pData = pData;
	pNewTask->pNext = NULL;
	
	if (pScheduler->pNextTask)
	{
		ShortRunningTask* pTask = pScheduler->pNextTask;
		while (pTask->pNext)
			pTask = pTask->pNext;
		
		pTask->pNext = pNewTask;
	}
	else
	{
		pScheduler->pNextTask = pNewTask;
	}
	EnableInterrupts;
}

ShortRunningTask* scheduler_fetchTask(Scheduler* pScheduler)
{
	ShortRunningTask* nextTask = NULL;
	DisableInterrupts;
	if (pScheduler->pNextTask)
	{
		nextTask = pScheduler->pNextTask;
		pScheduler->pNextTask = nextTask->pNext;
	}
	EnableInterrupts;
	return nextTask;
}
