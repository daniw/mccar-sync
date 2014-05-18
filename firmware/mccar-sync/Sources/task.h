/*
 * task.h
 *
 *  Created on: May 15, 2014
 *      Author: daniw
 */

#ifndef TASK_H_
#define TASK_H_

#include "hardware.h"
#include "swappableMemory.h"
#include "queue.h"
#include "util.h"
#include "malloc.h"
#include "scheduler.h"
#include "i2c.h"
#include "encoder.h"

#define STEERING 0x2000

typedef struct
{
	uint8 command[SCI_CMD_AND_PAYLOAD_SIZE + 1];
	SwappableMemoryPool* pSwappableMemoryPool;
} MemoryPoolResponseData;

void handleMemoryPoolResponse(void* data);
void handleSciReceive(SwappableMemoryPool* pSwappableMemoryPool);
void taskEncoder(void* unused);
void taskIrSensor(void* unused);
void taskControlMotors(void* unused);
void taskSciReceive(void* unused);
void taskSendStatus(void* unused);
void taskSendRessource(void* unused);

#endif /* TASK_H_ */
