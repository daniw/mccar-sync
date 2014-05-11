/*
 * pagepool.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#ifndef PAGEPOOL_H_
#define PAGEPOOL_H_

#include <platform.h>

#define PAGE_POOL_SIZE 20
#define PAGE_SIZE 1 * 32

typedef char Page[PAGE_SIZE];

typedef struct
{
	uint8 amountOfOccupiedPagesAhead[PAGE_POOL_SIZE];
	Page pages[PAGE_POOL_SIZE];
} PagePool;

void pagePool_init(PagePool* pagePool);
void* pagePool_malloc(PagePool* pagePool, uint8 size);
void pagePool_free(PagePool* pagePool, void* pData);

#endif /* PAGEPOOL_H_ */
