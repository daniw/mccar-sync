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
#include "platform.h" /* include peripheral declarations */
#include "hardware.h" /* include lowlevel hardware declarations */

#define MOTINC 1
#define MOTDEC 10

uint8 leftSpeeds[] =	{ 810, 960, 1010 };
uint8 rightSpeeds[] = 	{ 800, 950, 1000 };
    
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

    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on

    while(1)
    {
        getline(line);

        for (i = 0; i < 3; ++i)
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

        motorcontrol(FORWARD, leftspeed, rightspeed);
        
        //motorcontrol(FORWARD, line[0]/4, line[7]/4);
        /*
        for (i = 1023; i > 0; i--)   // negative ramp for testing PWM control
        {
            motorcontrol(d, i, i);
            
            for (j = 0; j < 10000; j++){}
        }

        d = d < BACKRIGHT ? d + 1 : STOP;   //switching through all possible motor directions
        */
    }
    
    for(;;) 
    {   
        __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
