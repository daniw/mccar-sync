/*
 * pid.h
 *
 *  Created on: May 8, 2014
 *      Author: daniw
 */

#ifndef PID_H_
#define PID_H_

#include "hardware.h"

typedef struct
{
	uint8 kp;
	uint8 ki;
	uint8 kd;
	
    uint32 e;
    uint32 olde;
    uint32 i;
    uint32 d;
} Pid;


void pid_init(Pid* pPid);
void pid_setCalibrationData(Pid* pPid, uint8 kp, uint8 ki, uint8 kd);
uint16 pid_calculate(Pid* pPid, uint16 currentspeed, uint16 targetspeed);

#endif /* PID_H_ */
