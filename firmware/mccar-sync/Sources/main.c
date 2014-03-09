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


/**
 * main program
 */  
void main(void) 
{
    uint16 i;
    uint16 j;
    Direction_t d = STOP;

    hardware_lowlevel_init();
    EnableInterrupts;       // Interrupts aktivieren

    // Switch rear LED on
    PTDD |= LED_B;

    while(1)
    {
        for (i = 255; i > 0; i--)   // negative ramp for testing PWM control
        {
            motorcontrol(d, i, i);
            
            for (j = 0; j < 40000; j++){}
        }

        d = d < BACKRIGHT ? d + 1 : STOP;   //switching through all possible motor directions
    }
    
    for(;;) 
    {   
        __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
