/*
 * taskQueue.c
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#include "taskQueue.h"

#include "malloc.h"
#include "util.h"

void taskqueue_init(TaskQueue* pQueue, uint8 bufferSize)
{
	pQueue->pBuffer = (Task**)_malloc(bufferSize * sizeof(Task*));
	pQueue->bufferSize = bufferSize;
	(void)_memset(pQueue->pBuffer, 0, pQueue->bufferSize);
}

bool taskqueue_enqueue(TaskQueue* pQueue, Task* pTask)
{
	if (taskqueue_getFreeSpace(pQueue) >= 1)
	{
		pQueue->pBuffer[pQueue->writePos] = pTask;
		++pQueue->writePos;
		pQueue->writePos %= pQueue->bufferSize;

		return TRUE;
	}
	return FALSE;
}

Task* taskqueue_dequeue(TaskQueue* pQueue)
{
	if (taskqueue_getUsedSpace(pQueue) >= 1)
	{
		Task* pTask = pQueue->pBuffer[pQueue->readPos];
		++pQueue->readPos;
		pQueue->readPos %= pQueue->bufferSize;
		return pTask;
	}
	return NULL;
}

uint8 taskqueue_getFreeSpace(TaskQueue* pQueue)
{
	uint8 spaceInBuffer = (uint8)((pQueue->readPos - pQueue->writePos) % pQueue->bufferSize);
	if (spaceInBuffer == 0)
		return -1; //max uint8
	else
		return spaceInBuffer;
}

uint8 taskqueue_getUsedSpace(TaskQueue* pQueue)
{
	uint8 usedSpace = (uint8)((pQueue->writePos - pQueue->readPos) % pQueue->bufferSize);
	return usedSpace;
}

