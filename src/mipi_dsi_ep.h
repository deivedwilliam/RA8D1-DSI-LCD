/*
 * mipi_dsi_ep.h
 *
 *  Created on: 27 de out. de 2025
 *      Author: Deived
 */

#ifndef MIPI_DSI_EP_H_
#define MIPI_DSI_EP_H_

#include "r_mipi_dsi_api.h"
#include "r_mipi_cmd_types.h"

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



#endif /* MIPI_DSI_EP_H_ */
