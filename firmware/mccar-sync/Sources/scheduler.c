/*
 * scheduler.c
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#include "scheduler.h"
#include "util.h"
#include "malloc.h"

#define MAX_NUM_TASKS 20

void scheduler_init(Scheduler* pScheduler)
{
	taskqueue_init(&pScheduler->taskQueue);
}

void scheduler_execute(Scheduler* pScheduler)
{
	for (;;)
	{
		Task* pTask = taskqueue_dequeue(&pScheduler->taskQueue);
		if (pTask)
		{
			pTask->execute(pTask->pData);
			_free(pTask);
		}
	}
}

void scheduler_scheduleTask(Scheduler* pScheduler, void (*fnExecute)(void* pData), void* pData)
{
	Task* pNewTask;
	pNewTask = _malloc(sizeof(Task));
	if (!pNewTask)
		FATAL_ERROR();
	
	pNewTask->execute = fnExecute;
	pNewTask->pData = pData;
	
	if (!taskqueue_enqueue(&pScheduler->taskQueue, pNewTask))
		FATAL_ERROR();
}
