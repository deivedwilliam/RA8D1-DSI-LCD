/*
 * mipi_dsi_ep.h
 *
 *  Created on: 27 de out. de 2025
 *      Author: Deived
 */

#ifndef MIPI_DSI_EP_H_
#define MIPI_DSI_EP_H_

#include "r_mipi_dsi_api.h"

#define MIPI_DSI_DISPLAY_CONFIG_DATA_DELAY_FLAG      ((mipi_dsi_cmd_id_t) 0xFE)
#define MIPI_DSI_DISPLAY_CONFIG_DATA_END_OF_TABLE    ((mipi_dsi_cmd_id_t) 0xFD)
#define BYTES_PER_PIXEL                              (4)
#define COLOR_BAND_COUNT                             (8)
#define BLUE                                         (0x000000FF)
#define LIME                                         (0xFF00FF00)
#define RED                                          (0x00FF0000)
#define BLACK                                        (0x00000000)
#define WHITE                                        (0xFFFFFFFF)
#define YELLOW                                       (0xFFFFFF00)
#define AQUA                                         (0xFF00FFFF)
#define MAGENTA                                      (0x00FF00FF)
#define RESET_FLAG                                   (false)
#define SET_FLAG                                     (true)


#define CIRCLE_VAL_X            (360)
#define CIRCLE_VAL_Y            (165)
#define CIRCLE_VAL_R            (45)
#define CIRCLE_VAL_W            (0)
#define TRIANGLE_X1             (285)
#define TRIANGLE_Y1             (560)
#define TRIANGLE_X2             (390)
#define TRIANGLE_Y2             (660)
#define TRIANGLE_X3             (285)
#define TRIANGLE_Y3             (760)
#define BOX_VAL_X1              (65)
#define BOX_VAL_Y1              (80)
#define BOX_VAL_LEN             (135)
#define BOX_VAL_WIDTH           (200)
#define BOX_PARAM               (270)
#define LINE_VAL_X1             (175)
#define LINE_VAL_Y1             (760)
#define LINE_VAL_X2             (65)
#define LINE_VAL_Y2             (580)
#define LINE_VAL_WIDTH          (6)


#define ALPHA_VALUE             (155U)
#define ANTI_ALIASING_VAL       (1U)
#define BUFFER_CLEAR_VAL        (0x000000)
#define RED_COLOR_VAL           (0xFF0000)
#define GREEN_COLOR_VAL         (0x00FF00)
#define BLUE_COLOR_VAL          (0x0000FF)
#define YELLOW_COLOR_VAL        (0xFFFF00)
#define SHIFT_VALUE             (4U)

#define DRW_TEST_IMAGE_RES_H    (720)
#define DRW_TEST_IMAGE_RES_V    (720)

#define ARRAY_INDEX             (0U)
#define BITFIELD_VALUE          (0U)


typedef struct
{
    unsigned char        size;
    unsigned char        buffer[64];
    mipi_dsi_cmd_id_t    cmd_id;
    mipi_dsi_cmd_flag_t flags;
} lcd_table_setting_t;

extern const lcd_table_setting_t g_lcd_init_focuslcd[];
void mipi_dsi_push_table (const lcd_table_setting_t *table);
void mipi_dsi_start_display ();
void mipi_dsi_entry(void);

void DRW_entry(void);

#endif /* MIPI_DSI_EP_H_ */
