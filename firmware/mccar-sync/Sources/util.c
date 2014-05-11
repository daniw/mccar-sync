/*
 * util.c
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#include "platform.h"

void memset(void* pData, int value, int num)
{
	uint8* pRealData = (uint8*)pData;
	int i;
	for (i = 0; i < num; ++i)
	{
		pRealData[i] = value;
	}
}
