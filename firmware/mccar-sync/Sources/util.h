/*
 * util.h
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "platform.h"

/**
 * sets num bytes to value, starting from pData
 */
void _memset(void* pData, uint8 value, int num);

#define FATAL_ERROR() do { } while (1)

#endif /* UTIL_H_ */
