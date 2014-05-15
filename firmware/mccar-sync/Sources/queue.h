/*
 * queue.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "platform.h"

typedef struct
{
	uint8 buffer[256];
	uint8 readPos;
	uint8 writePos;
} Queue;

void queue_init(Queue* pQueue);

uint8 queue_getFreeSpace(Queue* pQueue);
uint8 queue_getUsedSpace(Queue* pQueue);

bool queue_enqueue(Queue* pQueue, uint8* data, uint8 size);
bool queue_enqueueByte(Queue* pQueue, uint8 data);

bool queue_dequeue(Queue* pQueue, uint8* data, uint8 size);
uint8 queue_dequeueByte(Queue* pQueue);

#endif /* QUEUE_H_ */
