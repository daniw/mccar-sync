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
    uint32 i;
    EnableInterrupts;       // Interrupts aktivieren
    hardware_lowlevel_init();
    PTDD  |= LED_B;
    
    while(1)
    {
        PTDD ^= LED_B;
        for (i = 0; i < 100000; i++) {}
    }
    
    for(;;) 
    {   
        __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
