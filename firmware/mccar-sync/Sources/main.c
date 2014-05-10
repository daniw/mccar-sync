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
#include "malloc.h"
#include "swappableMemory.h"

#define STEERING 0x2000

uint8 driveval = 0;
int16 trimsteering = 0;
uint8 tempbuf[8];

extern uint8 bt_readbuf[];
extern uint8 bt_readbufread;
extern uint8 bt_readbufwrite;
extern uint8 bt_sendbuf[];
extern uint8 bt_sendbufread;
extern uint8 bt_sendbufwrite;

/**
 * main program
 */
void main(void)
{
    uint16 speedleft = 0;
    uint16 speedright = 0;
    uint8 olddriveval;
    Direction_t d = STOP;
    uint16 line[8];
    enc_data_t data;
    Com_Status_t status;
    unsigned char myirtimer = 0;
    uint8 i;
    enc_setup_t setup;
    SwappableMemoryPool swappableMemoryPool;
    uint8 testData[10];
    uint8 bufferNo;
    setup.byte = 0x00;
    setup.flags.carrieren = 1;

    malloc_init();
    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on

    while(getjoystick() != PUSH){}  // Wait until joystick is pushed

    status = setupencoder(setup);
    PTED |= IR_FM;                  // switch front IR LED on to detect obstacles in front of MCCar

    swappableMemoryPool_init(&swappableMemoryPool, malloc_getPagePool(), &bt_enqueue);

    {
    	int i;
    	for (i = 0; i < 10; ++i)
    	{
    	    testData[i] = i + 20;
    	}
    }

    bufferNo = swappableMemoryPool_swapOut(&swappableMemoryPool, testData, sizeof(testData));

    {
    	int i;
    	for (i = 0; i < 10; ++i)
    	{
    	    testData[i] = 0;
    	}
    }
    swappableMemoryPool_requestSwapIn(&swappableMemoryPool, bufferNo, testData, sizeof(testData));
    while (swappableMemoryPool_isSwapInPending(&swappableMemoryPool, bufferNo))
    {
    	/*waiting*/
    }

    while (1)
    {
    	// read encoder
        status = readencoder(&data);

        // read ir sensor
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

        // get data from bt module
        if ((uint8)(bt_readbufwrite - bt_readbufread) >= 8)
        {
        	for (i = 0; i < 8; i++)
        	{
        		tempbuf[i] = bt_readbuf[bt_readbufread++];
        	}
        }
        if (tempbuf[0] == 0x01)
        {
        	driveval = tempbuf[1];
        }

        // control motors
        speedleft = 0xffff;
        speedright = 0xffff;
        if (trimsteering > 0)
        {
        	speedleft -= trimsteering;
        }
        else
        {
        	speedright += trimsteering;
        }

        switch (driveval & 0x0f)
        {
        case 0x01:
        	motorcontrol(FORWARD,speedleft,speedright);
        	break;
        case 0x09:
        	motorcontrol(FORWARD,speedleft - STEERING,speedright);
        	break;
        case 0x08:
        	motorcontrol(CURVELEFT,0x0000,speedright);
        	break;
        case 0x0C:
        	motorcontrol(BACKWARD,speedleft - STEERING,speedright);
        	break;
        case 0x04:
        	motorcontrol(BACKWARD,speedleft,speedright);
        	break;
        case 0x06:
        	motorcontrol(BACKWARD,speedleft,speedright - STEERING);
        	break;
        case 0x02:
        	motorcontrol(CURVERIGHT,speedleft,0x0000);
        	break;
        case 0x03:
        	motorcontrol(FORWARD,speedleft,speedright - STEERING);
        	break;
        case 0x00:
        	motorcontrol(STOP,0x0000,0x0000);
        	break;
        default:
        	motorcontrol(STOP,0x0000,0x0000);
        	break;
        }
        if (driveval & 0x10)
        {
        	trimsteering += 0x0001;
        }
        if (driveval & 0x20)
        {
        	trimsteering -= 0x0001;
        }
        /*switch (driveval & 0x30)
        {
        	case 0x10:
        		PTFD_PTFD1 = 0;
        		PTFD_PTFD2 = 1;
        		break;
        	case 0x20:
        		PTFD_PTFD1 = 1;
        		PTFD_PTFD2 = 0;
        		break;
        	case 0x30:
        		PTFD_PTFD1 = 0;
        		PTFD_PTFD2 = 0;
        		break;
        	default:
        		PTFD_PTFD1 = 1;
        		PTFD_PTFD2 = 1;
        		break;
        }*/
        if (driveval & 0x40)
        {
        	PTFD_PTFD3 ^= 1;
        }
        else
        {
        	PTFD_PTFD3 = 0;
        }
        if ((driveval & 0x80) && !(olddriveval & 0x80))
        {
            PTCD_PTCD4 ^= 1;
            PTCD_PTCD6 ^= 1;
            PTED_PTED7 ^= 1;
            PTFD_PTFD0 ^= 1;
            PTFD_PTFD1 ^= 1;
            PTFD_PTFD2 ^= 1;
        }
        olddriveval = driveval;
        {
        	uint8 *arr1, *arr2;
        	int i;
            arr1 = _malloc(sizeof(uint8) * 100);
            arr2 = _malloc(sizeof(uint8) * 100);
            _free(arr1);
            _free(arr2);

            for (i = 0; i < 100; ++i)
            {
            	arr1[i] = 0xff;
            }
            for (i = 0; i < 100; ++i)
            {
            	arr2[i] = 0xff;
            }
        }
    }


    for(;;)
    {
        __RESET_WATCHDOG();  /* feeds the dog */
    }

  /* please make sure that you never leave main */
}
