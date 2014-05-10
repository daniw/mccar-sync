/*
 * hardware.h
 *
 *  Created on: Mar 7, 2014
 *      Author: daniw
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "platform.h"

#define CLOCK           24000000    // Bus clock frequency in Hz
#define MOT_RESOLUTION  10          // Motor control resolution in number of bits
#define ADC_RESOLUTION  12          // ADC Resolution in number of bits
#define BUZZER_FREQ     1000        // Buzzer frequency in Hz
#define BUZZER_SAMPLE   48000       // Buzzer sampling rate for streaming audio data in Hz

//--- User defined baud rate calculation ---
#define BT_BAUD         9600        // Baud rate for bluetooth module
#define BT_PRESCALER    CLOCK/BT_BAUD / 16  // Prescaler for bluetooth module
#define BT_PRESC_LOW    BT_PRESCALER
#define BT_PRESC_HIGH   BT_PRESCALER / 0x100
// Check if baud rate for bluetooth module can be set correct
#define BT_BAUD_REAL    CLOCK / 16 / (BT_PRESC_HIGH * 0x100 + BT_PRESC_LOW)
#define BT_BAUD_MAXERR  20          // Maximum error tolerated in permilles
#define BT_BAUD_MAXDIFF BT_BAUD * BT_BAUD_MAXERR / 1000
#define BT_BAUD_MAX     (BT_BAUD + BT_BAUD_MAXDIFF)
#define BT_BAUD_MIN     (BT_BAUD - BT_BAUD_MAXDIFF)
#if BT_PRESC_HIGH > 0x1f
    #error "Prescaler value for bluetooth module too high!"
#else
    // The following test does not work caused by an integer overflow
    #if ((BT_BAUD_REAL > BT_BAUD_MAX) || (BT_BAUD_REAL < BT_BAUD_MIN))
        #warning "Baud rate error for bluetooth module may be too high"
    #endif
#endif

//--- Predefined baud rates (These prescaler Values are not tested as above, so use them with caution!) ---
#define BT_PRESCALER_4800   CLOCK/4800 / 16             // Prescaler for bluetooth module baud rate = 4800
#define BT_PRESC_4800_LOW   BT_PRESCALER_4800
#define BT_PRESC_4800_HIGH  BT_PRESCALER_4800 / 0x100

#define BT_PRESCALER_9600   CLOCK/9600 / 16             // Prescaler for bluetooth module baud rate = 9600
#define BT_PRESC_9600_LOW   BT_PRESCALER_9600
#define BT_PRESC_9600_HIGH  BT_PRESCALER_9600 / 0x100

#define BT_PRESCALER_19200   CLOCK/19200 / 16           // Prescaler for bluetooth module baud rate = 19200
#define BT_PRESC_19200_LOW   BT_PRESCALER_19200
#define BT_PRESC_19200_HIGH  BT_PRESCALER_19200 / 0x100

#define BT_PRESCALER_38400   CLOCK/38400 / 16           // Prescaler for bluetooth module baud rate = 38400
#define BT_PRESC_38400_LOW   BT_PRESCALER_38400
#define BT_PRESC_38400_HIGH  BT_PRESCALER_38400 / 0x100

#define BT_PRESCALER_57600   CLOCK/57600 / 16           // Prescaler for bluetooth module baud rate = 57600
#define BT_PRESC_57600_LOW   BT_PRESCALER_57600
#define BT_PRESC_57600_HIGH  BT_PRESCALER_57600 / 0x100

#define BT_PRESCALER_115200   CLOCK/115200 / 16             // Prescaler for bluetooth module baud rate = 115200
#define BT_PRESC_115200_LOW   BT_PRESCALER_115200
#define BT_PRESC_115200_HIGH  BT_PRESCALER_115200 / 0x100

#define BT_PRESCALER_234000   CLOCK/234000 / 16             // Prescaler for bluetooth module baud rate = 234000
#define BT_PRESC_234000_LOW   BT_PRESCALER_234000
#define BT_PRESC_234000_HIGH  BT_PRESCALER_234000 / 0x100

#define BT_PRESCALER_460800   CLOCK/460800 / 16             // Prescaler for bluetooth module baud rate = 460800
#define BT_PRESC_460800_LOW   BT_PRESCALER_460800
#define BT_PRESC_460800_HIGH  BT_PRESCALER_460800 / 0x100

#define BT_PRESCALER_921600   CLOCK/921600 / 16             // Prescaler for bluetooth module baud rate = 921600
#define BT_PRESC_921600_LOW   BT_PRESCALER_921600
#define BT_PRESC_921600_HIGH  BT_PRESCALER_921600 / 0x100

#define BT_PRESCALER_1382400   CLOCK/1382400 / 16             // Prescaler for bluetooth module baud rate = 1382400
#define BT_PRESC_1382400_LOW   BT_PRESCALER_1382400
#define BT_PRESC_1382400_HIGH  BT_PRESCALER_1382400 / 0x100

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
#define LS_LED_R        BIT0    ///< |OH|   Line sensor infrared LED left
#define LS_LED_MR       BIT1    ///< |OH|   Line sensor infrared LED middle left
#define LS_LED_M        BIT2    ///< |OH|   Line sensor infrared LED middle
#define LS_LED_ML       BIT3    ///< |OH|   Line sensor infrared LED middle right
#define LS_LED_L        BIT4    ///< |OH|   Line sensor infrared LED right
#define IR_R            BIT5    ///< |OL|   Rear infrared LED

#define LS_LED_MASK     (LS_LED_R | LS_LED_MR | LS_LED_M | LS_LED_ML | LS_LED_L)

#define PTADD_INIT      (LS_LED_R | LS_LED_MR | LS_LED_M | LS_LED_ML | LS_LED_L | IR_R)
#define PTAD_INIT       (LS_LED_R | LS_LED_MR | LS_LED_M | LS_LED_ML | LS_LED_L)
#define PTAPE_INIT      (0)
#define PTASE_INIT      (0)
#define PTADS_INIT      (0)

//--- PortB ---
#define SPI_MISO        BIT0    ///< |IR|   SPI MISO
#define SPI_MOSI        BIT1    ///< |IR|   SPI_MOSI
#define SPI_SCK         BIT2    ///< |IR|   SPI_SCK
#define BT_EN           BIT3    ///< |OL|   Bluetooth Enable
#define LS_REC_R        BIT4    ///< |I|    Line sensor IR receiver right
#define LS_REC_MR       BIT5    ///< |I|    Line sensor IR receiver right middle
#define LS_REC_ML       BIT6    ///< |I|    Line sensor IR receiver left middle
#define LS_REC_L        BIT7    ///< |I|    Line sensor IR receiver left

#define PTBDD_INIT      (BT_EN)
#define PTBD_INIT       (BT_EN)
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
#define TPM1MOD_INIT    (CLOCK/BUZZER_FREQ)

//--- Initialisation for driving the buzzer with PWM ---
// bus rate clock, no prescaler
//#define TPM1SC_INIT     (TPM1SC_CLKSA_MASK)
// Modulo for a sampling rate 48 kHz
//#define TPM1MOD_INIT    (CLOCK/BUZZER_SAMPLE)
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
#define TPM2MOD_INIT    ((1<<MOT_RESOLUTION) + 1)
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


//### IIC Bus ###
//--- IIC master -> address not initialised yet  ---
#define IICA_INIT       (0)
//--- Divider 240 for a SCL frequency of 100 kHz ---
//#define IICF_INIT       (0x1f)
//--- Divider 60 for a SCL frequency of 400 kHz ---
#define IICF_INIT       (0x45)
//--- Enable IIC module, interrupt enabled, transmit mode,  ---
//#define IICC1_INIT      (IICC1_IICEN_MASK | IICC1_IICIE_MASK | IICC1_TX)
#define IICC1_INIT      (IICC1_IICEN_MASK | IICC1_TX)
//--- No initialisation required ---
#define IICS_INIT       (0)
//--- No data ---
#define IICD_INIT       (0)
//--- No general call, 7 bit address ---
#define IICC2_INIT      (0)


//### IIC Slave addresses ###
//--- Quadrature encoder ---
//#define IIC_ADR_ENCODER (0x54)      // Wrong in description
#define IIC_ADR_ENCODER (0x2A)
//--- Color sensor ---
#define IIC_ADR_COLOR   (0x39)
//--- Acceleration sensor ---
#define IIC_ADR_ACCEL   (0x1c)


//### SCI interface to bluetooth module ###
//--- SCI Baud rate ---
#define SCI1BDH_INIT    (BT_PRESC_HIGH)
#define SCI1BDL_INIT    (BT_PRESC_LOW)
//--- 8 Bit, no parity ---
#define SCI1C1_INIT     (0)
//--- Enable Receiver and Transmitter, RX not inverted, no interrupts enabled yet ---
#define SCI1C2_INIT     (SCI1C2_RIE_MASK | SCI1C2_TE_MASK | SCI1C2_RE_MASK)
//--- no writable bits in SCI1S1 ---
//#define SCI1S1_INIT
//--- No specific settings here ---
#define SCI1S2_INIT     (0)
//--- TX not inverted, no interrupts enabled yet ---
#define SCI1C3_INIT     (0)


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

//### Battery charger ###
//--- Battery charger state ---
typedef enum Chg_state_
{
    CHARGE,
    FULL
} Chg_state_t;

// function prototypes
void hardware_lowlevel_init(void);
void motorcontrol(Direction_t dir, uint16 speedleft, uint16 speedright);
Joy_ways_t getjoystick(void);
void getline(uint16* line);
uint16 getsupplyvoltage(void);
uint16 getsupplycurrent(void);
Chg_state_t getsupplystate(void);
uint8 getsupplymode(void);
void bt_on(void);
void bt_off(void);
void bt_cmdon(void);
void bt_cmdoff(void);
void bt_scibaud(uint16 baud);
void bt_sendbyte(uint8 data);
void bt_senddata(uint8* data, uint8 size);
uint8 bt_enqueue(uint8* data, uint8 size);
uint8 bt_dequeue(uint8* data, uint8 size);

#endif /* HARDWARE_H_ */
