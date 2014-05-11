/*
 * mcmath.h
 *
 *  Created on: May 10, 2014
 *      Author: daniw
 */

#ifndef MCMATH_H_
#define MCMATH_H_

#include "platform.h"

#define STATSHIFT 5			// Shift statistic results by this value
							// Change this value for different sizes than 8.

uint8 expv(uint16* x, uint8 size);
uint16 var1(uint16* x, uint8 size);
uint16 var2(uint16* x, uint8 size, uint8 expv);

#endif /* MCMATH_H_ */
