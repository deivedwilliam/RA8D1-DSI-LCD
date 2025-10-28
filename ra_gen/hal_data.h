/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_sci_b_uart.h"
#include "r_uart_api.h"
#include "r_iic_master.h"
#include "r_i2c_master_api.h"
FSP_HEADER
/** UART on SCI Instance. */
extern const uart_instance_t g_uart4;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_uart4_ctrl;
extern const uart_cfg_t g_uart4_cfg;
extern const sci_b_uart_extended_cfg_t g_uart4_cfg_extend;

#ifndef usart_callback
void usart_callback(uart_callback_args_t *p_args);
#endif
/* I2C Master on IIC Instance. */
extern const i2c_master_instance_t g_i2c_master0;

/** Access the I2C Master instance using these structures when calling API functions directly (::p_api is not used). */
extern iic_master_instance_ctrl_t g_i2c_master0_ctrl;
extern const i2c_master_cfg_t g_i2c_master0_cfg;

#ifndef i2c_master_callback
void i2c_master_callback(i2c_master_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
