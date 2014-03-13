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

uint16 leftSpeeds[] =	{ 810, 960, 1010 };
uint16 rightSpeeds[] = 	{ 810, 960, 1010 };
//uint16 leftSpeeds2[] =  {  800,  825,  850,  875,  900,  925,  950,  975 };
//uint16 rightspeeds2[] = {  975,  950,  925,  900,  875,  850,  825,  800 };
//uint16 speeds[] =  { 800, 810, 820, 835, 860, 890, 930, 975 };
//uint16 speeds[] =  { 800, 850, 885, 910, 930, 945, 960, 975 };
//uint16 speeds[] =  { 750, 780, 810, 840, 870, 900, 930, 960 };
//uint16 speeds[] =  { 700, 740, 780, 820, 860, 900, 940, 980 };
//uint16 speeds[] =  { 700, 710, 740, 820, 920, 970, 990, 1000 };
//uint16 speeds[] =  { 700, 705, 720, 750, 810, 890, 930, 950 };
//uint16 speeds[] =  { 700, 780, 820, 840, 850, 870, 900, 940 };
//uint16 speeds[] =  { 700, 780, 860, 920, 960, 980, 990, 1000 };
//uint16 speeds[] =  { 650, 720, 790, 860, 920, 960, 985, 1000 };
//uint16 speeds[] =  { 600, 720, 820, 880, 920, 950, 975, 1000 };
//uint16 speeds[] =  { 600, 800, 950, 1000, 1000, 1000, 1000, 1000 };
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
    uint8 lowestline;
    uint16 lowestvalue;

    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on

    while(getjoystick() != PUSH){}  // Wait until joystick is pushed

    while(1)
    {
        getline(line);              // read line sensor

        leftspeed = 1010;
        rightspeed = 1010;

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
        motorcontrol(FORWARD, leftspeed, rightspeed);   // drive motors with calculated speed
    }
    
    for(;;) 
    {   
        __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
