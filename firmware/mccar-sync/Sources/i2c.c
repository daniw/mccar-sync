/*
 * i2c.c
 *
 *  Created on: Mar 15, 2014
 *      Author: daniw
 */

#include "platform.h"
#include "hardware.h"
#include "i2c.h"

/**
 * Function to generate start condition on i2c bus and address a slave
 * @param address i2c slave address
 * @param dir     direction of communication following start command
 * @return response of slave
 */
Com_Status_t i2c_start(uint8 address, I2C_Dir_t dir)
{
    while (IICS_BUSY){}                     // wait until i2c module is ready

    IICC1_TX = 1;                           // prepare module for sending address to slave
    IICC1_MST = 1;                          // generate start condition
    IICD = (address << 1) | (dir == I2C_WRITE?0:1); // start communication by sending slave address and data direction bit
    while (!IICS_IICIF){}                   // wait until address has been sent
    IICS_IICIF = 1;                         // clear interrupt flag

    if (!IICS_RXAK)                         // slave responding?
    {
        return COM_SUCCESS;                 // addressing slave successful
    }
    else                                    // no slave responded
    {
        i2c_stop();                         // stop transmission
        return COM_FAILED;                  // addressing slave failed
    }
}

/**
 * Function to generate stop condition on i2c bus
 */
void i2c_stop(void)
{
    IICC_MST = 0;                           // send stop condition
    IICS_IICIF = 1;                         // clear interrupt flag
}

/**
 * Function to generate a start condition during a communication to change the data direction. 
 * @param address i2c slave address
 * @param dir     direction of communication following start command
 * @return response of slave
 */
Com_Status_t i2c_restart(uint8 address, I2C_Dir_t dir)
{
    IICC1_RSTA = 1;                         // send start condition again to change data direction
    IICD = (address << 1) | (dir == I2C_WRITE?0:1); // start communication by sending slave address and data direction bit
    while (!IICS_IICIF){}                   // wait until address has been sent
    IICS_IICIF = 1;                         // clear interrupt flag

    if (!IICS_RXAK)                         // slave responding?
    {
        return COM_SUCCESS;                 // addressing slave successful, data direction successfully changed
    }
    else                                    // no slave responded
    {
        i2c_stop();                         // stop transmission
        return COM_FAILED;                  // addressing slave failed
    }
}

/**
 * Function to send one byte of data to slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @param data data to be sent
 * @return response of slave
 */
Com_Status_t i2c_sendbyte(uint8 data)
{
    IICD = data;                            // send data
    while (!IICS_IICIF){}                   // wait until byte has been sent
    IICS_IICIF = 1;                         // clear interrupt flag
    if (!IICS_RXAK)                         // slave responding?
    {
        return COM_SUCCESS;                 // sending data successful
    }
    else                                    // slave did not respond
    {
        i2c_stop();                         // stop transmission
        return COM_FAILED;                  // sending data failed
    }
}

/**
 * Function to read one byte of data from slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @return data received from slave
 */
uint8 i2c_readbyte(void)
{
    uint8 temp;                             // temporary variable for reading data register to
    IICC_TX = 0;                            // change module to receiving mode
    IICC_TXAK = 1;                          // send no ack after receiving data
    temp = IICD;                            // read data register to start transmission
    while(!IICS_IICIF){}                    // wait until data has been received
    IICS_IICIF = 1;                         // clear interrupt flag
    return IICD;                            // read received data
}

/**
 * Function to send data to slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @param data pointer to data to be sent to slave
 * @param size number of bytes to be sent
 * @return response from slave
 */
Com_Status_t i2c_senddata(uint8 *data, uint8 size)
{
    uint8 i;                                // counting variable to iterate through data
    for (i = 0; i < size; i++)
    {
        IICD = data[i];                     // send data
//        IICD = *(data++);                   // send data
        while (!IICS_IICIF){}               // wait until byte has been sent
        IICS_IICIF = 1;                     // clear interrupt flag
        if (IICS_RXAK)                      // slave not responding?
        {
            i2c_stop();                     // stop transmission
            return COM_FAILED;              // sending data failed
        }
    }
    return COM_SUCCESS;
}

/**
 * Function to receive data from slave
 * This function expects the i2c communication to be started by the function i2c_start()
 * @param data pointer to save received data. This data will be changed after execution
 * @param size number of bytes to receive
 */
void i2c_readdata(uint8 *data, uint8 size)
{
    uint8 i;                                // counting variable to iterate through data
    IICC_TX = 0;                            // change module to receiving mode
    IICC_TXAK = (size > 1 ? 0 : 1);         // send ack after receiving data if reading more than one byte
    data[0] = IICD;                         // read data register to start transmission
//    *data = IICD;                           // read data register to start transmission
    for (i = 0; i < size; i++)
    {
        while(!IICS_IICIF){}                // wait until data has been received
        IICS_IICIF = 1;                     // clear interrupt flag
        if (i >= size - 1)
        {
            IICC1_TXAK = 1;                 // send no ack after last byte
        }
        data[i] = IICD;                     // read received data
//        *(data++) = IICD;                   // read received data
    }
    while(!IICS_IICIF){}                    // wait until data has been received
    IICS_IICIF = 1;                         // clear interrupt flag
    return;
}
