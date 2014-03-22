/*
 * encoder.c
 *
 *  Created on: Mar 20, 2014
 *      Author: Daniel
 */

#include "hardware.h"
#include "i2c.h"
#include "encoder.h"

/**
 * Function to check, if encoder is present
 * @return response if encoder present
 */
Com_Status_t testencoder()
{
    Com_Status_t com_status;
    com_status = i2c_start(IIC_ADR_ENCODER, I2C_READ);
    i2c_stop();
    return com_status;
}

/**
 * Function to read encoder status
 * @param *data pointer to an array to store status. Needs to be minimum 12 bytes long. 
 * @return response if encoder present
 */
Com_Status_t readencoder(uint8 *data)
{
    Com_Status_t com_status;
    com_status = i2c_start(IIC_ADR_ENCODER, I2C_WRITE);
    com_status |= i2c_sendbyte(0x00);
    com_status |= i2c_restart(IIC_ADR_ENCODER, I2C_READ);
    i2c_readdata(data, ENC_DATA_SIZE);
    i2c_stop();
    return com_status;
}

/**
 * Function to set up encoder
 * @param status to be written to encoder 
 * @return response if encoder present
 */
Com_Status_t setupencoder(enc_setup_t setup)
{
    Com_Status_t com_status;
    com_status = i2c_start(IIC_ADR_ENCODER, I2C_WRITE);
    com_status |= i2c_sendbyte(0x00);
    com_status |= i2c_sendbyte(setup.byte);
    i2c_stop();
    return com_status;
}
