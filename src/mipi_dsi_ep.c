/*
 * mipi_dsi_ep.c
 *
 *  Created on: 27 de out. de 2025
 *      Author: Deived
 */


#include "mipi_dsi_ep.h"
#include "r_mipi_dsi_api.h"



#include "hal_data.h"

/* Flag volátil para sinalizar a conclusão de um comando DSI */
static volatile mipi_dsi_event_t g_dsi_event_flag;

const lcd_table_setting_t g_lcd_init_focuslcd[] =
{
 {0x04, {0xB9, 0xF1, 0x12, 0x87},  MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
 {0x04, {0xB2, 0xB4, 0x03, 0x70},  MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
 {0x0B, {0xB3, 0x10, 0x10, 0x28, 0x28, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00},  MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
 {0x02, {0xB4, 0x80},  MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_1_PARAM, MIPI_DSI_CMD_FLAG_LOW_POWER},
 {0x03, {0xB5, 0x0A, 0x0A},  MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
 {0x03, {0xB6, 0x8D, 0x8D},  MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER}, // SET VCOM
 {0x05, {0xB8, 0x26, 0x22, 0xF0, 0x13},  MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
};

/**
 * @brief Callback da MIPI DSI.
 * Esta função é chamada pela interrupção da DSI.
 *
 * IMPORTANTE: Você DEVE configurar o módulo r_mipi_dsi no FSP
 * para usar esta função como "Callback".
 */
void mipi_dsi_callback(mipi_dsi_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case MIPI_DSI_EVENT_SEQUENCE_0:
        {
            if (p_args->tx_status == MIPI_DSI_SEQUENCE_STATUS_DESCRIPTORS_FINISHED)
            {
              //  g_message_sent = SET_FLAG;
            }
            break;
        }
        case MIPI_DSI_EVENT_PHY:
        {
         //   g_phy_status |= p_args->phy_status;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * @brief      Callback functions for GLCDC interrupts
 *
 * @param[in]  p_args    Callback arguments
 * @retval     none
 **********************************************************************************************************************/
void glcdc_callback (display_callback_args_t * p_args)
{
    if (p_args->event == DISPLAY_EVENT_LINE_DETECTION)
    {
//        g_vsync_flag = SET_FLAG;
    }
}

