/*
 * i2c_controller.c
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */


#include "i2c_controller.h"
#include "common_utils.h"


static fsp_err_t validate_i2c_event(void);


static volatile i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

fsp_err_t I2C_WriteByte(uint8_t device_address, uint8_t reg_address, uint8_t data){
    fsp_err_t err = FSP_SUCCESS;

    err = R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, device_address, I2C_MASTER_ADDR_MODE_7BIT);
    if(FSP_ERR_TRANSFER_ABORTED == err)
    {
        printf("** R_IIC_MASTER_SlaveAddressSet API failed* \r\n");
        return err;
    }

    err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &reg_address, sizeof(uint8_t), true);
    validate_i2c_event();

    if(FSP_ERR_TRANSFER_ABORTED == err)
    {
       printf("** R_IIC_MASTER_Write API failed ** \r\n");
    }
    else
    {
       err  = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &data, sizeof(uint8_t), false);
       if (err != FSP_SUCCESS)
       {
           printf("** R_IIC_MASTER_Write API failed ** \r\n");
       }
       else
       {
           err = validate_i2c_event();
           /* handle error */
           if(err == FSP_ERR_TRANSFER_ABORTED)
           {
               printf("** I2C transfer failed, operation aborted** \r\n");
           }
       }
    }
    return err;
}


fsp_err_t I2C_ReadByte(uint8_t device_address, uint8_t reg_address, uint8_t* data){
    fsp_err_t err = FSP_SUCCESS;

    err = R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, device_address, I2C_MASTER_ADDR_MODE_7BIT);
    if(FSP_ERR_TRANSFER_ABORTED == err)
    {
        printf("** R_IIC_MASTER_SlaveAddressSet API failed* \r\n");
        return err;
    }

    err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &reg_address, sizeof(uint8_t), true);
    validate_i2c_event();

    if(FSP_ERR_TRANSFER_ABORTED == err)
    {
       printf("** R_IIC_MASTER_Write API failed ** \r\n");
    }
    else
    {
       err  = R_IIC_MASTER_Read(&g_i2c_master0_ctrl, data, sizeof(uint8_t), false);
       if (err != FSP_SUCCESS)
       {
           printf("** R_IIC_MASTER_Read API failed ** \r\n");
       }
       else
       {
           err = validate_i2c_event();
           /* handle error */
           if(err == FSP_ERR_TRANSFER_ABORTED)
           {
               printf("** I2C transfer failed, operation aborted** \r\n");
           }
       }
    }
    return err;
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


/*******************************************************************************************************************//**
 *  @brief       Validate i2c receive/transmit  based on required write read operation
 *
 *  @param[in]   None
 *
 *  @retval      FSP_SUCCESS                       successful event receiving returns FSP_SUCCESS
 *               FSP_ERR_TRANSFER_ABORTED          Either on timeout elapsed or received callback event is
 *                                                 I2C_MASTER_EVENT_ABORTED
 **********************************************************************************************************************/
static fsp_err_t validate_i2c_event(void)
{
    uint16_t local_time_out = UINT16_MAX;

    /* resetting call back event capture variable */
    i2c_event = (i2c_master_event_t)RESET_VALUE;

    do
    {
        /* This is to avoid infinite loop */
        --local_time_out;

        if(local_time_out == RESET_VALUE)
        {
            return FSP_ERR_TRANSFER_ABORTED;
        }

    }while(i2c_event == RESET_VALUE);

    if(i2c_event != I2C_MASTER_EVENT_ABORTED)
    {
        i2c_event = (i2c_master_event_t)RESET_VALUE;  // Make sure this is always Reset before return
        return FSP_SUCCESS;
    }

    i2c_event = (i2c_master_event_t)RESET_VALUE; // Make sure this is always Reset before return
    return FSP_ERR_TRANSFER_ABORTED;
}

