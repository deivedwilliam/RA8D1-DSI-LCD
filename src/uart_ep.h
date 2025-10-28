/*
 * uart_ep.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef UART_EP_H_
#define UART_EP_H_

/* Macro definition */
#define CARRIAGE_ASCII            (13u)     /* Carriage return */
#define ZERO_ASCII                (48u)     /* ASCII value of zero */
#define NINE_ASCII                (57u)     /* ASCII value for nine */
#define DATA_LENGTH               (4u)      /* Expected Input Data length */
#define UART_ERROR_EVENTS         (UART_EVENT_BREAK_DETECT | UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | \
                                    UART_EVENT_ERR_PARITY)    /* UART Error event bits mapped in registers */


fsp_err_t uart_print_user_msg(uint8_t *p_msg);
fsp_err_t uart_initialize(void);
void deinit_uart(void);

#endif /* UART_EP_H_ */
