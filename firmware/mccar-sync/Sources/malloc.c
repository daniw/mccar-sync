/*
 * malloc.c
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#include "malloc.h"

#include "pagepool.h"

static PagePool pagePool;

void malloc_init(void)
{
	pagePool_init(&pagePool);
}

PagePool* malloc_getPagePool(void)
{
	return &pagePool;
}

void* _malloc(uint8 size)
{
	return pagePool_malloc(&pagePool, size);
}

void _free(void* pData)
{
	pagePool_free(&pagePool, pData);
}
