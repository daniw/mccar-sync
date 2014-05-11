/*
 * queue.c
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#include "queue.h"

#include "malloc.h"
#include "util.h"

void queue_init(Queue* pQueue, uint8 bufferSize)
{
	pQueue->pBuffer = (uint8*)_malloc(bufferSize);
	pQueue->bufferSize = bufferSize;
	(void)_memset(pQueue->pBuffer, 0, pQueue->bufferSize);
}

uint8 queue_getFreeSpace(Queue* pQueue)
{
	uint8 spaceInBuffer = (uint8)((pQueue->readPos - pQueue->writePos) % pQueue->bufferSize);
	if (spaceInBuffer == 0)
		return -1; //max uint8
	else
		return spaceInBuffer;
}

uint8 queue_getUsedSpace(Queue* pQueue)
{
	uint8 usedSpace = (uint8)((pQueue->writePos - pQueue->readPos) % pQueue->bufferSize);
	return usedSpace;
}

bool queue_enqueue(Queue* pQueue, uint8* data, uint8 size)
{
	if (queue_getFreeSpace(pQueue) >= size)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			pQueue->pBuffer[pQueue->writePos] = *(data++);
			++pQueue->writePos;
			pQueue->writePos %= pQueue->bufferSize;
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
			*(data++) = pQueue->pBuffer[pQueue->readPos];
			pQueue->readPos = (pQueue->readPos + 1) % pQueue->bufferSize;
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
