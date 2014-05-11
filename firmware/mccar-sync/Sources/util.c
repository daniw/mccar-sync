/*
 * util.c
 *
 *  Created on: May 11, 2014
 *      Author: Adrian
 */

#include "util.h"

void _memset(void* pData, uint8 value, int num)
{
	uint8* pRealData = (uint8*)pData;
	int i;
	for (i = 0; i < num; ++i)
	{
		pRealData[i] = value;
	}
}

void _memcpy(void* pSrc, void* pTarget, int num)
{
	uint8* pRealSrc = (uint8*)pSrc;
	uint8* pRealTarget = (uint8*)pTarget;
	int i;
	for (i = 0; i < num; ++i)
	{
		pRealTarget[i] = pRealSrc[i];
	}
}
