/*
 * taskQueue.c
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#include "taskQueue.h"

#include "malloc.h"
#include "util.h"

void taskqueue_init(TaskQueue* pQueue)
{
	(void)_memset(pQueue->buffer, 0, 256);
}

bool taskqueue_enqueue(TaskQueue* pQueue, Task* pTask)
{
	if (taskqueue_getFreeSpace(pQueue) >= 1)
	{
		pQueue->buffer[pQueue->writePos] = pTask;
		++pQueue->writePos;

		return TRUE;
	}
	return FALSE;
}

Task* taskqueue_dequeue(TaskQueue* pQueue)
{
	if (taskqueue_getUsedSpace(pQueue) >= 1)
	{
		Task* pTask = pQueue->buffer[pQueue->readPos];
		++pQueue->readPos;
		return pTask;
	}
	return NULL;
}

uint8 taskqueue_getFreeSpace(TaskQueue* pQueue)
{
	uint8 spaceInBuffer = (uint8)(pQueue->readPos - pQueue->writePos);
	if (spaceInBuffer == 0)
		return -1; //max uint8
	else
		return spaceInBuffer;
}

uint8 taskqueue_getUsedSpace(TaskQueue* pQueue)
{
	uint8 usedSpace = (uint8)(pQueue->writePos - pQueue->readPos);
	return usedSpace;
}

