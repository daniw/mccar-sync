/*
 * encoder.h
 *
 *  Created on: Mar 20, 2014
 *      Author: Daniel
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "i2c.h"

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
Com_Status_t readencoder(uint8 *data);

/**
 * Function to set up encoder
 * @param status to be written to encoder 
 * @return response if encoder present
 */
Com_Status_t setupencoder(enc_setup_t setup);

#endif /* ENCODER_H_ */
