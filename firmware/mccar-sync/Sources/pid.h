/*
 * pid.h
 *
 *  Created on: May 8, 2014
 *      Author: daniw
 */

#ifndef PID_H_
#define PID_H_

#include "hardware.h"

uint16 pid(uint16 currentspeed, uint16 targetspeed, uint8 motor);

#endif /* PID_H_ */
