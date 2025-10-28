/*
 * i2c_controller.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef I2C_CONTROLLER_H_
#define I2C_CONTROLLER_H_

#include "hal_data.h"
#include "hal_entry.h"


fsp_err_t I2C_WriteByte(uint8_t device_address, uint8_t reg_address, uint8_t data);
fsp_err_t I2C_ReadByte(uint8_t device_address, uint8_t reg_address, uint8_t* data);


#endif /* I2C_CONTROLLER_H_ */
