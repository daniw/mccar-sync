/*
 * task.c
 *
 *  Created on: May 15, 2014
 *      Author: daniw
 */

#include "task.h"
#include "mcmath.h"
#include "pid.h"

extern Pid motorPid[2];

uint8 driveval = 0;
int16 trimsteering = 0;

extern Queue bt_sendQueue;
extern Queue bt_receiveQueue;

extern Scheduler scheduler;

extern uint8 kp[];
extern uint8 ki[];
extern uint8 kd[];

extern uint8 bt_send_busy;

extern uint8 ledleftred;
extern uint8 ledleftgreen;
extern uint8 ledleftblue;
extern uint8 ledrightred;
extern uint8 ledrightgreen;
extern uint8 ledrightblue;

extern uint16 linesensor[8];
extern uint8  linepos;
extern uint16 linewidth;
extern uint16 voltage;
extern uint16 current;
extern uint16 charge_status;

/**
 *
 */
void handleMemoryPoolResponse(void* data)
{
	MemoryPoolResponseData* pData = data;

	swappableMemoryPool_handleResponse(pData->pSwappableMemoryPool, pData->command);

	_free(pData);
}

/**
 * Task to handle received commands
 */
void handleSciReceive(SwappableMemoryPool* pSwappableMemoryPool)
{
	uint8 maxCommandsToProcessAtATime = 5;
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
        	pid_setCalibrationData(&motorPid[0], command[1], command[2], command[3]);
        	pid_setCalibrationData(&motorPid[1], command[4], command[5], command[6]);
            break;
        // LEDColor
        case 0x04:
            ledleftred    = command[1];
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

		if (--maxCommandsToProcessAtATime == 0)
			return; //abort
	}
}

SwappableMemoryPool swappableMemoryPool;

/**
 * Task to read the ir sensor to detect obstacles in front of the mccar
 */
void taskIrSensor(void* unused)
{
    static unsigned char myirtimer = 0;
	(void)unused;

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

/**
 * Task to manually control the movements of the mccar
 */
void taskControlMotors(void* unused)
{
	static uint16 maxSpeed = 500;
	static uint16 STEERING = 100;
    static uint8 olddriveval = 0;
    uint16 speedleft = 0;
    uint16 speedright = 0;
    enc_data_t encoderData;
    Com_Status_t status;
    Direction_t dir;
    (void)unused;
    
    switch (driveval & 0x0f)
    {
    case 0x01:
    	dir = FORWARD;
    	speedleft = maxSpeed;
    	speedright = maxSpeed;
    	break;
    case 0x09:
    	dir = FORWARD;
    	speedleft = maxSpeed - STEERING;
    	speedright = maxSpeed;
    	break;
    case 0x08:
    	dir = CURVELEFT;
    	speedleft = 0x0000;
    	speedright = maxSpeed;
    	break;
    case 0x0C:
    	dir = BACKWARD;
    	speedleft = maxSpeed - STEERING;
    	speedright = maxSpeed;
    	break;
    case 0x04:
    	dir = BACKWARD;
    	speedleft = maxSpeed;
    	speedright = maxSpeed;
    	break;
    case 0x06:
    	dir = BACKWARD;
    	speedleft = maxSpeed;
    	speedright = maxSpeed - STEERING;
    	break;
    case 0x02:
    	dir = CURVERIGHT;
    	speedleft = maxSpeed;
    	speedright = 0x0000;
    	break;
    case 0x03:
    	dir = FORWARD;
    	speedleft = maxSpeed;
    	speedright = maxSpeed - STEERING;
    	break;
    case 0x00:
    	dir = STOP;
    	speedleft = 0x0000;
    	speedright = 0x0000;
    	break;
    default:
    	dir = STOP;
    	speedleft = 0x0000;
    	speedright = 0x0000;
    	break;
    }

	// read encoder
    status = readencoder(&encoderData);

	motorcontrol(
		dir,
		pid_calculate(&motorPid[0], encoderData.fields.speed_l, speedleft),
		pid_calculate(&motorPid[1], encoderData.fields.speed_r, speedright));
    
    
    
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
    	if (ledleftred)
    	{
            ledleftred    = 0x00;
            ledleftgreen  = 0x00;
            ledleftblue   = 0x00;
            ledrightred   = 0x00;
            ledrightgreen = 0x00;
            ledrightblue  = 0x00;
    	}
    	else
    	{
    		ledleftred    = 0xff;
            ledleftgreen  = 0xff;
            ledleftblue   = 0xff;
            ledrightred   = 0xff;
            ledrightgreen = 0xff;
            ledrightblue  = 0xff;
    	}
    }
    olddriveval = driveval;

    scheduler_scheduleTask(&scheduler, taskControlMotors, NULL);
}

/**
 * Task to handle received commands through the SCI
 */
void taskSciReceive(void* unused)
{
    (void)unused;
	handleSciReceive(&swappableMemoryPool);

    scheduler_scheduleTask(&scheduler, taskSciReceive, NULL);
}

/**
 * Task to send battery voltage, supply current and charge status to host computer
 */
void taskSendStatus(void* unused)
{
	static counter = 500;
    (void)unused;
	if ((++counter % 1000) == 0)
	{
		uint8 cmd[10];
		cmd[0] = 0x0b;
		cmd[1] = (uint8) (voltage >> 8);
		cmd[2] = (uint8) (voltage);
		cmd[3] = (uint8) (current >> 8);
		cmd[4] = (uint8) (current);
		cmd[5] = (uint8) (charge_status >> 8);
		cmd[6] = (uint8) (charge_status);
		cmd[7] = linepos;
		cmd[8] = (uint8) (linewidth >> 8);
		cmd[9] = (uint8) (linewidth);
		bt_enqueue_crc(cmd, sizeof(cmd));
	}
	scheduler_scheduleTask(&scheduler, taskSendStatus, NULL);
}

/**
 * Task to send actual memory and buffer usage to host computer
 */
void taskSendRessource(void* unused)
{
	static counter = 0;
	uint8 i;
	uint8 usedPages = 0;
	uint8 freePages;
	PagePool* pool;
    (void)unused;
	if ((++counter % 1000) == 0)
	{
		uint8 cmd[7];
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
		cmd[5] = queue_getUsedSpace(&bt_receiveQueue);
		cmd[6] = queue_getFreeSpace(&bt_receiveQueue);
		bt_enqueue_crc(cmd, sizeof(cmd));

		//test: sending up memory pool
	    //bufferNo = swappableMemoryPool_swapOut(&swappableMemoryPool, pool->pages, sizeof(Page) * PAGE_POOL_SIZE);
	}

    scheduler_scheduleTask(&scheduler, taskSendRessource, NULL);
}

/**
 * Task to calculate the actual position and width of the line below
 */
void taskCalcLine(void* unused)
{
	static counter = 250;
	uint16 linesensorcorr[8];
	uint8 i;
	uint16 max = 0;
    (void)unused;
	if ((++counter % 1000) == 0)
	{
		// invert results for detecting a black line, not needed for a white line
		for (i = 0; i < 8; i++)
		{
			max = linesensor[i] > max ? linesensor[i] : max;
		}
		for (i = 0; i < 8; i++)
		{
			linesensorcorr[i] = max - linesensor[i];
		}
		// Calculate Position
		linepos = expv(linesensorcorr, 8);
		linewidth = var2(linesensorcorr, 8, linepos);
	}
	scheduler_scheduleTask(&scheduler, taskCalcLine, NULL);
}
