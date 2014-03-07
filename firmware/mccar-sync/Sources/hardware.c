/*
 * hardware.c
 *
 *  Created on: Mar 7, 2014
 *      Author: daniw
 */

#include "platform.h"
#include "hardware.h"

/**
 * Initialize ports
 */
void hardware_lowlevel_init(void) 
{
	PTADD = PTADD_INIT;		// Init port direction register of portA
	PTAD  = PTAD_INIT;		// Init port data register of portA
	PTAPE = PTAPE_INIT;		// Init pullup enable register of portA
	PTASE = PTASE_INIT;		// Init slew rate control register of portA
	PTADS = PTADS_INIT;		// Init output drive strength register of portA

	PTBDD = PTBDD_INIT;		// Init port direction register of portB
	PTBD  = PTBD_INIT;		// Init port data register of portB
	PTBPE = PTBPE_INIT;		// Init pullup enable register of portB
	PTBSE = PTBSE_INIT;		// Init slew rate control register of portB
	PTBDS = PTBDS_INIT;		// Init output drive strength register of portB

	PTCDD = PTCDD_INIT;		// Init port direction register of portC
	PTCD  = PTCD_INIT;		// Init port data register of portC
	PTCPE = PTCPE_INIT;		// Init pullup enable register of portC
	PTCSE = PTCSE_INIT;		// Init slew rate control register of portC
	PTCDS = PTCDS_INIT;		// Init output drive strength register of portC

	PTDDD = PTDDD_INIT;		// Init port direction register of portD
	PTDD  = PTDD_INIT;		// Init port data register of portD
	PTDPE = PTDPE_INIT;		// Init pullup enable register of portD
	PTDSE = PTDSE_INIT;		// Init slew rate control register of portD
	PTDDS = PTDDS_INIT;		// Init output drive strength register of portD

	PTEDD = PTEDD_INIT;		// Init port direction register of portE
	PTED  = PTED_INIT;		// Init port data register of portE
	PTEPE = PTEPE_INIT;		// Init pullup enable register of portE
	PTESE = PTESE_INIT;		// Init slew rate control register of portE
	PTEDS = PTEDS_INIT;		// Init output drive strength register of portE

	PTFDD = PTFDD_INIT;		// Init port direction register of portF
	PTFD  = PTFD_INIT;		// Init port data register of portF
	PTFPE = PTFPE_INIT;		// Init pullup enable register of portF
	PTFSE = PTFSE_INIT;		// Init slew rate control register of portF
	PTFDS = PTFDS_INIT;		// Init output drive strength register of portF

	PTGDD = PTGDD_INIT;		// Init port direction register of portG
	PTGD  = PTGD_INIT;		// Init port data register of portG
	PTGPE = PTGPE_INIT;		// Init pullup enable register of portG
	PTGSE = PTGSE_INIT;		// Init slew rate control register of portG
	PTGDS = PTGDS_INIT;		// Init output drive strength register of portG

}
