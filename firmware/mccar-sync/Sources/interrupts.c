/*
 * interrupts.c
 *
 *  Created on: Mar 15, 2014
 *      Author: daniw
 */
#include "interrupts.h"

extern uint8* bt_dataptr;
extern uint8 bt_datacnt;
extern uint8 driveval;

extern uint8 bt_readbuf[];
extern uint8 bt_readbufread;
extern uint8 bt_readbufwrite;
extern uint8 bt_sendbuf[];
extern uint8 bt_sendbufread;
extern uint8 bt_sendbufwrite;
extern uint8 bt_send_busy;

interrupt void isr_RTC(void)        // RTC
{
    return;
}

interrupt void isr_IIC(void)        // IIC
{
    return;
}

interrupt void isr_ACMP(void)       // ACMP
{
    return;
}

interrupt void isr_ADC(void)        // ADC Conversion
{
    return;
}

interrupt void isr_KBI(void)        // KBI Keyboard
{
    return;
}

interrupt void isr_SCI2T(void)      // SCI2 transmit
{
    return;
}

interrupt void isr_SCI2R(void)      // SCI2 receive
{
    return;
}

interrupt void isr_SCI2E(void)      // SCI2 error
{
    return;
}

interrupt void isr_SCI1T(void)      // SCI1 transmit
{
	if (SCI1S1_TC)
	{
		uint16 i;
		if ((uint8)(bt_sendbufwrite - bt_sendbufread) > 0)
		{
			SCI1D = bt_sendbuf[bt_sendbufread++];
		}
		else
		{
			bt_send_busy = FALSE;
			SCI1C2_TCIE = 0;
		}
	}
    return;
}

interrupt void isr_SCI1R(void)      // SCI1 receive
{
	uint8 temp;
	if (SCI1S1_RDRF)
	{

		temp = SCI1D;
		//SCI1D = temp;  	// Echo
		bt_readbuf[bt_readbufwrite++] = temp;
	}
	else
	{
		temp = SCI1D;
	}
    return;
}

interrupt void isr_SCI1E(void)      // SCI1 error
{
    return;
}

interrupt void isr_TPM2O(void)      // TPM2 overflow
{
return;
}

interrupt void isr_TPM2CH1(void)    // TPM2 channel 1
{
    return;
}

interrupt void isr_TPM2CH0(void)    // TPM2 channel 0
{
    return;
}

interrupt void isr_TPM1O(void)      // TPM1 overflow
{
    return;
}

interrupt void isr_TPM1CH5(void)    // TPM1 channel 5
{
    return;
}

interrupt void isr_TPM1CH4(void)    // TPM1 channel 4
{
    return;
}

interrupt void isr_TPM1CH3(void)    // TPM1 channel 3
{
    return;
}

interrupt void isr_TPM1CH2(void)    // TPM1 channel 2
{
    return;
}

interrupt void isr_TPM1CH1(void)    // TPM1 channel 1
{
    return;
}

interrupt void isr_TPM1CH0(void)    // TPM1 channel 0
{
    return;
}

interrupt void isr_USB(void)        // USB
{
    return;
}

interrupt void isr_SPI2(void)       // SPI2
{
    return;
}

interrupt void isr_SPI1(void)       // SPI1
{
    return;
}

interrupt void isr_MCGLOL(void)     // MCGLOL (Loss of Lock)
{
    return;
}

interrupt void isr_LowVoltage(void) // Low voltage detect
{
    return;
}

interrupt void isr_IRQ(void)        // IRQ
{
    return;
}

interrupt void isr_SWI(void)        // SWI
{
    return;
}

