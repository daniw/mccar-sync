/*
 * malloc.h
 *
 *  Created on: May 10, 2014
 *      Author: Adrian
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include "platform.h"

void malloc_init(void);

void* _malloc(uint8 size);
void _free(void* pData);

#endif /* MALLOC_H_ */
