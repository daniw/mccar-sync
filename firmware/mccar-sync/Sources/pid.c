/*
 * pid.c
 *
 *  Created on: May 8, 2014
 *      Author: daniw
 */

#include "pid.h"

#include "util.h"

void pid_init(Pid* pPid)
{
	_memset(pPid, 0, sizeof(Pid));
	
	pPid->kp = 50;
}

void pid_setCalibrationData(Pid* pPid, uint8 kp, uint8 ki, uint8 kd)
{
	pPid->kp = kp;
	pPid->ki = ki;
	pPid->kd = kd;
}

/**
 * pid control system to control the mccars speed
 * this function has to be called within a fixed period
 */
uint16 pid_calculate(Pid* pPid, uint16 currentspeed, uint16 targetspeed)
{
    uint32 p;
    uint32 w;

    pPid->e = targetspeed - currentspeed;
    p = pPid->kp * pPid->e;
    pPid->i = pPid->i + pPid->ki * pPid->e;
    pPid->d = pPid->kd * (pPid->e - pPid->olde);

    w = p + pPid->i + pPid->d;
    w = w << 2;
    if (w > 0xffff)
    {
        w = 0xffff;
    }
    
    pPid->olde = pPid->e;

    return (uint16)w;
}
