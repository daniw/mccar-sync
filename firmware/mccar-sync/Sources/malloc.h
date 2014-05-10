/*
 * malloc.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include "platform.h"

typedef struct PagePoolSTRUCT PagePool;

void malloc_init(void);
PagePool* malloc_getPagePool(void);

void* _malloc(uint8 size);
void _free(void* pData);

#endif /* MALLOC_H_ */
