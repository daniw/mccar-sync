/*
 * queue.c
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#include "queue.h"

#include "malloc.h"
#include "util.h"

void queue_init(Queue* pQueue)
{
	(void)_memset(pQueue->buffer, 0, 256);
}

uint8 queue_getFreeSpace(Queue* pQueue)
{
	uint8 spaceInBuffer = (uint8)(pQueue->readPos - pQueue->writePos);
	if (spaceInBuffer == 0)
		return -1; //max uint8
	else
		return spaceInBuffer;
}

uint8 queue_getUsedSpace(Queue* pQueue)
{
	uint8 usedSpace = (uint8)(pQueue->writePos - pQueue->readPos);
	return usedSpace;
}

bool queue_enqueue(Queue* pQueue, uint8* data, uint8 size)
{
	if (queue_getFreeSpace(pQueue) >= size)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			pQueue->buffer[pQueue->writePos] = *(data++);
			++pQueue->writePos;
		}

		return TRUE;
	}
	return FALSE;
}

bool queue_enqueueByte(Queue* pQueue, uint8 data)
{
	return queue_enqueue(pQueue, &data, 1);
}

bool queue_dequeue(Queue* pQueue, uint8* data, uint8 size)
{
	if (queue_getUsedSpace(pQueue) >= size)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			*(data++) = pQueue->buffer[pQueue->readPos];
			++pQueue->readPos;
		}
		return TRUE;
	}
	return FALSE;
}

uint8 queue_dequeueByte(Queue* pQueue)
{
	uint8 value;
	if (!queue_dequeue(pQueue, &value, 1))
		FATAL_ERROR();
	
	return value;
}
