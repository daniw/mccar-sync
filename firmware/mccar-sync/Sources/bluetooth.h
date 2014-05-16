/*
 * bluetooth.h
 *
 *  Created on: May 1, 2014
 *      Author: daniw
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "hardware.h"
#include "queue.h"

typedef enum bt_success_
{
    SUCCESS=0,
    FAILED
} bt_success_t;

typedef struct bt_addr_
{
    uint16 nn;      // non-significant adress portion
    uint8 uu;       // 8 bit upper address portion
    uint32 ll;      // 24 bit lower address portion
} bt_addr_t;

typedef enum bt_role_
{
    SLAVE=0,
    MASTER,
    SLAVELOOP
} bt_role_t;

typedef enum bt_class_
{
    DEFAULT=0
} bt_class_t;

typedef enum bt_inqmode_
{
    STANDARD=0,
    RSSI=1
} bt_inqmode_t;

typedef struct bt_accessmode_
{
    bt_inqmode_t mode;    // Inquire access mode
    uint16 maxnumber;   // Maximum number of devices response
    uint8 timeout;      // Inquire timeout
} bt_accessmode_t;

typedef enum bt_baud_
{
    BT_BAUD_4800,       // 4800 Baud
    BT_BAUD_9600,       // 9600 Baud
    BT_BAUD_19200,      // 19200 Baud
    BT_BAUD_38400,      // 38400 Baud
    BT_BAUD_57600,      // 57600 Baud
    BT_BAUD_115200,     // 115200 Baud
    BT_BAUD_234000,     // 234000 Baud
    BT_BAUD_460800,     // 460800 Baud
    BT_BAUD_921600,     // 921600 Baud
    BT_BAUD_1382400,    // 1382400 Baud
} bt_baud_t;

typedef enum bt_stopbit_
{
    ONE=0,              // 1 Stopbit
    TWO=1               // 2 Stopbits
} bt_stopbit_t;

typedef enum bt_parity_
{
    NOPARITY=0,       // No praity bit
    ODDPARITY=1,        // Odd parity bit
    EVENPARITY=2        // Even parity bit
} bt_parity_t;

typedef struct bt_uartparam_
{
    bt_baud_t baud;     // Baud rate
    bt_stopbit_t stop;  // stop bit
    bt_parity_t parity;  // parity bit
} bt_uartparam_t;

typedef enum bt_conmode_
{
    CON_SPEC,           // Connect to a specified Bluetooth device only
    CON_ANY,            // Can connect with any other Bluetooth device
    TEST                // Test mode
} bt_conmode_t;

typedef enum bt_pol_
{
    LOWLOW,             // Both LED low active
    HIGHLOW,            // LED1 high active, LED2 low active
    LOWHIGH,            // LED1 low active, LED2 high active
    HIGHHIGH            // Both LED high active
} bt_pol_t;

typedef struct bt_scanparam_
{
    uint16 interval;    // Scan time interval
    uint16 duration;    // Scan time duration
    uint16 pageint;     // Page scan time interval
    uint16 pagedur;     // Page scan time duration
} bt_scanparam_t;

typedef struct bt_snifftime_
{
    uint16 maxtime;     // maximum time
    uint16 mintime;     // minimum time
    uint16 retry;       // retry time
    uint16 timeout;     // timeout
} bt_snifftime_t;

typedef enum bt_secmode_
{
    SECOFF=0,           // sec_mode_off
    NONSECURE,          // sec_mode1_non-secure
    SERVICE,            // sec_mode2_service
    LINK,               // sec_mode3_link
    UNKNOWN             // sec_mode_unknown
} bt_secmode_t;

typedef enum bt_encmode_
{
    ENCOFF=0,           // hci_enc_mode_off
    PTPT,               // hci_enc_mode_pt_tp_pt
    PTPTBROADCST,       // hci_enc_mode_pt_to_pt_and_bcast
} bt_encmode_t;

typedef struct bt_secencmode_
{
    bt_secmode_t secmode;   // security mode
    bt_encmode_t encmode;   // encryption mode
} bt_secencmode_t;

typedef enum bt_status_
{
    INITIALIZED,        // initialized
    READY,              // ready
    PAIRABLE,           // pairable
    PAIRED,             // paired
    INQUIRING,          // inquiring
    CONNECTING,         // connecting
    CONNECTED,          // connected
    DISCONNECTED,       // disconnected
    UNKNOWNSTATUS       // unknown
} bt_status_t;

typedef enum bt_results_
{
    BTSUCCESS,
    LINK_LOSS,
    NO_SLC,
    TIMEOUT,
    ERROR
} bt_results_t;

// 0 init commanc mode
void bt_joincmdmode(void);
void bt_partcmdmode(void);

// 1 test UART connection
bt_success_t bt_test(void);

// 2 reset device
bt_success_t bt_reset(void);

// 3 query firmware version
bt_success_t bt_version(void);

// 4 restore settings to factory defaults
bt_success_t bt_factoryreset(void);

// 5 query EGBT-045MS bluetooth address
bt_addr_t bt_address(void);

// 6 query/set device name
bt_success_t bt_getname(char* name);
bt_success_t bt_setname(char* name);

// 7 query remote bluetooth device's name
char bt_getremotename(bt_addr_t addr);

// 8 query/set device role
bt_role_t bt_getrole(void);
bt_success_t bt_setrole(bt_role_t role);

// 9 query/set class f device CoD
bt_class_t bt_getclass(void);
bt_success_t bt_setclass(bt_class_t class);

// 10 Query/Set Inquire Access Code
uint32 bt_getaccesscode(void);
bt_success_t bt_setaccesscode(uint32 code);

// 11 Query/Set Inquire Access Mode
bt_accessmode_t bt_getaccessmode(void);
bt_success_t bt_setaccessmode(bt_accessmode_t mode);

// 12 Query/Set Pairing Passkey
bt_success_t bt_getkey(char* key);
bt_success_t bt_setkey(char* key);

// 13 Query/Set UART parameter
bt_uartparam_t bt_getparam(void);
bt_success_t bt_setparam(bt_uartparam_t param);

// 14 Query/Set Connection Mode
bt_conmode_t bt_getconmode(void);
bt_success_t bt_setconmode(bt_conmode_t mode);

// 15 Query/Set Binding Bluetooth Address
bt_addr_t bt_getbindaddr(void);
bt_success_t bt_setbindaddr(bt_addr_t addr);

// 16 Query/Set LED Output Polarity
bt_pol_t bt_getpol(void);
bt_success_t bt_setpol(bt_pol_t polarity);

// 17 Set/Reset a User I/O pin
bt_success_t bt_setoneio(uint8 number);
bt_success_t bt_resetoneio(uint8 number);

// 18 Set/Reset multiple User I/O pin
bt_success_t bt_setio(uint16 io);

// 19 Query User I/O pin
uint16 bt_getio(void);

// 20 Query/Set Scanning Parameters
bt_scanparam_t bt_getscanparam(void);
bt_success_t bt_setscanparam(bt_scanparam_t param);

// 21 Query/Set SNIFF Energy Savings Parameters
bt_snifftime_t bt_getsnifftime(void);
bt_success_t bt_setsnifftime(bt_snifftime_t time);

// 22 Query/Set Security & Encryption Modes
bt_secencmode_t bt_getsecencmode(void);
bt_success_t bt_setsecencmode(bt_secencmode_t mode);

// 23 Delete Authenticated Device from List
bt_success_t bt_deldev(bt_addr_t addr);

// 24 Find Device from Authenticated Device List
bt_success_t bt_finddev(bt_addr_t addr);

// 25 Query Total Number of Device fromc Authenticated Device List 1A Invalid/zero lenght address entered
uint16 bt_getnumdev(void);

// 26 Query Most Recently Used Authenticated Device
bt_addr_t bt_mostused(void);

// 27 Query Current Status of the Device
bt_status_t bt_getstatus(void);

// 28 Initialize SPP Profile
bt_status_t bt_initspp(void);

// 29 Query Nearby Discoverable Devices
bt_addr_t bt_discovdev(void); // May need to be reconfigured

// 30 Cancel Search for Discoverable Devices
bt_success_t bt_cancel(void);

// 31 Device Pairing
bt_success_t bt_pair(bt_addr_t addr, uint8 timeout);

// 32 Connect to a Remote Device
bt_success_t bt_connect(bt_addr_t addr);

// 33 Disconnect from a Remote Device
bt_results_t bt_disconnect(void);

// 34 Enter Energy Saving mode
bt_success_t bt_enter_energysave(bt_addr_t addr);

// 35 Exit Energy Saving mode
bt_success_t bt_exit_energysave(bt_addr_t addr);


#endif /* BLUETOOTH_H_ */
