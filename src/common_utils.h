/*
 * commom_utils.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef COMMOM_UTILS_H_
#define COMMOM_UTILS_H_


/* generic headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hal_data.h"

/* SEGGER RTT and error related headers */
/* SEGGER RTT disabling macro */
#define DISABLE_APP_PRINT       (0)
#define DISABLE_APP_ERR_PRINT   (0)
#define DISABLE_APP_ERR_TRAP    (0)
#define DISABLE_APP_READ        (0)
#define DISABLE_APP_CHECK_DATA  (0)


#define BIT_SHIFT_8  (8u)
#define SIZE_64      (64u)

#define LVL_ERR      (1u)       /* error conditions   */

#define RESET_VALUE             (0x00)

#define EP_VERSION              ("1.0")
#define MODULE_NAME             "r_sci_uart"
#define BANNER_1                "\r\n******************************************************************"
#define BANNER_2                "\r\n*   Renesas FSP Example Project for "MODULE_NAME" Module            *"
#define BANNER_3                "\r\n*   Example Project Version %s                                  *"
#define BANNER_4                "\r\n*   Flex Software Pack Version  %d.%d.%d                            *"
#define BANNER_5                "\r\n******************************************************************"
#define BANNER_6                "\r\nRefer to readme.txt file for more details on Example Project and" \
        "\r\nFSP User's Manual for more information about "MODULE_NAME" driver\r\n"

#define SEGGER_INDEX            (0)

//#define APP_PRINT(fn_, ...)      (SEGGER_RTT_printf (SEGGER_INDEX,(fn_), ##__VA_ARGS__))

#define APP_READ(read_data)     (SEGGER_RTT_Read (SEGGER_INDEX, (read_data), sizeof(read_data)))

#define APP_CHECK_DATA          (SEGGER_RTT_HasKey())

/* Conditional disabling logic */
#if defined(APP_PRINT) && (DISABLE_APP_PRINT == 1)
#undef APP_PRINT
#define APP_PRINT(fn_, ...)
#endif

#if defined(APP_ERR_PRINT) && (DISABLE_APP_ERR_PRINT == 1)
#undef APP_ERR_PRINT
#define APP_ERR_PRINT(fn_, ...)
#endif

#if defined(APP_ERR_TRAP) && (DISABLE_APP_ERR_TRAP == 1)
#undef APP_ERR_TRAP
#define APP_ERR_TRAP(err)
#endif

#if defined(APP_READ) && (DISABLE_APP_READ == 1)
#undef APP_READ
#define APP_READ(read_data)
#endif

#if defined(APP_CHECK_DATA) && (DISABLE_APP_CHECK_DATA == 1)
#undef APP_CHECK_DATA
#define APP_CHECK_DATA (0)
#endif


#endif /* COMMOM_UTILS_H_ */
