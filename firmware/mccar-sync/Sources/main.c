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



/**
 * main program
 */  
void main(void) 
{
    EnableInterrupts;       // Interrupts aktivieren
    
    for(;;) 
    {   
      __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
