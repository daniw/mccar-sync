/*
 * hardware.c
 *
 *  Created on: Mar 7, 2014
 *      Author: daniw
 */

#include "platform.h"
#include "hardware.h"

/**
 * Initialize clock module, ports and timer
 * @author daniw
 */
void hardware_lowlevel_init(void) 
{
    //### Clock system ###
    /*
     * After startup the clock system is in FEI mode. To change to PEE mode the 
     * clock system has to be changed in the following order: 
     * FEI -> FBE -> BLPE -> PBE -> PEE 
     */
    //--- FEI -> FBE ---
    // Start external crystal oszillator
    MCGC2 = MCGC2_RANGE_MASK | MCGC2_HGO_MASK | MCGC2_EREFS_MASK | MCGC2_ERCLKEN_MASK;
    // Wait for crystal oscillator to be ready
    while(!MCGSC_OSCINIT);
    // Block interrupts
    DisableInterrupts;
    // Select external clock source for MCGOUT
    // divide by 128 for fll
    MCGC1 = MCGC1_CLKS1_MASK | MCGC1_RDIV_MASK;
    // Wait until clock source for reference clock has changed
    while(MCGSC_IREFST);
    // Wait until MCGOUT has changed to external reference clock
    while(MCGSC_CLKST != 2);
    //--- FBE -> BLPE ---
    // Enter BLPE mode (start PLL, stop FLL)
    MCGC2_LP = 1;
    // Interrupts can now be re-enabled
    /* EnableInterrupts */
    // Divide external clock by 4
    MCGC1_RDIV = 2; 
    // Prepare PLL  and set multiplier to 24 to achieve 48 MHz
    MCGC3_PLLS = 1;
    MCGC3_VDIV = 6;
    // Wait until PLLS has PLL as clock source
    while(!MCGSC_PLLST);
    //--- BLPE -> PBE ---
    // Switch to PBE mode
    MCGC2_LP = 0;
    // Wait until PLL has locked
    while(!MCGSC_LOCK);
    //--- PBE -> PEE ---
    // Select PLL output as system clock source
    MCGC1_CLKS = 0;
    // Wait until MCGSC is selected
    while(MCGSC_CLKST != 3);
    // MCGOUT is now configured for a frequency of 48 MHz
    // The bus frequency is 24 MHz

    //### I/O Ports ###
    //--- PortA ---
    PTADD = PTADD_INIT;     // Init port direction register of portA
    PTAD  = PTAD_INIT;      // Init port data register of portA
    PTAPE = PTAPE_INIT;     // Init pullup enable register of portA
    PTASE = PTASE_INIT;     // Init slew rate control register of portA
    PTADS = PTADS_INIT;     // Init output drive strength register of portA

    //--- PortB ---
    PTBDD = PTBDD_INIT;     // Init port direction register of portB
    PTBD  = PTBD_INIT;      // Init port data register of portB
    PTBPE = PTBPE_INIT;     // Init pullup enable register of portB
    PTBSE = PTBSE_INIT;     // Init slew rate control register of portB
    PTBDS = PTBDS_INIT;     // Init output drive strength register of portB

    //--- PortC ---
    PTCDD = PTCDD_INIT;     // Init port direction register of portC
    PTCD  = PTCD_INIT;      // Init port data register of portC
    PTCPE = PTCPE_INIT;     // Init pullup enable register of portC
    PTCSE = PTCSE_INIT;     // Init slew rate control register of portC
    PTCDS = PTCDS_INIT;     // Init output drive strength register of portC

    //--- PortD ---
    PTDDD = PTDDD_INIT;     // Init port direction register of portD
    PTDD  = PTDD_INIT;      // Init port data register of portD
    PTDPE = PTDPE_INIT;     // Init pullup enable register of portD
    PTDSE = PTDSE_INIT;     // Init slew rate control register of portD
    PTDDS = PTDDS_INIT;     // Init output drive strength register of portD

    //--- PortE ---
    PTEDD = PTEDD_INIT;     // Init port direction register of portE
    PTED  = PTED_INIT;      // Init port data register of portE
    PTEPE = PTEPE_INIT;     // Init pullup enable register of portE
    PTESE = PTESE_INIT;     // Init slew rate control register of portE
    PTEDS = PTEDS_INIT;     // Init output drive strength register of portE

    //--- PortF ---
    PTFDD = PTFDD_INIT;     // Init port direction register of portF
    PTFD  = PTFD_INIT;      // Init port data register of portF
    PTFPE = PTFPE_INIT;     // Init pullup enable register of portF
    PTFSE = PTFSE_INIT;     // Init slew rate control register of portF
    PTFDS = PTFDS_INIT;     // Init output drive strength register of portF

    //--- PortG ---
    PTGDD = PTGDD_INIT;     // Init port direction register of portG
    PTGD  = PTGD_INIT;      // Init port data register of portG
    PTGPE = PTGPE_INIT;     // Init pullup enable register of portG
    PTGSE = PTGSE_INIT;     // Init slew rate control register of portG
    PTGDS = PTGDS_INIT;     // Init output drive strength register of portG

    //### Timer 1 ###
    TPM1SC   = TPM1SC_INIT;
    TPM1MOD  = TPM1MOD_INIT;

    TPM1C0SC = TPM1C0SC_INIT;
    TPM1C1SC = TPM1C1SC_INIT;
    TPM1C2SC = TPM1C2SC_INIT;
    TPM1C3SC = TPM1C3SC_INIT;
    TPM1C4SC = TPM1C4SC_INIT;
    TPM1C5SC = TPM1C5SC_INIT;
    TPM1C0V  = TPM1C0V_INIT;
    TPM1C1V  = TPM1C1V_INIT;
    TPM1C2V  = TPM1C2V_INIT;
    TPM1C3V  = TPM1C3V_INIT;
    TPM1C4V  = TPM1C4V_INIT;
    TPM1C5V  = TPM1C5V_INIT;

    //### Timer 2 ###
    TPM2SC   = TPM2SC_INIT;
    TPM2MOD  = TPM2MOD_INIT;

    TPM2C0SC = TPM2C0SC_INIT;
    TPM2C1SC = TPM2C1SC_INIT;
    TPM2C0V  = TPM2C0V_INIT;
    TPM2C1V  = TPM2C1V_INIT;

    //### Analog digital converter ###
    ADCSC1 = ADCSC1_INIT;
    ADCSC2 = ADCSC2_INIT;
    ADCCV  = ADCCV_INIT;
    ADCCFG = ADCCFG_INIT;
    APCTL1 = APCTL1_INIT;
    APCTL2 = APCTL2_INIT;
}


//### Motor control ###
/**
 * This function controls both motors of the mccar.
 * @author daniw
 * @param dir direction, to which the mccar should drive
 * @param speedleft speed of the left motor
 * @param speedright speed of the right motor
 */
void motorcontrol(Direction_t dir, uint16 speedleft, uint16 speedright)
{
    switch (dir)
    {
        case STOP:
            PTDDD |=   MOTL_A | MOTL_B | MOTR_A | MOTR_B;
            break;
        case FORWARD:
            PTDDD |=   MOTL_A | MOTR_B;
            PTDDD &= ~(MOTL_B | MOTR_A);
            break;
        case BACKWARD:
            PTDDD |=   MOTL_B | MOTR_A;
            PTDDD &= ~(MOTL_A | MOTR_B);
            break;
        case TURNLEFT:
            PTDDD |=   MOTL_A | MOTR_A;
            PTDDD &= ~(MOTL_B | MOTR_B);
            break;
        case TURNRIGHT:
            PTDDD |=   MOTL_B | MOTR_B;
            PTDDD &= ~(MOTL_A | MOTR_A);
            break;
        case CURVELEFT:
            PTDDD |=   MOTL_A | MOTR_A | MOTR_B;
            PTDDD &= ~(MOTL_B);
            break;
        case CURVERIGHT:
            PTDDD |=   MOTL_A | MOTL_B | MOTR_B;
            PTDDD &= ~(MOTR_A);
            break;
        case BACKLEFT:
            PTDDD |=   MOTL_B | MOTR_A | MOTR_B;
            PTDDD &= ~(MOTL_A);
            break;
        case BACKRIGHT:
            PTDDD |=   MOTL_A | MOTL_B | MOTR_A;
            PTDDD &= ~(MOTR_B);
            break;
        default:
            PTDDD |=   MOTL_A | MOTL_B | MOTR_A | MOTR_B;
            break;
    }
    PTDD &= ~(MOTL_A | MOTL_B | MOTR_A | MOTR_B);
    TPM2C0V = speedright;
    TPM2C1V = speedleft;
}


//### Joystick ###
/**
 * Function to read the current status from the joystick
 * @return current position as joystick specific enum Joy_ways_t
 */
Joy_ways_t getjoystick(void)
{
    switch(PTGD & (SW_JOY_0 | SW_JOY_1 | SW_JOY_2))
    {
        case 4:
            return UP;
            break;
        case 6:
            return DOWN;
            break;
        case 3:
            return RIGHT;
            break;
        case 5:
            return LEFT;
            break;
        case 2:
            return PUSH;
            break;
        default:
            return NONE;
            break;
    }
}


//### line sensor ###
/**
 * Function to read out all fields from the line sensor
 * @param line Pointer to a field to store the value for each field
 *             This array must have a minimal length of 8!
 *             line[0] is on the left side, line[7] is on the right side
 */
void getline(uint16* line)
{
    uint8 i;
    uint16 linedark;                    // temporary register for dark value
    for (i = 0; i <= 7; i++)            // loop through all fields
    {
        PTAD |= LS_LED_MASK;            // switch all line sensor leds off
        ADCSC1_ADCH = ((i / 2) + 4);    // Start dummy conversion to wait for filters to settle
        while(!ADCSC1_COCO){}           // wait until conversion is complete
        ADCSC1_ADCH = ((i / 2) + 4);    // Start conversion for dark value
        while(!ADCSC1_COCO){}           // wait until conversion is complete
        linedark = ADCR;                // save dark value as reference for environmental light

        PTAD &= ~(1 << (4 - ((i + 1) / 2))); // switch corresponding led on
        ADCSC1_ADCH = ((i / 2) + 4);    // Start dummy conversion to wait for filters to settle
        while(!ADCSC1_COCO){}           // wait until conversion is complete
        ADCSC1_ADCH = ((i / 2) + 4);    // Start conversion for sensing line
        while(!ADCSC1_COCO){}           // wait until conversion is complete

        //line[i] = ADCR - linedark;      // calculate difference to eliminate environmental light
        line[i] = ADCR;                 // without dark correction
    }
    
}


//### Power supply ###
//--- Supply voltage ---
/**
 * Function to measure the supply voltage respectively battery status
 * @return ADC value for supply voltage
 */
uint16 getsupplyvoltage(void)
{
    ADCSC2_ADCH = 9;                // Start conversion
    while(!ADCSC1_COCO){}           // wait until conversion is complete
    return ADCR;
}

