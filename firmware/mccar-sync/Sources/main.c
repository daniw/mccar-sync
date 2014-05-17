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

//#define BT_PRG

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
#include "task.h"
#include "bluetooth.h"

extern Queue bt_sendQueue;
extern Queue bt_receiveQueue;
extern uint8 bt_send_busy;

extern uint8 ledleftred;
extern uint8 ledleftgreen;
extern uint8 ledleftblue;
extern uint8 ledrightred;
extern uint8 ledrightgreen;
extern uint8 ledrightblue;

extern SwappableMemoryPool swappableMemoryPool;

Scheduler scheduler;

void init()
{
    Com_Status_t status;
    enc_setup_t setup;
    bt_uartparam_t param;
    uint32 i;
    setup.byte = 0x00;
    setup.flags.carrieren = 1;
    setup.flags.oleden = 1;

    malloc_init();
    queue_init(&bt_sendQueue);
    queue_init(&bt_receiveQueue);
    swappableMemoryPool_init(&swappableMemoryPool, malloc_getPagePool(), &bt_enqueue_crc);

    hardware_lowlevel_init();
    EnableInterrupts;               // Interrupts aktivieren

    PTDD |= LED_B;                  // Switch rear LED on
    while(getjoystick() != PUSH){}  // Wait until joystick is pushed

    status = setupencoder(setup);
    PTED |= IR_FM;                  // switch front IR LED on to detect obstacles in front of MCCar

    param.baud = BT_BAUD_115200;
    param.parity = NOPARITY;
    param.stop = ONE;

    #ifdef BT_PRG
    	PTFD_PTFD1 = 0;
        bt_cmdon();
        //for (i = 0; i < 10000; i++);
        bt_setparam(param);
        PTFD_PTFD1 = 1;
        for (i = 0; i < 10000; i++);
        bt_cmdoff();
    #endif
    bt_scibaud(BT_PRESCALER_115200);
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
