/*
 * mipi_dsi_ep.c
 *
 *  Created on: 27 de out. de 2025
 *      Author: Deived
 */


#include "mipi_dsi_ep.h"
#include "r_mipi_dsi.h"
#include "hal_data.h"
#include "common_utils.h"
#include "lontium_bridge_lt8912.h"



/* Variables to store resolution information */
uint16_t g_hz_size, g_vr_size;
/* Variables used for buffer usage */
uint32_t g_buffer_size, g_hstride;
uint32_t * gp_single_buffer = NULL;
uint32_t * gp_double_buffer = NULL;
uint32_t * gp_frame_buffer  = NULL;
uint8_t read_data              = RESET_VALUE;
uint16_t period_sec           = RESET_VALUE;

volatile mipi_dsi_phy_status_t g_phy_status;
volatile bool g_vsync_flag = RESET_FLAG;
volatile bool g_message_sent = RESET_FLAG;
volatile bool g_ulps_flag = RESET_FLAG;
volatile bool g_irq_state = RESET_FLAG;
static void display_draw (uint32_t * framebuffer);


const lcd_table_setting_t g_lcd_init_focuslcd[] =
{
    {0x04, {0xB9, 0xF1, 0x12, 0x87}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x04, {0xB2, 0xB4, 0x03, 0x70}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x0B, {0xB3, 0x10, 0x10, 0x28, 0x28, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x02, {0xB4, 0x80}, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_1_PARAM, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x03, {0xB5, 0x0A, 0x0A}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x03, {0xB6, 0x8D, 0x8D}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x05, {0xB8, 0x26, 0x22, 0xF0, 0x13}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x1C, {0xBA, 0x31, 0x81, 0x05, 0xF9, 0x0E, 0x0E, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x25, 0x00, 0x91, 0x0A, 0x00, 0x00, 0x01, 0x4F, 0x01, 0x00, 0x00, 0x37}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x02, {0xBC, 0x47}, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_1_PARAM, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x06, {0xBF, 0x02, 0x10, 0x00, 0x80, 0x04}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x0A, {0xC0, 0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x12, 0x73, 0x00}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x12, {0xC1, 0x36, 0x00, 0x32, 0x32, 0x77, 0xE1, 0x77, 0x77, 0xCC, 0xCC, 0xFF, 0xFF, 0x11, 0x11, 0x00, 0x00, 0x32}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x0D, {0xC7, 0x10, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xED, 0xC5, 0x00, 0xA5}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x05, {0xC8, 0x10, 0x40, 0x1E, 0x03}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x02, {0xCC, 0x0B}, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_1_PARAM, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x23, {0xE0, 0x00, 0x0A, 0x0F, 0x2A, 0x33, 0x3F, 0x44, 0x39, 0x06, 0x0C, 0x0E, 0x14, 0x15, 0x13, 0x15, 0x10, 0x18, 0x00, 0x0A, 0x0F, 0x2A, 0x33, 0x3F, 0x44, 0x39, 0x06, 0x0C, 0x0E, 0x14, 0x15, 0x13, 0x15, 0x10, 0x18}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x08, {0xE1, 0x11, 0x11, 0x91, 0x00, 0x00, 0x00, 0x00}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x0F, {0xE3, 0x07, 0x07, 0x0B, 0x0B, 0x0B, 0x0B, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x04, 0xC0, 0x10}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x40, {0xE9, 0xC8, 0x10, 0x0A, 0x00, 0x00, 0x80, 0x81, 0x12, 0x31, 0x23, 0x4F, 0x86, 0xA0, 0x00, 0x47, 0x08, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x98, 0x02, 0x8B, 0xAF, 0x46, 0x02, 0x88, 0x88, 0x88, 0x88, 0x88, 0x98, 0x13, 0x8B, 0xAF, 0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x3E, {0xEA, 0x97, 0x0C, 0x09, 0x09, 0x09, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x31, 0x8B, 0xA8, 0x31, 0x75, 0x88, 0x88, 0x88, 0x88, 0x88, 0x9F, 0x20, 0x8B, 0xA8, 0x20, 0x64, 0x88, 0x88, 0x88, 0x88, 0x88, 0x23, 0x00, 0x00, 0x02, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x81, 0x00, 0x00, 0x00, 0x00}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x04, {0xEF, 0xFF, 0xFF, 0x01}, MIPI_DSI_CMD_ID_DCS_LONG_WRITE, MIPI_DSI_CMD_FLAG_LOW_POWER},
    {0x01, {0x11}, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_0_PARAM, MIPI_DSI_CMD_FLAG_LOW_POWER}, // Sleep Out
    {250, {0}, MIPI_DSI_DISPLAY_CONFIG_DATA_DELAY_FLAG, (mipi_dsi_cmd_flag_t)0 },         // DelayX1ms(250) deve ser chamado aqui no código C
    {0x01, {0x29}, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_0_PARAM, MIPI_DSI_CMD_FLAG_LOW_POWER}, // Display On
    {50, {0}, MIPI_DSI_DISPLAY_CONFIG_DATA_DELAY_FLAG, (mipi_dsi_cmd_flag_t)0 },           // DelayX1ms(50) deve ser chamado aqui no código C
    {0x00, {0}, MIPI_DSI_DISPLAY_CONFIG_DATA_END_OF_TABLE, (mipi_dsi_cmd_flag_t)0}
};


static void lcd_init_from_table (const lcd_table_setting_t *table);



/*******************************************************************************************************************//**
 * @brief      Initialize LCD
 *
 * @param[in]  table  LCD Controller Initialization structure.
 * @retval     None.
 **********************************************************************************************************************/
static void lcd_init_from_table (const lcd_table_setting_t *table){
    fsp_err_t err = FSP_SUCCESS;
    const lcd_table_setting_t *p_entry = table;

    while (p_entry->cmd_id != MIPI_DSI_DISPLAY_CONFIG_DATA_END_OF_TABLE){
        mipi_dsi_cmd_t msg = {
             .channel = 0,
             .cmd_id = p_entry->cmd_id,
             .flags = p_entry->flags,
             .tx_len = p_entry->size,
             .p_tx_buffer = p_entry->buffer,
        };

        if (MIPI_DSI_DISPLAY_CONFIG_DATA_DELAY_FLAG == msg.cmd_id)
        {
            printf("DelayMs: %i\r\n", p_entry->size);
            R_BSP_SoftwareDelay (p_entry->size, BSP_DELAY_UNITS_MILLISECONDS);
        }
        else
        {
            g_message_sent = false;
            /* Send a command to the peripheral device */
            err = R_MIPI_DSI_Command (&g_mipi_dsi0_ctrl, &msg);
            if(err != FSP_SUCCESS) {
                printf("%d: ** MIPI DSI Command API failed ** \r\n", (int)err);
            }
            /* Wait */
            while (!g_message_sent);
        }
        p_entry++;
    }
}


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
                g_message_sent = SET_FLAG;
            }
            break;
        }
        case MIPI_DSI_EVENT_PHY:
        {
            g_phy_status |= p_args->phy_status;
            break;
        }
        default:
        {
            break;
        }
    }
}


/*******************************************************************************************************************//**
 * @brief      Start video mode and draw color bands on the LCD screen
 *
 * @param[in]  None.
 * @retval     None.
 **********************************************************************************************************************/
void mipi_dsi_start_display(void){
    fsp_err_t err = FSP_SUCCESS;

    /* Get LCDC configuration */
    g_hz_size = (g_display_cfg.input[0].hsize);
    g_vr_size = (g_display_cfg.input[0].vsize);
    g_hstride = (g_display_cfg.input[0].hstride);

    printf("Width: %i\r\n", g_hz_size);
    printf("Height: %i\r\n", g_vr_size);
    printf("Hstride: %i\r\n", g_hstride);

    /* Initialize buffer pointers */
    g_buffer_size = (uint32_t) (g_hz_size * g_vr_size * BYTES_PER_PIXEL);
    gp_single_buffer = (uint32_t*) g_display_cfg.input[0].p_base;

    /* CORREÇÃO DO PONTEIRO: Avança apenas pixels totais, pois o ponteiro é uint32_t* */
    gp_double_buffer = gp_single_buffer + (g_hz_size * g_vr_size);

    /* Start video mode */
    err = R_GLCDC_Start(&g_display_ctrl);
    if(err != FSP_SUCCESS){
        printf("**%i GLCDC Start API failed ** \r\n", err);
    }

    while (true){
        gp_frame_buffer = (gp_frame_buffer == gp_single_buffer) ? gp_double_buffer : gp_single_buffer;

        /* Display color bands on LCD screen */
        display_draw (gp_frame_buffer);

        /* CORREÇÃO DO RUÍDO: Limpa a cache de dados da CPU para a memória RAM */
//        SCB_CleanDCache_by_Addr((uint32_t *)gp_frame_buffer, (int32_t)g_buffer_size);

        /* Now that the framebuffer is ready, update the GLCDC buffer pointer on the next Vsync */
        err = R_GLCDC_BufferChange (&g_display_ctrl, (uint8_t*) gp_frame_buffer, DISPLAY_FRAME_LAYER_1);
        if(err != FSP_SUCCESS){
            printf("**%i GLCD BufferChange API failed ** \r\n", err);
        }

        /* Wait for a Vsync event */
        g_vsync_flag = RESET_FLAG;
        while (RESET_FLAG == g_vsync_flag);
        break;
    }
}

/*******************************************************************************************************************//**
 * @brief      This function is used initialize related module and start display operation.
 *
 * @param[in]  none
 * @retval     none
 **********************************************************************************************************************/
void mipi_dsi_entry(void)
{
    fsp_err_t          err        = FSP_SUCCESS;

    /* Initialize GLCDC module */
    err = R_GLCDC_Open(&g_display_ctrl, &g_display_cfg);
    /* Handle error */
    if(err != FSP_SUCCESS){
        printf("**%i GLCDC driver initialization FAILED ** \r\n", err);
    }

    err = R_MIPI_DSI_Open(&g_mipi_dsi0_ctrl, &g_mipi_dsi0_cfg);
    if(err != FSP_SUCCESS){
        printf("**%i MIPI DSI driver initialization FAILED ** \r\n", err);
    }

#if 0
    lcd_init_from_table(g_lcd_init_focuslcd);
#endif
    /* Start display 8-color bars */
    mipi_dsi_start_display();
}

/*******************************************************************************************************************//**
 * @brief      User-defined function to draw the current display to a framebuffer.
 *
 * @param[in]  framebuffer    Pointer to frame buffer.
 * @retval     None.
 **********************************************************************************************************************/
static void display_draw (uint32_t * framebuffer){
    /* Draw buffer */
    uint32_t color[COLOR_BAND_COUNT]= {BLUE, LIME, RED, BLACK, WHITE, YELLOW, AQUA, MAGENTA};
    uint16_t bit_width = g_hz_size / COLOR_BAND_COUNT;
    for (uint32_t y = 0; y < g_vr_size; y++)
    {
       for (uint32_t x = 0; x < g_hz_size; x ++)
       {
           uint32_t bit       = x / bit_width;
           framebuffer[x] = color [bit];
       }
       framebuffer += g_hstride;
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
        g_vsync_flag = SET_FLAG;
    }
}

