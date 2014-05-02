/*
 * bluetooth.c
 *
 *  Created on: May 1, 2014
 *      Author: daniw
 */

#include "bluetooth.h"

// 0 init commanc mode
void bt_joincmdmode(void)
{

}

void bt_partcmdmode(void)
{

}

// 1 test UART connection
bt_success_t bt_test(void)
{

}

// 2 reset device
bt_success_t bt_reset(void)
{

}

// 3 query firmware version
bt_success_t bt_version(void)
{

}

// 4 restore settings to factory defaults
bt_success_t bt_factoryreset(void)
{

}

// 5 query EGBT-045MS bluetooth address
bt_addr_t bt_address(void)
{

}

// 6 query/set device name
bt_success_t bt_getname(char* name)
{

}

bt_success_t bt_setname(char* name)
{

}

// 7 query remote bluetooth device's name
 bt_getremotename(bt_addr_t addr)
{

}

// 8 query/set device role
bt_role_t bt_getrole(void)
{

}

bt_success_t bt_setrole(bt_role_t role)
{

}

// 9 query/set class f device CoD
bt_class_t bt_getclass(void)
{

}

bt_success_t bt_setclass(bt_class_t class)
{

}

// 10 Query/Set Inquire Access Code
uint32 bt_getaccesscode(void)
{

}

bt_success_t bt_setaccesscode(uint32 code)
{

}

// 11 Query/Set Inquire Access Mode
bt_accessmode_t bt_getaccessmode(void)
{

}

bt_success_t bt_setaccessmode(bt_accessmode_t mode)
{

}

// 12 Query/Set Pairing Passkey
bt_success_t bt_getkey(char* key)
{

}

bt_success_t bt_setkey(char* key)
{

}

// 13 Query/Set UART parameter
bt_uartparam_t bt_getparam(void)
{

}

bt_success_t bt_setparam(bt_uartparam_t param)
{

}

// 14 Query/Set Connection Mode
bt_conmode_t bt_getconmode(void)
{

}

bt_success_t bt_setconmode(bt_conmode_t mode)
{

}

// 15 Query/Set Binding Bluetooth Address
bt_addr_t bt_getbindaddr(void)
{

}

bt_success_t bt_setbindaddr(bt_addr_t addr)
{

}

// 16 Query/Set LED Output Polarity
bt_pol_t bt_getpol(void)
{

}

bt_success_t bt_setpol(bt_pol_t polarity)
{

}

// 17 Set/Reset a User I/O pin
bt_success_t bt_setoneio(uint8 number)
{

}

bt_success_t bt_resetoneio(uint8 number)
{

}

// 18 Set/Reset multiple User I/O pin
bt_success_t bt_setio(uint16 io)
{

}

// 19 Query User I/O pin
uint16 bt_getio(void)
{

}

// 20 Query/Set Scanning Parameters
bt_scanparam_t bt_getscanparam(void)
{

}

bt_success_t bt_setscanparam(bt_scanparam_t param)
{

}

// 21 Query/Set SNIFF Energy Savings Parameters
bt_snifftime_t bt_getsnifftime(void)
{

}

bt_success_t bt_setsnifftime(bt_snifftime_t time)
{

}

// 22 Query/Set Security & Encryption Modes
bt_secencmode_t bt_getsecencmode(void)
{

}

bt_success_t bt_setsecencmode(bt_secencmode_t mode)
{

}

// 23 Delete Authenticated Device from List
bt_success_t bt_deldev(bt_addr_t addr)
{

}

// 24 Find Device from Authenticated Device List
bt_success_t bt_finddev(bt_addr_t addr)
{

}

// 25 Query Total Number of Device fromc Authenticated Device List 1A Invalid/zero lenght address entered
uint16 bt_getnumdev(void)
{

}

// 26 Query Most Recently Used Authenticated Device
bt_addr_t bt_mostused(void)
{

}

// 27 Query Current Status of the Device
bt_status_t bt_getstatus(void)
{

}

// 28 Initialize SPP Profile
bt_status_t bt_initspp(void)
{

}

// 29 Query Nearby Discoverable Devices
bt_addr_t bt_discovdev(void) // May need to be reconfigured
{

}

// 30 Cancel Search for Discoverable Devices
bt_success_t bt_cancel(void)
{

}

// 31 Device Pairing
bt_success_t bt_pair(bt_addr_t addr, uint8 timeout)
{

}

// 32 Connect to a Remote Device
bt_success_t bt_connect(bt_addr_t addr)
{

}

// 33 Disconnect from a Remote Device
bt_results_t bt_disconnect(void)
{

}

// 34 Enter Energy Saving mode
bt_success_t bt_enter_energysave(bt_addr_t addr)
{

}

// 35 Exit Energy Saving mode
bt_success_t bt_exit_energysave(bt_addr_t addr)
{

}

