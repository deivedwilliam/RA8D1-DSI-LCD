/*
 * lontium_bridge_lt8912.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef LONTIUM_BRIDGE_LT8912_H_
#define LONTIUM_BRIDGE_LT8912_H_


#define EDID_ADDR 0x50
#define LT8912_REG_CHIP_REVISION_0          (0x00)
#define LT8912_REG_CHIP_REVISION_1          (0x01)

#define LT8912_VAL_CHIP_REVISION_0          (0x12)
#define LT8912_VAL_CHIP_REVISION_1          (0xB2)

#define LT8912_DSI_CEC_I2C_ADDR_REG         (0xE1)
#define LT8912_RESET_DELAY (100)

#define PINCTRL_STATE_ACTIVE    "pmx_lt8912_active"
#define PINCTRL_STATE_SUSPEND   "pmx_lt8912_suspend"

#define MDSS_MAX_PANEL_LEN      256
#define EDID_SEG_SIZE 0x100
/* size of audio and speaker info Block */
#define AUDIO_DATA_SIZE 32

/* 0x94 interrupts */
#define HPD_INT_ENABLE           BIT(7)
#define MONITOR_SENSE_INT_ENABLE BIT(6)
#define ACTIVE_VSYNC_EDGE        BIT(5)
#define AUDIO_FIFO_FULL          BIT(4)
#define EDID_READY_INT_ENABLE    BIT(2)

#define MAX_WAIT_TIME (100)
#define MAX_RW_TRIES (3)

/* 0x95 interrupts */
#define CEC_TX_READY             BIT(5)
#define CEC_TX_ARB_LOST          BIT(4)
#define CEC_TX_RETRY_TIMEOUT     BIT(3)
#define CEC_TX_RX_BUF3_READY     BIT(2)
#define CEC_TX_RX_BUF2_READY     BIT(1)
#define CEC_TX_RX_BUF1_READY     BIT(0)

#define HPD_INTERRUPTS           (HPD_INT_ENABLE | \
                    MONITOR_SENSE_INT_ENABLE)
#define EDID_INTERRUPTS          EDID_READY_INT_ENABLE
#define CEC_INTERRUPTS           (CEC_TX_READY | \
                    CEC_TX_ARB_LOST | \
                    CEC_TX_RETRY_TIMEOUT | \
                    CEC_TX_RX_BUF3_READY | \
                    CEC_TX_RX_BUF2_READY | \
                    CEC_TX_RX_BUF1_READY)

#define CFG_HPD_INTERRUPTS       BIT(0)
#define CFG_EDID_INTERRUPTS      BIT(1)
#define CFG_CEC_INTERRUPTS       BIT(3)

#define MAX_OPERAND_SIZE    14
#define CEC_MSG_SIZE            (MAX_OPERAND_SIZE + 2)


#define HDMI_MODE_480P   0
#define HDMI_MODE_720P   0
#define HDMI_MODE_1080P  1

static int hdmi_connected = 0;

enum lt8912_i2c_addr {
    I2C_ADDR_MAIN = 0x48,
    I2C_ADDR_CEC_DSI = 0x49,
    I2C_ADDR_I2S = 0x4a,
};


#endif /* LONTIUM_BRIDGE_LT8912_H_ */
