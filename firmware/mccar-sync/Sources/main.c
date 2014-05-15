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
#include "util.h"
#include "pagepool.h"
#include "queue.h"
#include "scheduler.h"

#define STEERING 0x2000

uint8 driveval = 0;
int16 trimsteering = 0;

extern Queue bt_sendQueue;
extern Queue bt_receiveQueue;
extern uint8 bt_send_busy;

extern uint8 kp[];
extern uint8 ki[];
extern uint8 kd[];

extern uint8 ledleftred;
extern uint8 ledleftgreen;
extern uint8 ledleftblue;
extern uint8 ledrightred;
extern uint8 ledrightgreen;
extern uint8 ledrightblue;

Scheduler scheduler;

typedef struct
{
	uint8 command[SCI_CMD_AND_PAYLOAD_SIZE + 1];
	SwappableMemoryPool* pSwappableMemoryPool;
} MemoryPoolResponseData;

void handleMemoryPoolResponse(void* data)
{
	MemoryPoolResponseData* pData = data;

	swappableMemoryPool_handleResponse(pData->pSwappableMemoryPool, pData->command);

	_free(pData);
}

void handleSciReceive(SwappableMemoryPool* pSwappableMemoryPool)
{
	uint8 command[SCI_CMD_AND_PAYLOAD_SIZE + 1];
	while (queue_getUsedSpace(&bt_receiveQueue) >= sizeof(command))
	{
		if (!queue_dequeue(&bt_receiveQueue, command, sizeof(command)))
			FATAL_ERROR();

		switch (command[0])
		{
        // Null command
        case 0x00:
            // No valid command
            break;
        // Move
		case 0x01:
			{
				driveval = command[1];
			}
			break;
        // FollowLine
        case 0x02:
            // not implemented yet
            break;
        // ConfigPID
        case 0x03:
            kp[0] = command[1];
            ki[0] = command[2];
            kd[0] = command[3];
            kp[1] = command[4];
            ki[1] = command[5];
            kd[1] = command[6];
            break;
        // LEDColor
        case 0x04:
            ledleftred    = command[1];
            ledleftgreen  = command[2];
            ledleftblue   = command[3];
            ledrightred   = command[4];
            ledrightgreen = command[5];
            ledrightblue  = command[6];
            break;
        // Colorsensor
        case 0x05:
            // not implemented yet
            break;
        // Acceleration
        case 0x06:
            // not implemented yet
            break;
        // Beep
        case 0x07:
            // not implemented yet
            break;
        // RequestData
        case 0x08:
            // not implemented yet
            break;
        // WriteData
        case 0x09:
            // not implemented yet
            break;
        // HandleRequestedData
		case 0x0A:
			{
				MemoryPoolResponseData* pData = _malloc(sizeof(MemoryPoolResponseData));
				_memcpy(pData->command, command, SCI_CMD_AND_PAYLOAD_SIZE + 1);
				pData->pSwappableMemoryPool = pSwappableMemoryPool;
				scheduler_scheduleTask(&scheduler, handleMemoryPoolResponse, pData);
			}
			break;
        // Status
        case 0x0B:
            // not implemented yet
            break;
        // Display
        case 0x0C:
            // not implemented yet
            break;
		default:
			break;
		}
	}
}

SwappableMemoryPool swappableMemoryPool;

void taskEncoder(void* unused)
{
    enc_data_t data;
    Com_Status_t status;

	// read encoder
    status = readencoder(&data);

    scheduler_scheduleTask(&scheduler, taskEncoder, NULL);
}

void taskIrSensor(void* unused)
{
    static unsigned char myirtimer = 0;

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

    scheduler_scheduleTask(&scheduler, taskIrSensor, NULL);
}

void taskControlMotors(void* unused)
{
    static uint8 olddriveval = 0;
    uint16 speedleft = 0;
    uint16 speedright = 0;

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
        ledleftred    ^= 0xff;
        ledleftgreen  ^= 0xff;
        ledleftblue   ^= 0xff;
        ledrightred   ^= 0xff;
        ledrightgreen ^= 0xff;
        ledrightblue  ^= 0xff;
    }
    olddriveval = driveval;

    scheduler_scheduleTask(&scheduler, taskControlMotors, NULL);
}

void taskSciReceive(void* unused)
{
	handleSciReceive(&swappableMemoryPool);

    scheduler_scheduleTask(&scheduler, taskSciReceive, NULL);
}

void taskSendStatus(void* unused)
{
	static counter = 0;
	uint16 bufferNo;
	uint8 i;
	uint8 usedPages = 0;
	uint8 freePages;
	PagePool* pool;
	if ((++counter % 10000) == 0)
	{
		uint8 cmd[5];
		cmd[0] = 0x0d;
		cmd[1] = taskqueue_getUsedSpace(&scheduler.taskQueue);
		pool = malloc_getPagePool();
		for (i = 0; i < PAGE_POOL_SIZE; ++i)
		{
			usedPages += pool->amountOfOccupiedPagesAhead[i];
		}
		freePages = PAGE_POOL_SIZE - usedPages;
		cmd[2] = usedPages;
		cmd[3] = freePages;
		cmd[4] = PAGE_SIZE;
		bt_enqueue(cmd, sizeof(cmd));

		//test: sending up memory pool
	    bufferNo = swappableMemoryPool_swapOut(&swappableMemoryPool, pool->pages, sizeof(Page) * PAGE_POOL_SIZE);
	}

    scheduler_scheduleTask(&scheduler, taskSendStatus, NULL);
}

void init()
{
    Com_Status_t status;
    enc_setup_t setup;
    setup.byte = 0x00;
    setup.flags.carrieren = 1;
    setup.flags.oleden = 1;

    malloc_init();
    queue_init(&bt_sendQueue);
    queue_init(&bt_receiveQueue);
    swappableMemoryPool_init(&swappableMemoryPool, malloc_getPagePool(), &bt_enqueue);

    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on
    while(getjoystick() != PUSH){}  // Wait until joystick is pushed

    status = setupencoder(setup);
    PTED |= IR_FM;                  // switch front IR LED on to detect obstacles in front of MCCar
}

/**
 * main program
 */
void main(void)
{
    init();

	scheduler_init(&scheduler);

    //scheduler_scheduleTask(&scheduler, taskEncoder, NULL);
    scheduler_scheduleTask(&scheduler, taskIrSensor, NULL);
    scheduler_scheduleTask(&scheduler, taskControlMotors, NULL);
    scheduler_scheduleTask(&scheduler, taskSciReceive, NULL);
    scheduler_scheduleTask(&scheduler, taskSendStatus, NULL);

	scheduler_execute(&scheduler);

    for(;;)
    {
        __RESET_WATCHDOG();  /* feeds the dog */
    }

  /* please make sure that you never leave main */
}
