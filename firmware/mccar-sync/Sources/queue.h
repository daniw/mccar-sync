/*
 * queue.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#include "platform.h"

typedef struct
{
	uint8* pBuffer;
	uint8 bufferSize;
	uint8 readPos;
	uint8 writePos;
} Queue;

void queue_init(Queue* pQueue, uint8 bufferSize);

uint8 queue_getFreeSpace(Queue* pQueue);
uint8 queue_getUsedSpace(Queue* pQueue);

bool queue_enqueue(Queue* pQueue, uint8* data, uint8 size);
bool queue_enqueueByte(Queue* pQueue, uint8 data);

bool queue_dequeue(Queue* pQueue, uint8* data, uint8 size);
uint8 queue_dequeueByte(Queue* pQueue);
