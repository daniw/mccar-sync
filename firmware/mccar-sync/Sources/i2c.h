/*
 * i2c.h
 *
 *  Created on: Mar 15, 2014
 *      Author: daniw
 */

#ifndef I2C_H_
#define I2C_H_

#include "platform.h"
#include "hardware.h"

typedef enum Com_Status_
{
    COM_SUCCESS,
    COM_FAILED
} Com_Status_t;

typedef enum I2C_Dir_
{
    I2C_READ,
    I2C_WRITE
} I2C_Dir_t;

/**
 * Function to generate start condition on i2c bus and address a slave
 * @param address i2c slave address
 * @param dir     direction of communication following start command
 * @return response of slave
 */
Com_Status_t i2c_start(uint8 address, I2C_Dir_t write);

/**
 * Function to generate stop condition on i2c bus
 */
void i2c_stop(void);

/**
 * Function to generate a start condition during a communication to change the data direction. 
 * @param address i2c slave address
 * @param dir     direction of communication following start command
 * @return response of slave
 */
Com_Status_t i2c_restart(uint8 address, I2C_Dir_t write);

/**
 * Function to send one byte of data to slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @param data data to be sent
 * @return response of slave
 */
Com_Status_t i2c_sendbyte(uint8 data);

/**
 * Function to read one byte of data from slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @return data received from slave
 */
uint8 i2c_readbyte(void);

/**
 * Function to send data to slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @param data pointer to data to be sent to slave
 * @param size number of bytes to be sent
 * @return response from slave
 */
Com_Status_t i2c_senddata(uint8 *data, uint8 size);

/**
 * Function to receive data from slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @param data pointer to save received data. This data will be changed after execution
 * @param size number of bytes to receive
 */
void i2c_readdata(uint8 *data, uint8 size);

#endif /* I2C_H_ */
