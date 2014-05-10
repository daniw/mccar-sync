/*
 * swappableMemory.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#ifndef swappableMemoryPool_H_
#define swappableMemoryPool_H_

#include "platform.h"
#include "pagePool.h"

typedef uint8(*callback_writeBuf)(uint8* pBuffer, uint8 bufferSize);

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

void swappableMemoryPool_init(SwappableMemoryPool* pPool, PagePool* pPagePool, callback_writeBuf fnWriteBuf);
uint8 swappableMemoryPool_swapOut(SwappableMemoryPool* pPool, void* pData, uint8 size); //! @returns bufferNo
void swappableMemoryPool_requestSwapIn(SwappableMemoryPool* pPool, uint8 bufferNo, void* pData, uint8 size);
bool swappableMemoryPool_isSwapInPending(SwappableMemoryPool* pPool, uint8 bufferNo);
void swappableMemoryPool_handleResponse(SwappableMemoryPool* pPool, void* pData);


#endif /* swappableMemoryPool_H_ */
