/*
 * bluetooth.c
 *
 *  Created on: May 1, 2014
 *      Author: daniw
 */

#include "bluetooth.h"

extern Queue bt_sendQueue;
extern Queue bt_receiveQueue;


static uint8 busy = 0;
static uint8 bt_str[64];

// 0 init command mode
void bt_joincmdmode(void)
{
    if (!busy)
    {
        bt_cmdon();
    }
}

void bt_partcmdmode(void)
{
    if (!busy)
    {
        bt_cmdoff();
    }
}

// 1 test UART connection
bt_success_t bt_test(void)
{
    bt_str[0] = 'A';
    bt_str[1] = 'T';
    bt_str[2] = '+';
    bt_str[3] = '\r';
    bt_str[4] = '\n';
    bt_senddata(bt_str, 4);

    return SUCCESS;
}

// 2 reset device
bt_success_t bt_reset(void)
{
	bt_str[0] = 'A';
	bt_str[1] = 'T';
	bt_str[2] = '+';
	bt_str[3] = 'R';
	bt_str[4] = 'E';
	bt_str[5] = 'S';
	bt_str[6] = 'E';
	bt_str[7] = 'T';
	bt_str[8] = '\r';
	bt_str[9] = '\n';
    bt_senddata(bt_str, 10);

    return SUCCESS;
}

// 3 query firmware version
bt_success_t bt_version(void)
{
    bt_str[0] = 'A';
	bt_str[1] = 'T';
	bt_str[2] = '+';
	bt_str[3] = 'V';
	bt_str[4] = 'E';
	bt_str[5] = 'R';
	bt_str[6] = 'S';
	bt_str[7] = 'I';
	bt_str[8] = 'O';
	bt_str[9] = 'N';
	bt_str[10] = '?';
	bt_str[11] = '\r';
	bt_str[12] = '\n';
    bt_senddata(bt_str, 13);

    return SUCCESS;
}

// 4 restore settings to factory defaults
bt_success_t bt_factoryreset(void)
{
    bt_str[0] = 'A';
	bt_str[1] = 'T';
	bt_str[2] = '+';
	bt_str[3] = 'O';
	bt_str[4] = 'R';
	bt_str[5] = 'G';
	bt_str[6] = 'L';
	bt_str[7] = '\r';
	bt_str[8] = '\n';
    bt_senddata(bt_str, 9);

    return SUCCESS;
}

// 5 query EGBT-045MS bluetooth address
bt_addr_t bt_address(void)
{
	bt_addr_t addr;

    bt_str[0] = 'A';
	bt_str[1] = 'T';
	bt_str[2] = '+';
	bt_str[3] = 'A';
	bt_str[4] = 'D';
	bt_str[5] = 'D';
	bt_str[6] = 'R';
	bt_str[7] = '?';
	bt_str[8] = '\r';
	bt_str[9] = '\n';
    bt_senddata(bt_str, 10);

    return addr;
}

// 6 query/set device name
bt_success_t bt_getname(char* name)
{
	return SUCCESS;
}

bt_success_t bt_setname(char* name)
{
	return SUCCESS;
}

// 7 query remote bluetooth device's name
char bt_getremotename(bt_addr_t addr)
{
	 return 0;
}

// 8 query/set device role
bt_role_t bt_getrole(void)
{
	return 0;
}

bt_success_t bt_setrole(bt_role_t role)
{
	return SUCCESS;
}

// 9 query/set class f device CoD
bt_class_t bt_getclass(void)
{
	return 0;
}

bt_success_t bt_setclass(bt_class_t class)
{
	return SUCCESS;
}

// 10 Query/Set Inquire Access Code
uint32 bt_getaccesscode(void)
{
	return 0;
}

bt_success_t bt_setaccesscode(uint32 code)
{
	return SUCCESS;
}

// 11 Query/Set Inquire Access Mode
bt_accessmode_t bt_getaccessmode(void)
{
	bt_accessmode_t mode;
	mode.maxnumber = 0;
	mode.mode = STANDARD;
	mode.timeout = 0;
	return mode;
}

bt_success_t bt_setaccessmode(bt_accessmode_t mode)
{
	return SUCCESS;
}

// 12 Query/Set Pairing Passkey
bt_success_t bt_getkey(char* key)
{
	return SUCCESS;
}

bt_success_t bt_setkey(char* key)
{
	return SUCCESS;
}

// 13 Query/Set UART parameter
bt_uartparam_t bt_getparam(void)
{
	bt_uartparam_t param;
	param.baud = BT_BAUD_9600;
	param.parity = NOPARITY;
	param.stop = ONE;
	return param;
}

bt_success_t bt_setparam(bt_uartparam_t param)
{
	uint8 ret[4];

    bt_str[0]  = 'A';
	bt_str[1]  = 'T';
	bt_str[2]  = '+';
	bt_str[3]  = 'U';
	bt_str[4]  = 'A';
	bt_str[5]  = 'R';
	bt_str[6]  = 'T';
	bt_str[7]  = '=';
    bt_str[8]  = '1';
    bt_str[9]  = '1';
    bt_str[10] = '5';
    bt_str[11] = '2';
    bt_str[12] = '0';
    bt_str[13] = '0';
    bt_str[14] = ',';
    bt_str[15] = '0';
    bt_str[16] = ',';
    bt_str[17] = '0';
	bt_str[18] = '\r';
	bt_str[19] = '\n';
    bt_enqueue(bt_str, 20);
    while (!queue_dequeue(&bt_receiveQueue, ret, 4));
    if (ret[0] == 'O' && ret[1] == 'K' && ret[2] == '\r' && ret[3] == '\n')
    {
	    return SUCCESS;
    }
    else
    {
        return FAILED;
    }
}

// 14 Query/Set Connection Mode
bt_conmode_t bt_getconmode(void)
{
	return CON_SPEC;
}

bt_success_t bt_setconmode(bt_conmode_t mode)
{
	return SUCCESS;
}

// 15 Query/Set Binding Bluetooth Address
bt_addr_t bt_getbindaddr(void)
{
	bt_addr_t addr;
	addr.ll = 0;
	addr.nn = 0;
	addr.uu = 0;
	return addr;
}

bt_success_t bt_setbindaddr(bt_addr_t addr)
{
	return SUCCESS;
}

// 16 Query/Set LED Output Polarity
bt_pol_t bt_getpol(void)
{
	return HIGHHIGH;
}

bt_success_t bt_setpol(bt_pol_t polarity)
{
	return SUCCESS;
}

// 17 Set/Reset a User I/O pin
bt_success_t bt_setoneio(uint8 number)
{
	return SUCCESS;
}

bt_success_t bt_resetoneio(uint8 number)
{
	return SUCCESS;
}

// 18 Set/Reset multiple User I/O pin
bt_success_t bt_setio(uint16 io)
{
	return SUCCESS;
}

// 19 Query User I/O pin
uint16 bt_getio(void)
{
	return 0;
}

// 20 Query/Set Scanning Parameters
bt_scanparam_t bt_getscanparam(void)
{
	bt_scanparam_t param;
	param.duration = 0;
	param.interval = 0;
	param.pagedur = 0;
	param.pageint = 0;
	return param;
}

bt_success_t bt_setscanparam(bt_scanparam_t param)
{
	return SUCCESS;
}

// 21 Query/Set SNIFF Energy Savings Parameters
bt_snifftime_t bt_getsnifftime(void)
{
	bt_snifftime_t time;
	time.maxtime = 0;
	time.mintime = 0;
	time.retry = 0;
	time.timeout = 0;
	return time;
}

bt_success_t bt_setsnifftime(bt_snifftime_t time)
{
	return SUCCESS;
}

// 22 Query/Set Security & Encryption Modes
bt_secencmode_t bt_getsecencmode(void)
{
	bt_secencmode_t mode;
	mode.encmode = SECOFF;
	mode.secmode = ENCOFF;
	return mode;
}

bt_success_t bt_setsecencmode(bt_secencmode_t mode)
{
	return SUCCESS;
}

// 23 Delete Authenticated Device from List
bt_success_t bt_deldev(bt_addr_t addr)
{
	return SUCCESS;
}

// 24 Find Device from Authenticated Device List
bt_success_t bt_finddev(bt_addr_t addr)
{
	return SUCCESS;
}

// 25 Query Total Number of Device fromc Authenticated Device List 1A Invalid/zero lenght address entered
uint16 bt_getnumdev(void)
{
	return 0;
}

// 26 Query Most Recently Used Authenticated Device
bt_addr_t bt_mostused(void)
{
	bt_addr_t addr;
	addr.ll = 0;
	addr.nn = 0;
	addr.uu = 0;
	return addr;
}

// 27 Query Current Status of the Device
bt_status_t bt_getstatus(void)
{
	return UNKNOWNSTATUS;
}

// 28 Initialize SPP Profile
bt_status_t bt_initspp(void)
{
	return UNKNOWNSTATUS;
}

// 29 Query Nearby Discoverable Devices
bt_addr_t bt_discovdev(void) // May need to be reconfigured
{
	bt_addr_t addr;
	addr.ll = 0;
	addr.nn = 0;
	addr.uu = 0;
	return addr;
}

// 30 Cancel Search for Discoverable Devices
bt_success_t bt_cancel(void)
{
	return SUCCESS;
}

// 31 Device Pairing
bt_success_t bt_pair(bt_addr_t addr, uint8 timeout)
{
	return SUCCESS;
}

// 32 Connect to a Remote Device
bt_success_t bt_connect(bt_addr_t addr)
{
	return SUCCESS;
}

// 33 Disconnect from a Remote Device
bt_results_t bt_disconnect(void)
{
	return BTSUCCESS;
}

// 34 Enter Energy Saving mode
bt_success_t bt_enter_energysave(bt_addr_t addr)
{
	return SUCCESS;
}

// 35 Exit Energy Saving mode
bt_success_t bt_exit_energysave(bt_addr_t addr)
{
	return SUCCESS;
}

