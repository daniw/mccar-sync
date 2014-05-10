/*
 * mcmath.c
 *
 *  Created on: May 10, 2014
 *      Author: daniw
 */

#include "mcmath.h"

//-- --
// This function is created for 12 Bit values as x
// and a size of 8.
// For other values the boundaries need to be rechecked
uint8 expv(uint16* x, uint8 size)
{
	uint8 i;
	uint32 z = 0;
	uint16 n = 0;
	for (i = 0; i < size; i++)
	{
		z += i * x[i];
		n += x[i];
	}
	z = z << STATSHFIT;
	z = z / n;
	return (uint8) z;
}

//-- --
// This function is created for 12 Bit values as x
// and a size of 8.
// For other values the boundaries need to be rechecked
uint16 var(uint16* x, uint8 size)
{
	uint8 expv = expv(x, size);
	return var(x, size, expv);
}

//-- --
// This function is created for 12 Bit values as x
// and a size of 8.
// For other values the boundaries need to be rechecked
uint16 var(uint16* x, uint8 size, uint8 expv)
{
	uint8 i;
	uint32 z;
	uint16 n;
	for (i = 0; i < size; i++)
	{
		z += ((i << STATSHIFT) - exp)*(i - expv)*(x[i]);
		n += x[i];
	}
	z = z / n;
	return (uint16) z;
}
