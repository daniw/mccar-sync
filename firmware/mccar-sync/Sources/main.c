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

/*
        if (line[7] > 30)
        {
            if (leftspeed + MOTINC <= 1023)
            {
                leftspeed += MOTINC;
            }
            else
            {
                leftspeed = 1023;
            }
        }
        else
        {
            if (leftspeed >= MOTDEC)
            {
                leftspeed -= MOTDEC;
            }
            else
            {
                leftspeed = 0;
            }
        }

        if (line[0] > 700)
        {
            if (rightspeed + MOTINC <= 1023)
            {
                rightspeed += MOTINC;
            }
            else
            {
                rightspeed = 1023;
            }
        }
        else
        {
            if (rightspeed >= MOTDEC)
            {
                rightspeed -= MOTDEC;
            }
            else
            {
                rightspeed = 0;
            }
        }
*/



        if (line[0] > 100)
        {
            leftspeed = 950;
        }
        else
        {
            leftspeed = 0;
        }

        if (line[7] > 100)
        {
            rightspeed = 950;
        }
        else
        {
            rightspeed = 0;
        }


        motorcontrol(FORWARD, leftspeed, rightspeed);
        
        for (i = 0; i < 100; i++){}
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
