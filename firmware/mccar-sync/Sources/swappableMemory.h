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

typedef void(*callback_writeBuf)(uint8* pBuffer, uint8 bufferSize);

typedef struct SwappableMemorySwapInSTRUCT
{
	uint16 bufferNo;

	void* target;
	uint16 targetSize;
	uint16 currentOffset;
	
	struct SwappableMemorySwapInSTRUCT* next;
} SwappableMemorySwapIn;

typedef struct SwappableMemoryPoolSTRUCT
{
	PagePool* pPagePool;
	
	uint16 lastPageNo; //TODO: register and free pages
	callback_writeBuf fnWriteBuf;
	
	SwappableMemorySwapIn* pAwaitingSwapIns;
} SwappableMemoryPool;

typedef struct PagePoolSTRUCT PagePool;

void swappableMemoryPool_init(SwappableMemoryPool* pPool, PagePool* pPagePool, callback_writeBuf fnWriteBuf);
uint16 swappableMemoryPool_swapOut(SwappableMemoryPool* pPool, void* pData, uint16 size); //! @returns bufferNo
void swappableMemoryPool_requestSwapIn(SwappableMemoryPool* pPool, uint16 bufferNo, void* pData, uint16 size);
bool swappableMemoryPool_isSwapInPending(SwappableMemoryPool* pPool, uint16 bufferNo);
void swappableMemoryPool_handleResponse(SwappableMemoryPool* pPool, void* pData);


#endif /* swappableMemoryPool_H_ */
