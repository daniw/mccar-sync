/*
 * pagepool.c
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#include "pagepool.h"

void pagePool_init(PagePool* pagePool)
{
	int i;
	for (i = 0; i < PAGE_POOL_SIZE; ++i)
	{
		pagePool->amountOfOccupiedPagesAhead[i] = 0;
	}
}

void* pagePool_malloc(PagePool* pagePool, uint8 size)
{
	uint8 i;
	uint8 firstFreePage = 0;
	uint8 amountOfContinuousPages = 0;
	for (i = 0; i < PAGE_POOL_SIZE; i++)
	{
		if (pagePool->amountOfOccupiedPagesAhead[i] == 0)
		{
			if (amountOfContinuousPages == 0)
			{
				firstFreePage = i;
			}
			
			++amountOfContinuousPages;
			
			if (amountOfContinuousPages * sizeof(Page) >= size)
			{
				pagePool->amountOfOccupiedPagesAhead[firstFreePage] = amountOfContinuousPages;
				return pagePool->pages[firstFreePage];
			}
		}
		else
		{
			i += (pagePool->amountOfOccupiedPagesAhead[i] - 1);
			amountOfContinuousPages = 0;
		}
	}
	
	return NULL;
}

void pagePool_free(PagePool* pagePool, void* pData)
{
	if (pData)
	{
		Page* pDataPage = pData;
		uint8 pageIndex = (uint8)(pDataPage - &pagePool->pages[0]);
		pagePool->amountOfOccupiedPagesAhead[pageIndex] = 0;
	}
}
