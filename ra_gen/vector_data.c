/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = glcdc_line_detect_isr, /* GLCDC LINE DETECT (Specified line) */
            [1] = mipi_dsi_seq0_isr, /* MIPIDSI SEQ0 (Sequence operation channel 0 interrupt) */
            [2] = mipi_dsi_seq1_isr, /* MIPIDSI SEQ1 (Sequence operation channel 1 interrupt) */
            [3] = mipi_dsi_vin1_isr, /* MIPIDSI VIN1 (Video-Input operation channel1 interrupt) */
            [4] = mipi_dsi_rcv_isr, /* MIPIDSI RCV (DSI packet receive interrupt) */
            [5] = mipi_dsi_ferr_isr, /* MIPIDSI FERR (DSI fatal error interrupt) */
            [6] = mipi_dsi_ppi_isr, /* MIPIDSI PPI (DSI D-PHY PPI interrupt) */
            [7] = iic_master_rxi_isr, /* IIC0 RXI (Receive data full) */
            [8] = iic_master_txi_isr, /* IIC0 TXI (Transmit data empty) */
            [9] = iic_master_tei_isr, /* IIC0 TEI (Transmit end) */
            [10] = iic_master_eri_isr, /* IIC0 ERI (Transfer error) */
            [11] = sci_b_uart_rxi_isr, /* SCI4 RXI (Receive data full) */
            [12] = sci_b_uart_txi_isr, /* SCI4 TXI (Transmit data empty) */
            [13] = sci_b_uart_tei_isr, /* SCI4 TEI (Transmit end) */
            [14] = sci_b_uart_eri_isr, /* SCI4 ERI (Receive error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_GLCDC_LINE_DETECT,GROUP0), /* GLCDC LINE DETECT (Specified line) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_MIPIDSI_SEQ0,GROUP1), /* MIPIDSI SEQ0 (Sequence operation channel 0 interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_MIPIDSI_SEQ1,GROUP2), /* MIPIDSI SEQ1 (Sequence operation channel 1 interrupt) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_MIPIDSI_VIN1,GROUP3), /* MIPIDSI VIN1 (Video-Input operation channel1 interrupt) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_MIPIDSI_RCV,GROUP4), /* MIPIDSI RCV (DSI packet receive interrupt) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_MIPIDSI_FERR,GROUP5), /* MIPIDSI FERR (DSI fatal error interrupt) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_MIPIDSI_PPI,GROUP6), /* MIPIDSI PPI (DSI D-PHY PPI interrupt) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_IIC0_RXI,GROUP7), /* IIC0 RXI (Receive data full) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_IIC0_TXI,GROUP0), /* IIC0 TXI (Transmit data empty) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_IIC0_TEI,GROUP1), /* IIC0 TEI (Transmit end) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_IIC0_ERI,GROUP2), /* IIC0 ERI (Transfer error) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_SCI4_RXI,GROUP3), /* SCI4 RXI (Receive data full) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_SCI4_TXI,GROUP4), /* SCI4 TXI (Transmit data empty) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_SCI4_TEI,GROUP5), /* SCI4 TEI (Transmit end) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_SCI4_ERI,GROUP6), /* SCI4 ERI (Receive error) */
        };
        #endif
        #endif
