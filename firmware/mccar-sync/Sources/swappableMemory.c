/*
 * swappableMemory.c
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */


#include "swappableMemory.h"

uint8 swappableMemory_swapOut(SwappableMemoryPool* pPool, void* pData, uint8 size)
{
	uint8 pageNo = ++pPool->lastPageNo;
	char* pCharData = pData;
	uint8 i;
	
	for (i = 0; i < size;)
	{
		uint8 data[7] = { 0 };
		data[0] = 0x09;
		data[1] = pageNo;
		data[2] = i;
		data[3] = pCharData[i];
		if ((i + 1) < size)
			data[4] = pCharData[i + 1];
		
		if ((i + 2) < size)
			data[5] = pCharData[i + 2];

		if ((i + 3) < size)
			data[6] = pCharData[i + 3];
		
		i += 4;
		pPool->fnWriteBuf(data, 7);
	}
	
	return pageNo;
}

void swappableMemory_requestSwapIn(SwappableMemoryPool* pPool, uint8 bufferNo, void* pData, uint8 size)
{
	SwappableMemorySwapIn* pNewSwapInInfo;
	SwappableMemorySwapIn* pCurr;
	uint8 data[8] = { 0 };
	data[0] = 0x08;
	data[1] = bufferNo;

	pPool->fnWriteBuf(data, 3);
	
	pNewSwapInInfo = pagePool_malloc(pPool->pPagePool, sizeof(SwappableMemorySwapIn));
	
	pNewSwapInInfo->bufferNo = bufferNo;
	pNewSwapInInfo->next = NULL;
	pNewSwapInInfo->target = pData;
	pNewSwapInInfo->targetSize = size;
	pNewSwapInInfo->currentOffset = 0;
	
	pCurr = pPool->pAwaitingSwapIns;
	if (pCurr && pCurr->next)
	{
		pCurr = pCurr->next;
	}
	
	if (pCurr)
	{
		pCurr->next = pNewSwapInInfo;
	}
	else
	{
		pPool->pAwaitingSwapIns = pNewSwapInInfo;
	}
}

bool swappableMemory_isSwapInPending(SwappableMemoryPool* pPool, uint8 bufferNo)
{
	SwappableMemorySwapIn* pCurr = pPool->pAwaitingSwapIns;
	while (pCurr)
	{
		if (pCurr->bufferNo == bufferNo)
		{
			return TRUE;
		}
		pCurr = pCurr->next;
	}
	return FALSE;
}

void swappableMemory_handleResponse(SwappableMemoryPool* pPool, void* pData)
{
	uint8 i;
	bool finishedReading = FALSE;
	SwappableMemorySwapIn* pCurr;
	SwappableMemorySwapIn* pPrevCurr = NULL;
	uint8* pCharData = (uint8*)pData;
	uint8 bufferNo = pCharData[1];

	pCurr = pPool->pAwaitingSwapIns;
	while (pCurr)
	{
		if (pCurr->bufferNo == bufferNo)
		{
			for (i = 2; i < 7; ++i)
			{
				uint8* pDataTarget = (uint8*)pCurr->target;
				pDataTarget[++pCurr->currentOffset] = pCharData[i];
				if (pCurr->currentOffset >= pCurr->targetSize)
				{
					finishedReading = TRUE;
				}
			}
			if (finishedReading)
			{
				if (pPrevCurr)
				{
					pPrevCurr->next = pCurr->next;
				}
				else
				{
					pPool->pAwaitingSwapIns = NULL;
				}
				pagePool_free(pPool->pPagePool, pCurr);
			}
			
			return;
		}
		pPrevCurr = pCurr;
		pCurr = pCurr->next;
	}
}
