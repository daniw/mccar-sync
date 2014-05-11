/*
 * swappableMemory.c
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */


#include "swappableMemory.h"
#include "hardware.h"

#define HANDLE_RESPONSE_HEADER_SIZE 2

void swappableMemoryPool_init(SwappableMemoryPool* pPool, PagePool* pPagePool, callback_writeBuf fnWriteBuf)
{
	pPool->fnWriteBuf = fnWriteBuf;
	pPool->lastPageNo = 0;
	pPool->pAwaitingSwapIns = NULL;
	pPool->pPagePool = pPagePool;
}

uint16 swappableMemoryPool_swapOut(SwappableMemoryPool* pPool, void* pData, uint16 size)
{
	uint16 pageNo = ++pPool->lastPageNo;
	char* pCharData = pData;
	uint16 i;

	for (i = 0; i < size;)
	{
		uint8 data[SCI_CMD_AND_PAYLOAD_SIZE] = { 0 };
		data[0] = 0x09;
		data[1] = pageNo >> 8;
		data[2] = (uint8)pageNo;
		data[3] = i >> 8;
		data[4] = (uint8)i;
		
		{
			uint16 j;
			for (j = 0; j < (SCI_CMD_AND_PAYLOAD_SIZE - 5); ++j)
			{
				if ((i + j) < size)
					data[5 + j] = pCharData[i + j];
			}
		}

		i += (uint16)(SCI_CMD_AND_PAYLOAD_SIZE - 5);
		pPool->fnWriteBuf(data, SCI_CMD_AND_PAYLOAD_SIZE);
	}

	return pageNo;
}

void swappableMemoryPool_requestSwapIn(SwappableMemoryPool* pPool, uint16 bufferNo, void* pData, uint16 size)
{
	SwappableMemorySwapIn* pNewSwapInInfo;
	SwappableMemorySwapIn* pCurr;
	uint8 data[SCI_CMD_AND_PAYLOAD_SIZE] = { 0 };
	data[0] = 0x08;
	data[1] = bufferNo >> 8;
	data[2] = (uint8)bufferNo;

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

bool swappableMemoryPool_isSwapInPending(SwappableMemoryPool* pPool, uint16 bufferNo)
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

void swappableMemoryPool_handleResponse(SwappableMemoryPool* pPool, void* pData)
{
	uint8 i;
	bool finishedReading = FALSE;
	SwappableMemorySwapIn* pCurr;
	SwappableMemorySwapIn* pPrevCurr = NULL;
	uint8* pCharData = (uint8*)pData;
	uint16 bufferNo = ((uint8)pCharData[2]) | pCharData[1] << 8; 

	pCurr = pPool->pAwaitingSwapIns;
	while (pCurr)
	{
		if (pCurr->bufferNo == bufferNo)
		{
			for (i = HANDLE_RESPONSE_HEADER_SIZE + 1; i < SCI_CMD_AND_PAYLOAD_SIZE; ++i)
			{
				uint8* pDataTarget = (uint8*)pCurr->target;
				pDataTarget[pCurr->currentOffset++] = pCharData[i];
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
