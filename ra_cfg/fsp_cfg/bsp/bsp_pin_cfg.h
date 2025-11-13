/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define DEAD_PIN (BSP_IO_PORT_02_PIN_00)
#define BACKLIGHT (BSP_IO_PORT_04_PIN_08)
#define LED_STATE (BSP_IO_PORT_04_PIN_11)
#define DSI_DEST_SELECT (BSP_IO_PORT_04_PIN_12)
#define UART4_RX (BSP_IO_PORT_04_PIN_14)
#define UART4_TX (BSP_IO_PORT_04_PIN_15)
#define RESET_N (BSP_IO_PORT_07_PIN_06)

extern const ioport_cfg_t g_bsp_pin_cfg; /* R7FA8D1BHECFC.pincfg */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
