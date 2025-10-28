#include "hal_data.h"
#include "hal_entry.h"
#include "uart_ep.h"
#include "stdio.h"
#include "common_utils.h"
#include "i2c_controller.h"


void R_HDMI_BridgeInit(void);
void TxAnalog(void);
void DigitalClockEn(void);
void HDMIPllAnalog(void);
void MIPIAnalog(void);
void MipiBasicSet(void);
void MIPIDig480P(void);
void MIPIDig720P(void);
void MIPIDig1080P(void);
void MIPIRxLogicRes(void);
void DDSConfig(void);
void AudioIIsEn(void);
void CbusAnalog(void);
void DigitalClockEn(void){
    I2C_WriteByte(0x48, 0x08, 0xff);
    I2C_WriteByte(0x48, 0x09, 0xff);
    I2C_WriteByte(0x48, 0x0a, 0xff);
    I2C_WriteByte(0x48, 0x0b, 0x7c);
    I2C_WriteByte(0x48, 0x0c, 0xff);
}

void TxAnalog(void){
    I2C_WriteByte(0x48, 0x31, 0xb1);
    I2C_WriteByte(0x48, 0x32, 0xb1);
    I2C_WriteByte(0x48, 0x33, 0x0e);
    I2C_WriteByte(0x48, 0x37, 0x00);
    I2C_WriteByte(0x48, 0x38, 0x22);
    I2C_WriteByte(0x48, 0x60, 0x82);
}

void HDMIPllAnalog(void){
    I2C_WriteByte(0x48, 0x44, 0x31);
    I2C_WriteByte(0x48, 0x55, 0x44);
    I2C_WriteByte(0x48, 0x57, 0x01);
    I2C_WriteByte(0x48, 0x5a, 0x02);
}

void MIPIAnalog(void){
    I2C_WriteByte(0x48, 0x3e, 0xd6);
    I2C_WriteByte(0x48, 0x3f, 0xd4);
    I2C_WriteByte(0x48, 0x41, 0x3c);
}

void MipiBasicSet(void){
    I2C_WriteByte(0x49, 0x10, 0x04);
    I2C_WriteByte(0x49, 0x11, 0x10);
    I2C_WriteByte(0x49, 0x12, 0x04);
    I2C_WriteByte(0x49, 0x13, 0x00);
    I2C_WriteByte(0x49, 0x14, 0x00);
    I2C_WriteByte(0x49, 0x15, 0x00);
    I2C_WriteByte(0x49, 0x1a, 0x03);
    I2C_WriteByte(0x49, 0x1b, 0x03);
}
void MIPIDig480P(void){
    I2C_WriteByte(0x49, 0x18, 0x3e);
    I2C_WriteByte(0x49, 0x19, 0x06);
    I2C_WriteByte(0x49, 0x1c, 0xd0);
    I2C_WriteByte(0x49, 0x1d, 0x02);
    I2C_WriteByte(0x49, 0x2f, 0x0c);
    I2C_WriteByte(0x49, 0x34, 0x5a);
    I2C_WriteByte(0x49, 0x35, 0x03);
    I2C_WriteByte(0x49, 0x36, 0x0d);
    I2C_WriteByte(0x49, 0x37, 0x02);
    I2C_WriteByte(0x49, 0x38, 0x1e);
    I2C_WriteByte(0x49, 0x39, 0x00);
    I2C_WriteByte(0x49, 0x3a, 0x09);
    I2C_WriteByte(0x49, 0x3b, 0x00);
    I2C_WriteByte(0x49, 0x3c, 0x3c);
    I2C_WriteByte(0x49, 0x3d, 0x00);
    I2C_WriteByte(0x49, 0x3e, 0x10);
    I2C_WriteByte(0x49, 0x3f, 0x00);
}
void MIPIDig720P(void){
    I2C_WriteByte(0x49, 0x18, 0x28);
    I2C_WriteByte(0x49, 0x19, 0x05);
    I2C_WriteByte(0x49, 0x1c, 0x00);
    I2C_WriteByte(0x49, 0x1d, 0x05);
    I2C_WriteByte(0x49, 0x2f, 0x0c);
    I2C_WriteByte(0x49, 0x34, 0x72);
    I2C_WriteByte(0x49, 0x35, 0x06);
    I2C_WriteByte(0x49, 0x36, 0xee);
    I2C_WriteByte(0x49, 0x37, 0x02);
    I2C_WriteByte(0x49, 0x38, 0x14);
    I2C_WriteByte(0x49, 0x39, 0x00);
    I2C_WriteByte(0x49, 0x3a, 0x05);
    I2C_WriteByte(0x49, 0x3b, 0x00);
    I2C_WriteByte(0x49, 0x3c, 0xdc);
    I2C_WriteByte(0x49, 0x3d, 0x00);
    I2C_WriteByte(0x49, 0x3e, 0x6e);
    I2C_WriteByte(0x49, 0x3f, 0x00);
}

void MIPIDig1080P(void){
    I2C_WriteByte(0x49, 0x18, 0x2c);
    I2C_WriteByte(0x49, 0x19, 0x05);
    I2C_WriteByte(0x49, 0x1c, 0x80);
    I2C_WriteByte(0x49, 0x1d, 0x07);
    I2C_WriteByte(0x49, 0x2f, 0x0c);
    I2C_WriteByte(0x49, 0x34, 0x98);
    I2C_WriteByte(0x49, 0x35, 0x08);
    I2C_WriteByte(0x49, 0x36, 0x65);
    I2C_WriteByte(0x49, 0x37, 0x04);
    I2C_WriteByte(0x49, 0x38, 0x24);
    I2C_WriteByte(0x49, 0x39, 0x00);
    I2C_WriteByte(0x49, 0x3a, 0x04);
    I2C_WriteByte(0x49, 0x3b, 0x00);
    I2C_WriteByte(0x49, 0x3c, 0x94);
    I2C_WriteByte(0x49, 0x3d, 0x00);
    I2C_WriteByte(0x49, 0x3e, 0x58);
    I2C_WriteByte(0x49, 0x3f, 0x00);
}

void MIPIRxLogicRes(void){
    I2C_WriteByte(0x48, 0x03, 0x7f);
    R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);
    I2C_WriteByte(0x48, 0x03, 0xff);
}

void DDSConfig(void){
    I2C_WriteByte(0x49,0x4e,0xdb);
    I2C_WriteByte(0x49,0x4f,0x97);
    I2C_WriteByte(0x49,0x50,0x69);

    I2C_WriteByte(0x49,0x51,0x80);
    I2C_WriteByte(0x49,0x1f,0x5e);
    I2C_WriteByte(0x49,0x20,0x01);
    I2C_WriteByte(0x49,0x21,0x2c);
    I2C_WriteByte(0x49,0x22,0x01);
    I2C_WriteByte(0x49,0x23,0xfa);
    I2C_WriteByte(0x49,0x24,0x00);
    I2C_WriteByte(0x49,0x25,0xc8);
    I2C_WriteByte(0x49,0x26,0x00);
    I2C_WriteByte(0x49,0x27,0x5e);
    I2C_WriteByte(0x49,0x28,0x01);
    I2C_WriteByte(0x49,0x29,0x2c);
    I2C_WriteByte(0x49,0x2a,0x01);
    I2C_WriteByte(0x49,0x2b,0xfa);
    I2C_WriteByte(0x49,0x2c,0x00);
    I2C_WriteByte(0x49,0x2d,0xc8);
    I2C_WriteByte(0x49,0x2e,0x00);
    I2C_WriteByte(0x49,0x42,0x64);
    I2C_WriteByte(0x49,0x43,0x00);
    I2C_WriteByte(0x49,0x44,0x04);
    I2C_WriteByte(0x49,0x45,0x00);
    I2C_WriteByte(0x49,0x46,0x59);
    I2C_WriteByte(0x49,0x47,0x00);
    I2C_WriteByte(0x49,0x48,0xf2);
    I2C_WriteByte(0x49,0x49,0x06);
    I2C_WriteByte(0x49,0x4a,0x00);
    I2C_WriteByte(0x49,0x4b,0x72);
    I2C_WriteByte(0x49,0x4c,0x45);
    I2C_WriteByte(0x49,0x4d,0x00);
    I2C_WriteByte(0x49,0x52,0x08);
    I2C_WriteByte(0x49,0x53,0x00);
    I2C_WriteByte(0x49,0x54,0xb2);
    I2C_WriteByte(0x49,0x55,0x00);
    I2C_WriteByte(0x49,0x56,0xe4);
    I2C_WriteByte(0x49,0x57,0x0d);
    I2C_WriteByte(0x49,0x58,0x00);
    I2C_WriteByte(0x49,0x59,0xe4);
    I2C_WriteByte(0x49,0x5a,0x8a);
    I2C_WriteByte(0x49,0x5b,0x00);
    I2C_WriteByte(0x49,0x5c,0x34);
    I2C_WriteByte(0x49,0x1e,0x4f);
    I2C_WriteByte(0x49,0x51,0x00);
}

void AudioIIsEn(void){
//    I2CADR = 0x90;
    I2C_WriteByte(0x48, 0xB2, 0x01);
//    I2CADR = 0x94;
    I2C_WriteByte(0x4A, 0x06, 0x08);
    I2C_WriteByte(0x4A, 0x07, 0xF0);
    I2C_WriteByte(0x4A, 0x0f, 0x28); //Audio 16bit, 48K
    I2C_WriteByte(0x4A, 0x34, 0xe2);
}

void PowerOFF(void) {

}

void LT8912_Sleep_HDMI(void){

}

void CbusAnalog(void)
{
//    I2CADR = 0x90;
    I2C_WriteByte(0x48, 0x39, 0x45);
    I2C_WriteByte(0x48, 0x3a, 0x00);
    I2C_WriteByte(0x48, 0x3b, 0x00);
}

void R_HDMI_BridgeInit(void){
    uint8_t aux = 0;
    uint16_t deviceId = 0;
    fsp_err_t err = FSP_SUCCESS;
    uint8_t reg_address = 0x00;


    I2C_ReadByte(0x48, 0x00, &aux);

    deviceId = aux;

    I2C_ReadByte(0x48, 0x01, &aux);

    deviceId |= (((uint16_t)aux) << 8);

    printf("Device ID: 0x%04X\r\n", deviceId);

//    DigitalClockEn();
//    TxAnalog();
//    CbusAnalog();
//    HDMIPllAnalog();
//    MIPIAnalog();
//    MipiBasicSet();
//    MIPIDig720P();//MIPIDig720P();  MIPIDig1080P();  MIPIDig480P();
//    DDSConfig();
//    AudioIIsEn();
//    MIPIRxLogicRes();
}



int  __weak _write(int file, char *ptr, int len){
   (void)file;

   uart_print_user_msg((uint8_t *)ptr);

   return len;
}




/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */

    fsp_err_t err = FSP_SUCCESS;

    uart_initialize();
    R_IIC_MASTER_Open(&g_i2c_master0_ctrl, &g_i2c_master0_cfg);


#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
    R_BSP_PinAccessEnable();
    R_BSP_PinWrite(RESET_N, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(50, BSP_DELAY_UNITS_MILLISECONDS);
    R_BSP_PinWrite(RESET_N, BSP_IO_LEVEL_HIGH);

    R_HDMI_BridgeInit();

//    R_MIPI_DSI_Open(&g_mipi_dsi0_ctrl, &g_mipi_dsi0_cfg);
//    R_MIPI_DSI_Command(&g_mipi_dsi0_ctrl, p_cmd)

   for(;;){

       printf("Deus é o Rei\r\n");
       R_BSP_PinWrite(BACKLIGHT, BSP_IO_LEVEL_LOW);
       R_BSP_SoftwareDelay(200, BSP_DELAY_UNITS_MILLISECONDS);
       R_BSP_PinWrite(BACKLIGHT, BSP_IO_LEVEL_HIGH);
       R_BSP_SoftwareDelay(200, BSP_DELAY_UNITS_MILLISECONDS);

   }
}



#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
