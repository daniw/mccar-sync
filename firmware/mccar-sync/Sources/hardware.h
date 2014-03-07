/*
 * hardware.h
 *
 *  Created on: Mar 7, 2014
 *      Author: daniw
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "platform.h"

/*
PINS: 
Comment-Abbrevations: 
I: Input, O: Output (PTxDD)
L: Low, H: High (PTxD)
R: Pullup Resistor active (PTxPE)
S: Slew rate control enabled (PTxSE)
D: High drive strength enabled (PTxDS)
*/


//--- PortA ---
#define PTA_0			BIT0	///< |IR|	unused
#define PTA_1			BIT1	///< |IR|	unused
#define PTA_2			BIT2	///< |IR|	unused
#define PTA_3			BIT3	///< |IR|	unused
#define PTA_4			BIT4	///< |IR|	unused
#define PTA_5			BIT5	///< |IR|	unused

#define PTADD_INIT		(0)
#define PTAD_INIT		(0)
#define PTAPE_INIT		(0)
#define PTASE_INIT		(0)
#define PTADS_INIT		(0)


//--- PortB ---
#define PTB_0			BIT0	///< |IR|	unused
#define PTB_1			BIT1	///< |IR|	unused
#define PTB_2			BIT2	///< |IR|	unused
#define PTB_3			BIT3	///< |IR|	unused
#define PTB_4			BIT4	///< |IR|	unused
#define PTB_5			BIT5	///< |IR|	unused
#define PTB_6			BIT6	///< |IR|	unused
#define PTB_7			BIT7	///< |IR|	unused

#define PTBDD_INIT		(0)
#define PTBD_INIT		(0)
#define PTBPE_INIT		(0)
#define PTBSE_INIT		(0)
#define PTBDS_INIT		(0)


//--- PortC ---
#define PTC_0			BIT0	///< |IR|	unused
#define PTC_1			BIT1	///< |IR|	unused
#define PTC_2			BIT2	///< |IR|	unused
#define PTC_3			BIT3	///< |IR|	unused
#define PTC_4			BIT4	///< |IR|	unused
#define PTC_5			BIT5	///< |IR|	unused
#define PTC_6			BIT6	///< |IR|	unused

#define PTCDD_INIT		(0)
#define PTCD_INIT		(0)
#define PTCPE_INIT		(0)
#define PTCSE_INIT		(0)
#define PTCDS_INIT		(0)


//--- PortD ---
#define PTD_0			BIT0	///< |IR|	unused
#define PTD_1			BIT1	///< |IR|	unused
#define PTD_2			BIT2	///< |IR|	unused
#define PTD_3			BIT3	///< |IR|	unused
#define PTD_4			BIT4	///< |IR|	unused
#define PTD_5			BIT5	///< |IR|	unused
#define PTD_6			BIT6	///< |IR|	unused
#define PTD_7			BIT7	///< |IR|	unused

#define PTDDD_INIT		(0)
#define PTDD_INIT		(0)
#define PTDPE_INIT		(0)
#define PTDSE_INIT		(0)
#define PTDDS_INIT		(0)


//--- PortE ---
#define PTE_0			BIT0	///< |IR|	unused
#define PTE_1			BIT1	///< |IR|	unused
#define PTE_2			BIT2	///< |IR|	unused
#define PTE_3			BIT3	///< |IR|	unused
#define PTE_4			BIT4	///< |IR|	unused
#define PTE_5			BIT5	///< |IR|	unused
#define PTE_6			BIT6	///< |IR|	unused
#define PTE_7			BIT7	///< |IR|	unused

#define PTEDD_INIT		(0)
#define PTED_INIT		(0)
#define PTEPE_INIT		(0)
#define PTESE_INIT		(0)
#define PTEDS_INIT		(0)


//--- PortF ---
#define PTF_0			BIT0	///< |IR|	unused
#define PTF_1			BIT1	///< |IR|	unused
#define PTF_2			BIT2	///< |IR|	unused
#define PTF_3			BIT3	///< |IR|	unused
#define PTF_4			BIT4	///< |IR|	unused
#define PTF_5			BIT5	///< |IR|	unused
#define PTF_6			BIT6	///< |IR|	unused
#define PTF_7			BIT7	///< |IR|	unused

#define PTFDD_INIT		(0)
#define PTFD_INIT		(0)
#define PTFPE_INIT		(0)
#define PTFSE_INIT		(0)
#define PTFDS_INIT		(0)


//--- PortG ---
#define PTG_0			BIT0	///< |IR|	unused
#define PTG_1			BIT1	///< |IR|	unused
#define PTG_2			BIT2	///< |IR|	unused
#define PTG_3			BIT3	///< |IR|	unused
#define PTG_4			BIT4	///< |IR|	unused
#define PTG_5			BIT5	///< |IR|	unused

#define PTGDD_INIT		(0)
#define PTGD_INIT		(0)
#define PTGPE_INIT		(0)
#define PTGSE_INIT		(0)
#define PTGDS_INIT		(0)


// function prototypes
void hardware_lowlevel_init(void);


#endif /* HARDWARE_H_ */
