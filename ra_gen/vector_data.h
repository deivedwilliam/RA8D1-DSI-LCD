/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (15)
#endif
/* ISR prototypes */
void glcdc_line_detect_isr(void);
void mipi_dsi_seq0_isr(void);
void mipi_dsi_seq1_isr(void);
void mipi_dsi_vin1_isr(void);
void mipi_dsi_rcv_isr(void);
void mipi_dsi_ferr_isr(void);
void mipi_dsi_ppi_isr(void);
void iic_master_rxi_isr(void);
void iic_master_txi_isr(void);
void iic_master_tei_isr(void);
void iic_master_eri_isr(void);
void sci_b_uart_rxi_isr(void);
void sci_b_uart_txi_isr(void);
void sci_b_uart_tei_isr(void);
void sci_b_uart_eri_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_GLCDC_LINE_DETECT ((IRQn_Type) 0) /* GLCDC LINE DETECT (Specified line) */
#define GLCDC_LINE_DETECT_IRQn          ((IRQn_Type) 0) /* GLCDC LINE DETECT (Specified line) */
#define VECTOR_NUMBER_MIPIDSI_SEQ0 ((IRQn_Type) 1) /* MIPIDSI SEQ0 (Sequence operation channel 0 interrupt) */
#define MIPIDSI_SEQ0_IRQn          ((IRQn_Type) 1) /* MIPIDSI SEQ0 (Sequence operation channel 0 interrupt) */
#define VECTOR_NUMBER_MIPIDSI_SEQ1 ((IRQn_Type) 2) /* MIPIDSI SEQ1 (Sequence operation channel 1 interrupt) */
#define MIPIDSI_SEQ1_IRQn          ((IRQn_Type) 2) /* MIPIDSI SEQ1 (Sequence operation channel 1 interrupt) */
#define VECTOR_NUMBER_MIPIDSI_VIN1 ((IRQn_Type) 3) /* MIPIDSI VIN1 (Video-Input operation channel1 interrupt) */
#define MIPIDSI_VIN1_IRQn          ((IRQn_Type) 3) /* MIPIDSI VIN1 (Video-Input operation channel1 interrupt) */
#define VECTOR_NUMBER_MIPIDSI_RCV ((IRQn_Type) 4) /* MIPIDSI RCV (DSI packet receive interrupt) */
#define MIPIDSI_RCV_IRQn          ((IRQn_Type) 4) /* MIPIDSI RCV (DSI packet receive interrupt) */
#define VECTOR_NUMBER_MIPIDSI_FERR ((IRQn_Type) 5) /* MIPIDSI FERR (DSI fatal error interrupt) */
#define MIPIDSI_FERR_IRQn          ((IRQn_Type) 5) /* MIPIDSI FERR (DSI fatal error interrupt) */
#define VECTOR_NUMBER_MIPIDSI_PPI ((IRQn_Type) 6) /* MIPIDSI PPI (DSI D-PHY PPI interrupt) */
#define MIPIDSI_PPI_IRQn          ((IRQn_Type) 6) /* MIPIDSI PPI (DSI D-PHY PPI interrupt) */
#define VECTOR_NUMBER_IIC0_RXI ((IRQn_Type) 7) /* IIC0 RXI (Receive data full) */
#define IIC0_RXI_IRQn          ((IRQn_Type) 7) /* IIC0 RXI (Receive data full) */
#define VECTOR_NUMBER_IIC0_TXI ((IRQn_Type) 8) /* IIC0 TXI (Transmit data empty) */
#define IIC0_TXI_IRQn          ((IRQn_Type) 8) /* IIC0 TXI (Transmit data empty) */
#define VECTOR_NUMBER_IIC0_TEI ((IRQn_Type) 9) /* IIC0 TEI (Transmit end) */
#define IIC0_TEI_IRQn          ((IRQn_Type) 9) /* IIC0 TEI (Transmit end) */
#define VECTOR_NUMBER_IIC0_ERI ((IRQn_Type) 10) /* IIC0 ERI (Transfer error) */
#define IIC0_ERI_IRQn          ((IRQn_Type) 10) /* IIC0 ERI (Transfer error) */
#define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 11) /* SCI4 RXI (Receive data full) */
#define SCI4_RXI_IRQn          ((IRQn_Type) 11) /* SCI4 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 12) /* SCI4 TXI (Transmit data empty) */
#define SCI4_TXI_IRQn          ((IRQn_Type) 12) /* SCI4 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 13) /* SCI4 TEI (Transmit end) */
#define SCI4_TEI_IRQn          ((IRQn_Type) 13) /* SCI4 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 14) /* SCI4 ERI (Receive error) */
#define SCI4_ERI_IRQn          ((IRQn_Type) 14) /* SCI4 ERI (Receive error) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (15)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
