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
Comment-Abbreviations: 
I: Input, O: Output (PTxDD)
L: Low, H: High (PTxD)
R: Pullup Resistor active (PTxPE)
S: Slew rate control enabled (PTxSE)
D: High drive strength enabled (PTxDS)
*/

//--- Bit definitions ---
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80


//### I/O Ports ##
//--- PortA ---
#define LS_R            BIT0    ///< |OH|   Line sensor infrared LED left
#define LS_MR           BIT1    ///< |OH|   Line sensor infrared LED middle left
#define LS_M            BIT2    ///< |OH|   Line sensor infrared LED middle
#define LS_ML           BIT3    ///< |OH|   Line sensor infrared LED middle right
#define LS_L            BIT4    ///< |OH|   Line sensor infrared LED right
#define IR_R            BIT5    ///< |OL|   Rear infrared LED

#define PTADD_INIT      (LS_R | LS_MR | LS_M | LS_ML | LS_L | IR_R)
#define PTAD_INIT       (LS_R | LS_MR | LS_M | LS_ML | LS_L)
#define PTAPE_INIT      (0)
#define PTASE_INIT      (0)
#define PTADS_INIT      (0)

//--- PortB ---
#define SPI_MISO        BIT0    ///< |IR|   SPI MISO
#define SPI_MOSI        BIT1    ///< |IR|   SPI_MOSI
#define SPI_SCK         BIT2    ///< |IR|   SPI_SCK
#define BT_EN           BIT3    ///< |OL|   Bluetooth Enable
#define LS_IR_R         BIT4    ///< |I|    Line sensor IR receiver right
#define LS_IR_MR        BIT5    ///< |I|    Line sensor IR receiver right middle
#define LS_IR_ML        BIT6    ///< |I|    Line sensor IR receiver left middle
#define LS_IR_L         BIT7    ///< |I|    Line sensor IR receiver left

#define PTBDD_INIT      (BT_EN)
#define PTBD_INIT       (0)
#define PTBPE_INIT      (SPI_MISO | SPI_MOSI| SPI_SCK)
#define PTBSE_INIT      (0)
#define PTBDS_INIT      (0)

//--- PortC ---
#define I2C_SCL         BIT0    ///< |IR|   I2C SCL
#define I2C_SDA         BIT1    ///< |IR|   I2C SDA
#define COL_LED         BIT2    ///< |OL|   Color sensor LED
#define VIRT_RXD        BIT3    ///< |IR|   Serial connection RXD
#define LED_FL_G        BIT4    ///< |OH|   Headlight left green
#define VIRT_TXD        BIT5    ///< |I|    Serial connection TXD
#define LED_FR_G        BIT6    ///< |OH|   Headlight right green

#define PTCDD_INIT      (COL_LED | LED_FL_G | LED_FR_G)
#define PTCD_INIT       (LED_FL_G | LED_FR_G)
#define PTCPE_INIT      (I2C_SCL | I2C_SDA | VIRT_RXD)
#define PTCSE_INIT      (0)
#define PTCDS_INIT      (0)

//--- PortD ---
#define I_MON           BIT0    ///< |I|    Current monitor
#define U_MON           BIT1    ///< |I|    Voltage monitor
#define LED_B           BIT2    ///< |OL|   Backlight
#define CHG_STAT        BIT3    ///< |I|    Charge status
#define MOTL_A          BIT4    ///< |OL|   Motor left channel A 
#define MOTL_B          BIT5    ///< |OL|   Motor left channel B
#define MOTR_A          BIT6    ///< |OL|   Motor right channel A
#define MOTR_B          BIT7    ///< |OL|   Motor right channel B

#define PTDDD_INIT      (LED_B | MOTL_A | MOTL_B | MOTR_A | MOTR_B)
#define PTDD_INIT       (0)
#define PTDPE_INIT      (0)
#define PTDSE_INIT      (0)
#define PTDDS_INIT      (0)

//--- PortE ---
#define BT_RXD          BIT0    ///< |IR|   Bluetooth RXD
#define BT_TXD          BIT1    ///< |I|    Bluetooth TXD
#define IR_RX_F         BIT2    ///< |IR|   Front infrared receiver
#define IR_RX_R         BIT3    ///< |I|    Rear infrared receiver
#define IR_FL           BIT4    ///< |OL|   Front left infrared LED
#define IR_FM           BIT5    ///< |OL|   Front middle infrared LED
#define IR_FR           BIT6    ///< |OL|   Front right infrared LED
#define LED_FR_B        BIT7    ///< |OH|   Headlight right blue

#define PTEDD_INIT      (IR_FL | IR_FM | IR_FR | LED_FR_B)
#define PTED_INIT       (LED_FR_B)
#define PTEPE_INIT      (BT_RXD | IR_RX_F)
#define PTESE_INIT      (0)
#define PTEDS_INIT      (0)

//--- PortF ---
#define LED_FL_B        BIT0    ///< |OH|   Headlight left blue
#define LED_FL_R        BIT1    ///< |OH|   Headlight left red
#define LED_FR_R        BIT2    ///< |OH|   Headlight right red
#define BUZ             BIT3    ///< |OL|   Buzzer
#define MOTL_PWM        BIT4    ///< |OL|   Motor left PWM
#define MOTR_PWM        BIT5    ///< |OL|   Motor right PWM
#define SPI_SS          BIT6    ///< |OH|   SPI SS
#define BT_CMD          BIT7    ///< |OL|   Bluetooth command

#define PTFDD_INIT      (LED_FL_B | LED_FL_R | LED_FR_R | BUZ | MOTL_PWM | MOTR_PWM | SPI_SS | BT_CMD)
#define PTFD_INIT       (LED_FL_B | LED_FL_R | LED_FR_R | SPI_SS)
#define PTFPE_INIT      (0)
#define PTFSE_INIT      (0)
#define PTFDS_INIT      (0)

//--- PortG ---
#define SW_JOY_0        BIT0    ///< |IR|   Joystick
#define SW_JOY_1        BIT1    ///< |IR|   Joystick
#define SW_JOY_2        BIT2    ///< |IR|   Joystick
#define SW_MODE         BIT3    ///< |I|    Mode switch
#define PTG_4           BIT4    ///< |IR|   unused
#define PTG_5           BIT5    ///< |IR|   unused

#define PTGDD_INIT      (0)
#define PTGD_INIT       (0)
#define PTGPE_INIT      (SW_JOY_0 | SW_JOY_1 | SW_JOY_2)
#define PTGSE_INIT      (0)
#define PTGDS_INIT      (0)


//### Timer 1 ###
//--- Initialisation for generating the buzzer frequency directly from timer ---
// bus rate clock, prescaler 4
#define TPM1SC_INIT     (TPM1SC_CLKSA_MASK | TPM1SC_PS1_MASK)
// Initial value for a frequency of 1 kHz on Buzzer
#define TPM1MOD_INIT    (3000)

//--- Initialisation for driving the buzzer with PWM ---
// bus rate clock, no prescaler
//#define TPM1SC_INIT     (TPM1SC_CLKSA_MASK)
// Modulo for a sampling rate of 96 kHz
//#define TPM1MOD_INIT    (250)
// Modulo for a sampling rate of 48 kHz
//#define TPM1MOD_INIT    (500)
// Modulo for a sampling rate of 44.1 kHz
//#define TPM1MOD_INIT    (544)
// Modulo for a sampling rate of 32 kHz
//#define TPM1MOD_INIT    (750)
// Not in use
#define TPM1C0SC_INIT   (0)
// Not in use
#define TPM1C1SC_INIT   (0)
// Not in use
#define TPM1C2SC_INIT   (0)
// Not in use
#define TPM1C3SC_INIT   (0)
// Not in use
#define TPM1C4SC_INIT   (0)
// Buzzer not yet configured
#define TPM1C5SC_INIT   (0)
// Not in use
#define TPM1C0V_INIT    (0)
// Not in use
#define TPM1C1V_INIT    (0)
// Not in use
#define TPM1C2V_INIT    (0)
// Not in use
#define TPM1C3V_INIT    (0)
// Not in use
#define TPM1C4V_INIT    (0)
// Buzzer not yet configured
#define TPM1C5V_INIT    (0)


//### Timer 2 ###
// bus rate clock, no prescaler
#define TPM2SC_INIT     (TPM2SC_CLKSA_MASK)
// Motor control with 10 bit resolution and a frequency of 23.4 kHz
#define TPM2MOD_INIT    (1023)
// Motor control with 8 bit resolution and a frequency of 93.75 kHz
//#define TPM2MOD_INIT    (255)
// Edge aligned PWM for both motors
#define TPM2C0SC_INIT   (TPM2C0SC_MS0B_MASK | TPM2C0SC_ELS0B_MASK)
#define TPM2C1SC_INIT   (TPM2C0SC_MS0B_MASK | TPM2C0SC_ELS0B_MASK)
// Stop motors at startup
#define TPM2C0V_INIT    (0)
#define TPM2C1V_INIT    (0)


//### Analog digital converter ###
//--- Signal conversion, module disabled ---
#define ADCSC1_INIT     (ADCSC1_ADCH_MASK)
//--- Software trigger ---
#define ADCSC2_INIT     (0)
//--- ADCCV not in use ---
#define ADCCV_INIT      (0)
//--- Long sample time, Clock divided by 4 for ADCK, 12 bit conversion, bus clock as clock source ---
#define ADCCFG_INIT     (ADCCFG_ADLSMP_MASK | ADCCFG_ADIV1_MASK | ADCCFG_MODE0_MASK)
//--- I/O pins as analog inputs
#define APCTL1_INIT     (APCTL1_ADPC4_MASK | APCTL1_ADPC5_MASK | APCTL1_ADPC6_MASK | APCTL1_ADPC7_MASK)
#define APCTL2_INIT     (APCTL2_ADPC8_MASK | APCTL2_ADPC9_MASK)
#define APCTL3_INIT     (0)


//### Motor control ###
//--- Directions for mccar to drive ---
typedef enum Direction_
{
    STOP,
    FORWARD,
    BACKWARD,
    TURNLEFT,
    TURNRIGHT,
    CURVELEFT,
    CURVERIGHT,
    BACKLEFT,
    BACKRIGHT
} Direction_t;


//### Joystick ###
//--- Mask for joystick pins ---
#define JOY_MASK = SW_JOY_0| SW_JOY_1 | SW_JOY_2;

//--- Ways, the Joystick can be moved to ---
typedef enum Joy_ways_
{
    NONE,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    PUSH,
} Joy_ways_t;

// function prototypes
void hardware_lowlevel_init(void);
void motorcontrol(Direction_t dir, uint16 speedleft, uint16 speedright);
Joy_ways_t getjoystick(void);

#endif /* HARDWARE_H_ */
