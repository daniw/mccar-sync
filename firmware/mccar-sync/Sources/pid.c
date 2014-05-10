/*
 * pid.c
 *
 *  Created on: May 8, 2014
 *      Author: daniw
 */

#include "pid.h"

uint8 kp[2] = {0, 0};
uint8 ki[2] = {0, 0};
uint8 kd[2] = {0, 0};

uint16 pid(uint16 currentspeed, uint16 targetspeed, uint8 motor)
{
    static uint16 e[2] = {0, 0};
    static uint16 olde[2] = {0, 0};
    static uint32 p[2] = {0, 0};
    static uint32 i[2] = {0, 0};
    static uint32 d[2] = {0, 0};
    static uint32 w;

    e[motor] = targetspeed - currentspeed;
    p[motor] = kp[motor] * e[motor];
    i[motor] = i[motor] + ki[motor] * e[motor];
    d[motor] = kd[motor] * (e[motor] - olde[motor]);

    w = p[motor] + i[motor] + d[motor];
    w = w >> 8;
    if (w > 0xffff)
    {
        w = 0xffff;
    }

    return (uint16) w;
}
