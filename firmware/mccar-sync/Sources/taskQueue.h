/*
 * taskQueue.h
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#include "platform.h"

typedef struct
{
	void (*execute)(void* pData);
	void* pData;
} Task;

typedef struct
{
	Task** pBuffer;
	uint8 bufferSize;
	uint8 readPos;
	uint8 writePos;
} TaskQueue;

void taskqueue_init(TaskQueue* pQueue, uint8 bufferSize);

uint8 taskqueue_getFreeSpace(TaskQueue* pQueue);
uint8 taskqueue_getUsedSpace(TaskQueue* pQueue);

bool taskqueue_enqueue(TaskQueue* pQueue, Task* pTask);
Task* taskqueue_dequeue(TaskQueue* pQueue);

#endif /* TASKQUEUE_H_ */
