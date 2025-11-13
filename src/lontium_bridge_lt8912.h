/*
 * lontium_bridge_lt8912.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef LONTIUM_BRIDGE_LT8912_H_
#define LONTIUM_BRIDGE_LT8912_H_

#include "stdbool.h"
#include "hal_entry.h"
#include "hal_data.h"

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

#define AR_ND       0x00
#define AR_4_3      0x01
#define AR_16_9     0x02



static int hdmi_connected = 0;

enum lt8912_i2c_addr {
    I2C_ADDR_MAIN = 0x48,
    I2C_ADDR_CEC_DSI = 0x49,
    I2C_ADDR_I2S = 0x4a,
};


typedef struct video_timing{
    uint16_t hfp;
    uint16_t hs;
    uint16_t hbp;
    uint16_t hact;
    uint16_t htotal;
    uint16_t vfp;
    uint16_t vs;
    uint16_t vbp;
    uint16_t vact;
    uint16_t vtotal;
    _Bool h_polarity;
    _Bool v_polarity;
    uint16_t vic;
    uint16_t aspact_ratio;  // 0=no data, 1=4:3, 2=16:9, 3=no data.
    uint32_t pclk_khz;
}_video_timing;

typedef struct panel_parameter
{
        uint16_t hfp;
        uint16_t hs;
        uint16_t hbp;
        uint16_t hact;
        uint16_t htotal;
        uint16_t vfp;
        uint16_t vs;
        uint16_t vbp;
        uint16_t vact;
        uint16_t vtotal;
        uint16_t pclk_khz;
}_panel_parameter;

extern uint8_t Tx_HPD;

void DigitalClockEn(void);
void TxAnalog(void);
void CbusAnalog(void);
void HDMIPllAnalog(void);
void AviInfoframe(struct video_timing *video_format);
void MipiAnalog(void);
void MipiBasicSet();
void MIPI_Video_Setup(struct video_timing *video_format);
void MIPIRxLogicRes(void);
void DDSConfig(void);
void AudioIIsEn(void);
void AudioSpdifEn(void);
void Core_Pll_setup(struct panel_parameter *panel);
void Core_Pll_bypass(void);
void Lvds_Pll_Reset(void);
void Scaler_bypass(void);
void Scaler_setup(struct video_timing *input_video,struct panel_parameter *panel);
void LvdsPowerUp(void);
void LvdsPowerDown(void);
void LvdsBypass(void);
void LvdsOutput(_Bool on);
void HdmiOutput(_Bool on);
void LvdsScalerResult(void);
void ScalerReset(void);
void lt8912_check_dds(void);
void lvds_output_cfg(void);
void MIPI_Input_det(void);
void pattern_test(void);
uint8_t LT8912_Get_HPD(void);
uint16_t LT8912B_GetChipID(void);
void LT8912B_Suspend(_Bool on);
void LT8912B_Config(void);
void HDMI_Test_Pattern(void);


#endif /* LONTIUM_BRIDGE_LT8912_H_ */
