/*
 * encoder.h
 *
 *  Created on: Mar 20, 2014
 *      Author: Daniel
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "i2c.h"

#define ENC_DATA_SIZE 13        // Size of encoder memory

typedef enum Enc_Mode_
{
    ENC_OFF,
    ENC_ON,
    ENC_CAL
    //ENC_UNDEF
} Enc_Mode_t;

typedef union enc_setup_
{
    uint8 byte;
    struct flags_
    {
        uint8 encmode0  : 1;
        uint8 encmode1  : 1;
        uint8 encrestic : 1;
        uint8 encreserr : 1;
        uint8 carrieren : 1;
        uint8 oleden    : 1;
        uint8 unused    : 1;
        uint8 power     : 1;
    } flags;
    struct mergedflags_
    {
        uint8 encmode   : 2;
        uint8 encrestic : 1;
        uint8 encreserr : 1;
        uint8 carrieren : 1;
        uint8 oleden    : 1;
        uint8 unused    : 1;
        uint8 power     : 1;
    } mergedflags;
} enc_setup_t;

typedef union enc_data_
{
    uint8 array[ENC_DATA_SIZE];
    struct bytes_
    {
        enc_setup_t setup;
        uint8       speed_l_high;
        uint8       speed_l_low;
        uint8       speed_r_high;
        uint8       speed_r_low;
        uint8       ticks_l_high;
        uint8       ticks_l_low;
        uint8       ticks_r_high;
        uint8       ticks_r_low;
        uint8       error_l;
        uint8       error_r;
        uint8       carrier_mod_high;
        uint8       carrier_mod_low;
    } bytes;
    struct fields_
    {
        enc_setup_t setup;
        uint16      speed_l;
        uint16      speed_r;
        uint16      ticks_l;
        uint16      ticks_r;
        uint8       error_l;
        uint8       error_r;
        uint16      carrier_mod_high;
    } fields;
} enc_data_t;


/**
 * Function to check, if encoder is present
 * @return response if encoder present
 */
Com_Status_t testencoder();

/**
 * Function to read encoder status
 * @param *data pointer to an array to store status. Needs to be minimum 12 bytes long. 
 * @return response if encoder present
 */
Com_Status_t readencoder(enc_data_t *data);

/**
 * Function to set up encoder
 * @param status to be written to encoder 
 * @return response if encoder present
 */
Com_Status_t setupencoder(enc_setup_t setup);

#endif /* ENCODER_H_ */
