/*
 * i2c_controller.c
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */


#include "i2c_controller.h"
#include "common_utils.h"


static fsp_err_t wait_i2c_event(i2c_master_event_t expected_event);

static volatile i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

fsp_err_t I2C_WriteByte(uint8_t device_address, uint8_t reg_address, uint8_t data){
    fsp_err_t err;
    uint8_t buf[2];

    buf[0] = reg_address;
    buf[1] = data;

    err = R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, device_address, I2C_MASTER_ADDR_MODE_7BIT);
    if (err != FSP_SUCCESS) return err;

    i2c_event = RESET_VALUE;
    err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, buf, 2, false);
    if (err != FSP_SUCCESS) return err;

    return wait_i2c_event(I2C_MASTER_EVENT_TX_COMPLETE);
}


fsp_err_t I2C_ReadByte(uint8_t device_address, uint8_t reg_address, uint8_t* data){
    fsp_err_t err;

      err = R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, device_address, I2C_MASTER_ADDR_MODE_7BIT);
      if (err != FSP_SUCCESS) return err;

      i2c_event = RESET_VALUE;
      err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &reg_address, 1, true);
      if (err != FSP_SUCCESS) return err;

      err = wait_i2c_event(I2C_MASTER_EVENT_TX_COMPLETE);
      if (err != FSP_SUCCESS) return err;

      i2c_event = RESET_VALUE;
      err = R_IIC_MASTER_Read(&g_i2c_master0_ctrl, data, 1, false);
      if (err != FSP_SUCCESS) return err;

      return wait_i2c_event(I2C_MASTER_EVENT_RX_COMPLETE);
}


/*******************************************************************************************************************//**
 *  @brief      User callback function
 *  @param[in]  p_args
 *  @retval None
 **********************************************************************************************************************/
void i2c_master_callback(i2c_master_callback_args_t *p_args){
    if (p_args != NULL){
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
    }
}

static fsp_err_t wait_i2c_event(i2c_master_event_t expected_event)
{
    uint32_t timeout = 0xFFFFF;

    while ((i2c_event == RESET_VALUE) && timeout--)
    {
        __NOP();
    }

    if (timeout == 0)
    {
        return FSP_ERR_TRANSFER_ABORTED;
    }

    if (i2c_event != expected_event)
    {
        return FSP_ERR_TRANSFER_ABORTED;
    }

    return FSP_SUCCESS;
}


