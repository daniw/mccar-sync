/*
 * interrupts.c
 *
 *  Created on: Mar 15, 2014
 *      Author: daniw
 */
#include "interrupts.h"

#include "queue.h"
#include "util.h"

#include "task.h"

extern Scheduler scheduler;

extern uint8* bt_dataptr;
extern uint8 bt_datacnt;
extern uint8 driveval;

extern Queue bt_sendQueue;
extern Queue bt_receiveQueue;
extern uint8 bt_send_busy;

extern uint8 ledleftred;
extern uint8 ledleftgreen;
extern uint8 ledleftblue;
extern uint8 ledrightred;
extern uint8 ledrightgreen;
extern uint8 ledrightblue;

extern uint16 linesensor[8];
extern uint16 voltage;
extern uint16 current;
extern uint16 charge_status;

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
	static int adcstate = 0;
	static int linedark = 0;
	switch (adcstate)
    {
        case 0:     // let the filters settle
            PTAD |= LS_LED_MASK;
            ADCSC1_ADCH = 7;
            adcstate = 1;
            break;
        case 1:     // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD4 = 0;
            ADCSC1_ADCH = 7;
            adcstate = 2;
            break;
        case 2:     // let the filters settle
            ADCSC1_ADCH = 7;
            adcstate = 3;
            break;
        case 3:     // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[0] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 7;
            adcstate = 4;
            break;
        case 4:     // let the filters settle
            ADCSC1_ADCH = 7;
            adcstate = 5;
            break;
        case 5:     // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD3 = 0;
            ADCSC1_ADCH = 7;
            adcstate = 6;
            break;
        case 6:     // let the filters settle
            ADCSC1_ADCH = 7;
            adcstate = 7;
            break;
        case 7:     // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[1] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 6;
            adcstate = 8;
            break;
        case 8:     // let the filters settle
            ADCSC1_ADCH = 6;
            adcstate = 9;
            break;
        case 9:     // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD3 = 0;
            ADCSC1_ADCH = 6;
            adcstate = 10;
            break;
        case 10:    // let the filters settle
            ADCSC1_ADCH = 6;
            adcstate = 11;
            break;
        case 11:    // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[2] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 6;
            adcstate = 12;
            break;
        case 12:    // let the filters settle
            ADCSC1_ADCH = 6;
            adcstate = 13;
            break;
        case 13:    // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD2 = 0;
            ADCSC1_ADCH = 6;
            adcstate = 14;
            break;
        case 14:    // let the filters settle
            ADCSC1_ADCH = 6;
            adcstate = 15;
            break;
        case 15:    // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[3] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 5;
            adcstate = 16;
            break;
        case 16:    // let the filters settle
            ADCSC1_ADCH = 5;
            adcstate = 17;
            break;
        case 17:    // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD2 = 0;
            ADCSC1_ADCH = 5;
            adcstate = 18;
            break;
        case 18:    // let the filters settle
            ADCSC1_ADCH = 5;
            adcstate = 19;
            break;
        case 19:    // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[4] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 5;
            adcstate = 20;
            break;
        case 20:    // let the filters settle
            ADCSC1_ADCH = 5;
            adcstate = 21;
            break;
        case 21:    // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD1 = 0;
            ADCSC1_ADCH = 5;
            adcstate = 22;
            break;
        case 22:    // let the filters settle
            ADCSC1_ADCH = 5;
            adcstate = 23;
            break;
        case 23:    // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[5] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 4;
            adcstate = 24;
            break;
        case 24:    // let the filters settle
            ADCSC1_ADCH = 4;
            adcstate = 25;
            break;
        case 25:    // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD1 = 0;
            ADCSC1_ADCH = 4;
            adcstate = 26;
            break;
        case 26:    // let the filters settle
            ADCSC1_ADCH = 4;
            adcstate = 27;
            break;
        case 27:    // switch all line sensor led off, read the bright value
            PTAD |= LS_LED_MASK;
            linesensor[6] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 4;
            adcstate = 28;
            break;
        case 28:    // let the filters settle
            ADCSC1_ADCH = 4;
            adcstate = 29;
            break;
        case 29:    // read dark value and switch ir led on
            linedark = ADCR;
            PTAD_PTAD0 = 0;
            ADCSC1_ADCH = 4;
            adcstate = 30;
            break;
        case 30:    // let the filters settle
            ADCSC1_ADCH = 4;
            adcstate = 31;
            break;
        case 31:    // switch all line sensor led off, read the bright value, start current measurement
            PTAD |= LS_LED_MASK;
            linesensor[7] = ADCR > linedark ? ADCR - linedark : 0;
            ADCSC1_ADCH = 8;
            adcstate = 32;
//            scheduler_scheduleTask(&scheduler, taskCalcLine, NULL);
            break;
        case 32:    // measure current, start voltage measurement
            current = ADCR;
            ADCSC1_ADCH = 9;
            adcstate = 33;
            break;
        case 33:    // measure voltage, start charge state measurement
            voltage = ADCR;
            ADCSC1_ADCH = 10;
            adcstate = 34;
            break;
        case 34:    // measure charge status, start line sensor measurement
            charge_status = ADCR;
            PTAD |= LS_LED_MASK;
            ADCSC1_ADCH = 0;
            adcstate = 0;
            break;
        default:    // not defined adc state entered, throw away result and start line sensor measurement
            PTAD |= LS_LED_MASK;
            ADCSC1_ADCH = 0;
            adcstate = 0;
            break;
	}
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
		if (queue_getUsedSpace(&bt_sendQueue) > 0)
		{
			SCI1D = queue_dequeueByte(&bt_sendQueue);
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
		queue_enqueueByte(&bt_receiveQueue, SCI1D);
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
    static uint8 cnt = 0;
    struct
    {
    	uint8 leftred    : 1;
        uint8 leftgreen  : 1;
        uint8 leftblue   : 1;
        uint8 rightred   : 1;
        uint8 rightgreen : 1;
        uint8 rightblue  : 1;
        uint8 unused     : 2;
    } color;

    TPM2SC_TOF = 0;
    if (cnt == 0)
    {
        color.leftred    = 0;       // left red on
        color.leftgreen  = 0;       // left green on
        color.leftblue   = 0;       // left blue on
        color.rightred   = 0;       // right red on
        color.rightgreen = 0;       // right green on
        color.rightblue  = 0;       // right blue on
    }
    if (ledleftred <= cnt)
    {
        color.leftred    = 1;       // left red off
    }
    if (ledleftgreen <= cnt)
    {
        color.leftgreen  = 1;       // left green off
    }
    if (ledleftblue <= cnt)
    {
        color.leftblue   = 1;       // left blue off
    }
    if (ledrightred <= cnt)
    {
        color.rightred   = 1;       // right red off
    }
    if (ledrightgreen <= cnt)
    {
        color.rightgreen = 1;       // right green off
    }
    if (ledrightblue <= cnt)
    {
        color.rightblue  = 1;       // right blue off
    }
    PTFD_PTFD1 = color.leftred;     // left red
    PTCD_PTCD4 = color.leftgreen;   // left green
    PTFD_PTFD0 = color.leftblue;    // left blue
    PTFD_PTFD4 = color.rightred;    // right red
    PTCD_PTCD6 = color.rightgreen;  // right green
    PTED_PTED7 = color.rightblue;   // right blue
    cnt++;
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

