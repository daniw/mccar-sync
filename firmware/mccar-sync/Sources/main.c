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
#include "encoder.h"    /* include encoder driver */

/**
 * main program
 */
void main(void)
{
    Direction_t d = STOP;
    uint16 line[8];
    enc_data_t data;
    Com_Status_t status;
    unsigned char myirtimer = 0;
    enc_setup_t setup;
    setup.byte = 0x00;
    setup.flags.carrieren = 1;

    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on

    while(getjoystick() != PUSH){}  // Wait until joystick is pushed

    status = setupencoder(setup);
    PTED |= IR_FM;                  // switch front IR LED on to detect obstacles in front of MCCar

    while (1)
    {
        status = readencoder(&data);
        if(myirtimer++ < 3)
        {
            PTED |= IR_FM;
        }
        else
        {
            PTED &= ~IR_FM;
        }
        if((PTED & IR_RX_F))
        {
            PTDD &= ~LED_B;
        }
        else
        {
            PTDD |= LED_B;
        }
        if(myirtimer > 30)
        {
            myirtimer = 0;
        }
    }

    for(;;)
    {
        __RESET_WATCHDOG();  /* feeds the dog */
    }

  /* please make sure that you never leave main */
}
