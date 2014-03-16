/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         C Template for the MC Car
 * \file
 * \author        Daniel Winz, Adrian Imboden
 * \date          06.03.2014
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC-Car  \n
 *
 * \par Description:
 *
 * $Id: main.c 485 2014-06-03 21:17:55Z daniw $
 *--------------------------------------------------------------------
 */
#include "platform.h"   /* include peripheral declarations */
#include "hardware.h"   /* include lowlevel hardware declarations */
#include "i2c.h"        /* include i2c module drivers */

#define STARTCMD 0x00
#define ENDCMD   0x0b

uint16 leftSpeeds[] =    { 730, 870, 910 };
uint16 rightSpeeds[] =   { 720, 860, 900 };
uint16 speeds[] =  { 500, 700, 800, 900, 970, 1000, 1000, 1000 };

/**
 * main program
 */  
void main(void) 
{
    uint16 leftspeed = 0;
    uint16 rightspeed = 0;
    uint16 i;
    Direction_t d = STOP;
    uint16 line[8];
    //uint8 lowestline;
    //uint16 lowestvalue;
    uint8 data[(ENDCMD - STARTCMD + 1)];
    Com_Status_t status;

    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on

    while(getjoystick() != PUSH){}  // Wait until joystick is pushed

    status = i2c_start(IIC_ADR_ENCODER, I2C_WRITE);
    status = i2c_sendbyte(0x00);
    status = i2c_sendbyte(0x10);
    i2c_stop();

    while (1)
    {
        status = i2c_start(IIC_ADR_ENCODER, I2C_WRITE);
        status = i2c_sendbyte(0x00);
//        status = i2c_sendbyte(0x10);
        status = i2c_restart(IIC_ADR_ENCODER, I2C_READ);
        i2c_readdata(data, sizeof(data));
        i2c_stop();
    }

    while (1)
    {
        getline(line);              // read line sensor

        leftspeed = 1010;           // Values for adi
        rightspeed = 1000;
//        leftspeed = 1020;           // Values for daniw
//        rightspeed = 980;

        for (i = 0; i < 3; ++i)     // calculate speed based on position of line below the car. 
        {
        	if (line[i] < 100)
        	{
                leftspeed = leftSpeeds[i];
        	}
        	if (line[7 - i] < 100)
        	{
                rightspeed = rightSpeeds[i];
        	}
        }
        
/*        lowestvalue = line[0];
        lowestline = 0;
        
        for (i = 1; i < 8; i++)
        {
            if (line[i] < lowestvalue)
            {
                lowestvalue = line[i];
                lowestline = (uint8) i;
            }
        }
        
        leftspeed = speeds[lowestline];
        rightspeed = speeds[7- lowestline];
*/
        //leftspeed = 1020;                             // Calibrating motors to drive straight
        //rightspeed = 980;
        motorcontrol(FORWARD, leftspeed, rightspeed);   // drive motors with calculated speed
    }
    
    for(;;) 
    {   
        __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
