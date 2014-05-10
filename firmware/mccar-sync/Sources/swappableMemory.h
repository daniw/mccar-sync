/*
 * swappableMemory.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#ifndef SWAPPABLEMEMORY_H_
#define SWAPPABLEMEMORY_H_

#include "platform.h"
#include "pagePool.h"

typedef void(*callback_writeBuf)(uint8* pBuffer, uint8 bufferSize);

typedef struct SwappableMemorySwapInSTRUCT
{
	uint8 bufferNo;

	void* target;
	uint8 targetSize;
	uint8 currentOffset;
	
	struct SwappableMemorySwapInSTRUCT* next;
} SwappableMemorySwapIn;

typedef struct SwappableMemoryPoolSTRUCT
{
	PagePool* pPagePool;
	
	uint8 lastPageNo;
	callback_writeBuf fnWriteBuf;
	
	SwappableMemorySwapIn* pAwaitingSwapIns;
} SwappableMemoryPool;

typedef struct PagePoolSTRUCT PagePool;



#endif /* SWAPPABLEMEMORY_H_ */
