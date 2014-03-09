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

        d = d < BACKRIGHT ? d + 1 : STOP;   //switching through all motor directions

        /*
        switch(PTGD & (SW_JOY_0 | SW_JOY_1 | SW_JOY_2))
        {
            case 4: // Up
                PTDD |= MOTL_B | MOTR_A;
                PTDD &= ~(MOTL_A | MOTR_B);
                PTCD &= ~(LED_FL_G | LED_FR_G);
                PTED &= ~(LED_FR_B);
                PTFD &= ~(LED_FL_B | LED_FL_R | LED_FR_R);
                break;
            case 3: // Right
                PTDD |= MOTR_A;
                PTDD &= ~(MOTL_A | MOTL_B | MOTR_B);
                PTCD &= ~(LED_FR_G);
                PTED &= ~(LED_FR_B);
                PTFD &= ~(LED_FR_R);
                PTCD |= LED_FL_G;
                PTFD |= LED_FL_B | LED_FL_R;
                break;
            case 6: // Down
                PTDD |= MOTL_A | MOTR_B;
                PTDD &= ~(MOTL_B | MOTR_A);
                PTCD &= ~(LED_FL_G | LED_FR_G);
                //PTED &= ~(LED_FR_B);
                //PTFD &= ~(LED_FL_B | LED_FL_R | LED_FR_R);
                PTED |= LED_FR_B;
                PTFD |= LED_FL_B | LED_FL_R | LED_FR_R;
                break;
            case 5: // Left
                PTDD |= MOTL_B;
                PTDD &= ~(MOTL_A | MOTR_A | MOTR_B);
                PTCD &= ~(LED_FL_G);
                PTFD &= ~(LED_FL_B | LED_FL_R);
                PTCD |= LED_FR_G;
                PTED |= LED_FR_B;
                PTFD |= LED_FR_R;
                break;
            case 2: // Push
                PTDD |= MOTL_A | MOTR_A;
                PTDD &= ~(MOTL_B | MOTR_B);
                PTED &= ~(LED_FR_B);
                PTFD &= ~(LED_FL_B);
                PTCD |= LED_FL_G | LED_FR_G;
                PTFD |= LED_FL_R | LED_FR_R;
                break;
            default:
                if (!(PTGD & SW_MODE))
                {
                    PTDD &= ~(MOTL_A | MOTL_B | MOTR_A | MOTR_B);
                    PTCD |= LED_FL_G | LED_FR_G;
                    PTED |= LED_FR_B;
                    PTFD |= LED_FL_B | LED_FL_R | LED_FR_R;
                }
                break;
        }*/
    }
    
    for(;;) 
    {   
        __RESET_WATCHDOG();  /* feeds the dog */
    }
    
  /* please make sure that you never leave main */
}
