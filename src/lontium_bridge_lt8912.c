/*
 * lontium_bridge_lt8912.c
 *
 *  Created on: 6 de nov. de 2025
 *      Author: Deived
 */

#include "lontium_bridge_lt8912.h"
#include "i2c_controller.h"
#include "hdmi_config.h"
#include "stdbool.h"
#include "stdio.h"

#define LOG_FLAG "[LT8912]"

bool suspend_on = 0;
// hfp, hs, hbp, hact, htotal, vfp, vs, vbp, vact, vtotal, hfp, hs, hbp, hact, htotal, vfp, vs, vbp, vact, vtotal, h_polary, v_polary, vic, aspact_ratio, pclk_khz
struct video_timing video_640x480_60Hz =
{ 16, 96, 48, 640, 800, 10, 2, 33, 480, 525, 0, 0, 1, AR_4_3, 25000 };
struct video_timing video_720x480_60Hz =
{ 16, 62, 60, 720, 858, 9, 6, 30, 480, 525, 0, 0, 2, AR_4_3, 27000 };
struct video_timing video_720x576_50Hz =
{ 12, 64, 68, 720, 864, 5, 5, 39, 576, 625, 0, 0, 17, AR_4_3, 27000 };
struct video_timing video_800x600_60Hz =
{ 48, 128, 88, 800, 1056, 1, 4, 23, 600, 628, 1, 1, 0, AR_16_9, 40000 };
struct video_timing video_1024x768_60Hz =
{ 24, 136, 160, 1024, 1344, 3, 6, 29, 768, 806, 0, 0, 0, AR_16_9, 65000 };
struct video_timing video_1280x720_60Hz =
{ 110, 40, 220, 1280, 1650, 5, 5, 20, 720, 750, 1, 1, 4, AR_16_9, 37125 };
struct video_timing video_1280x800_60Hz =
{ 28, 32, 100, 1280, 1440, 2, 6, 15, 800, 823, 0, 0, 0, AR_16_9, 71000 };
struct video_timing video_1920x1080_60Hz =
{ 88, 44, 148, 1920, 2200, 4, 5, 36, 1080, 1125, 1, 1, 16, AR_16_9, 148500 };


struct video_timing timing_480x854_60 =
{
/* Horizontal */
.hfp = 72,
  .hs = 2, .hbp = 5, .hact = 480, .htotal = 559,

  /* Vertical */
  .vfp = 17,
  .vs = 8, .vbp = 6, .vact = 854, .vtotal = 894,

  /* Polarity */
  .h_polarity = 0,   // HSYNC positive
  .v_polarity = 0,   // VSYNC positive

  /* Info */
  .vic = 0, // não CEA
  .aspact_ratio = 0, // sem info
  .pclk_khz = 30000 };

struct video_timing timing_800x600_30 =
{ .hfp = 128,  // Calculado acima (1056 - 800 - 88 - 40)
  .hs = 40,   // Reduzido para evitar warning no FSP
  .hbp = 48,   // Valor REAL (88 do FSP - 40 do Sync)
  .hact = 800,
  .htotal = 1056, // Volta ao padrão VESA (60Hz)

  // Vertical
  .vfp = 1,
  .vs = 4,
  .vbp = 19,   // Valor REAL (23 do FSP - 4 do Sync)
  .vact = 600,
  .vtotal = 628,

  // Infos
  .h_polarity = 1,
  .v_polarity = 1,
  .vic = 0,
  .aspact_ratio = AR_4_3,
  .pclk_khz = 40000 // 40 MHz (Importante o Divisor do GLCDC bater com isso)
        };

struct video_timing *video;

uint8_t Tx_HPD = 0;

void MIPIDig480P(void);
void LT8912_Sleep_exit_HDMI(void);
void LT8912_DDS_Update(struct video_timing *video_format);

void DigitalClockEn(void)
{
    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

    I2C_WriteByte (device_address, 0x08, 0xff);
    I2C_WriteByte (device_address, 0x09, 0xff);
    I2C_WriteByte (device_address, 0x0a, 0xff);
    I2C_WriteByte (device_address, 0x0b, 0x7c);
    I2C_WriteByte (device_address, 0x0c, 0xff);
//    I2C_WriteByte(device_address, 0x02, 0xf7);
//    I2C_WriteByte(device_address, 0x42, 0x04);
}

void TxAnalog(void)
{
    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

//    I2C_WriteByte(device_address, 0x31, 0xE1);
//    I2C_WriteByte(device_address, 0x32, 0xE1);
//    I2C_WriteByte(device_address, 0x33, 0x0c); // en/disable HDMI output
//    I2C_WriteByte(device_address, 0x37, 0x00);
//    I2C_WriteByte(device_address, 0x38, 0x22);
//    I2C_WriteByte(device_address, 0x60, 0x82);

    I2C_WriteByte (device_address, 0x31, 0xB1);
    I2C_WriteByte (device_address, 0x32, 0xB1);
    I2C_WriteByte (device_address, 0x33, 0x0E); // en/disable HDMI output
    I2C_WriteByte (device_address, 0x37, 0x00);
    I2C_WriteByte (device_address, 0x38, 0x22);
    I2C_WriteByte (device_address, 0x60, 0x82);
}

void CbusAnalog(void)
{
    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

    I2C_WriteByte (device_address, 0x39, 0x45);
    I2C_WriteByte (device_address, 0x3a, 0x00); // 20180719
    I2C_WriteByte (device_address, 0x3b, 0x00);
}

void HDMIPllAnalog(void)
{
    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

    I2C_WriteByte (device_address, 0x44, 0x31);
    I2C_WriteByte (device_address, 0x55, 0x44);
    I2C_WriteByte (device_address, 0x57, 0x01);
    I2C_WriteByte (device_address, 0x5a, 0x02);
}

void AviInfoframe(struct video_timing *video_format)
{
    // Mapeamento básico para segurança
        // 1 = 4:3, 2 = 16:9 (Certifique-se que sua struct usa esses valores do enum)
        uint8_t VIC = video_format->vic;
        uint8_t AR_Code = video_format->aspact_ratio;

        uint8_t pb1, pb2, pb4, Sync_Polarity;
        uint8_t checksum;
        uint8_t device_address;

        // --- Configuração dos Bytes do Payload ---

        // PB1: 0x10 = RGB, No Scaling, Active Format Valid.
        // Se quiser mudar para YCbCr 4:2:2 no futuro, mudaria aqui para 0x30, etc.
        pb1 = 0x10;

        // PB2: Aspect Ratio
        // Bits [5:4] = Picture Aspect Ratio (M1,M0)
        // Bit 3 (0x08) = Active Format Ratio same as Picture (R3)
        pb2 = (uint8_t)((AR_Code << 4) | 0x08);

        // PB4: VIC Code
        pb4 = VIC;

        // --- Cálculo Real do Checksum ---
        // Header do AVI InfoFrame (Type 0x82 + Ver 0x02 + Len 0x0D) soma sempre 0x91.
        // Checksum = 0x100 - (HeaderSum + PB1 + PB2 + PB3 + PB4 + ...)
        // PB3 é sempre 0x00 no seu caso.

        uint16_t sum = 0x91 + pb1 + pb2 + 0x00 + pb4;
        checksum = (uint8_t)(0x100 - (sum & 0xFF));

        // --- Escrita nos Registradores ---

        // Endereço 0x94 -> 0x4A (7-bit)
        device_address = 0x4A;
        I2C_WriteByte(device_address, 0x3c, 0x41); // AVI InfoFrame Enable (Packet Type control)

        // Configura Polaridade (Banco 0x48)
        device_address = 0x48;
        Sync_Polarity = (uint8_t)((video_format->h_polarity << 1) | video_format->v_polarity);
        I2C_WriteByte(device_address, 0xab, Sync_Polarity);

        // Escreve o Payload (Banco 0x4A)
        device_address = 0x4A;
        I2C_WriteByte(device_address, 0x43, checksum); // PB0
        I2C_WriteByte(device_address, 0x44, pb1);      // PB1
        I2C_WriteByte(device_address, 0x45, pb2);      // PB2
        I2C_WriteByte(device_address, 0x46, 0x00);     // PB3
        I2C_WriteByte(device_address, 0x47, pb4);      // PB4
}

void MipiAnalog(void)
{
    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

#ifdef _pn_swap_
    I2C_WriteByte(device_address, 0x3e, 0xf6); // P/N swap
#else
    I2C_WriteByte (device_address, 0x3e, 0xd6); // if MIPI pin map follows reference design, no swap needed
#endif
    I2C_WriteByte (device_address, 0x3f, 0xd4);
    I2C_WriteByte (device_address, 0x41, 0x3c); // EQ
//    I2C_WriteByte(device_address, 0xB2, 0x00); // EQ
////    I2C_WriteByte(device_address, 0x3f, 0xd4); // EQ
}

void MipiBasicSet(void)
{
    // Endereço 0x92 -> 0x49 (7-bit)
    uint8_t device_address = 0x49;

    I2C_WriteByte (device_address, 0x10, 0x04);    // term en
    I2C_WriteByte (device_address, 0x11, 0x10);    // settle
    I2C_WriteByte (device_address, 0x12, 0x04); // trail
    I2C_WriteByte (device_address, 0x13, lane_cnt); // 00 4 lane // 01 1 lane // 02 2 lane // 03 3lane
    I2C_WriteByte (device_address, 0x14, 0x00);     // debug mux

#ifdef _lane_swap_  // for EVB only; if MIPI pin map follows reference design, no need swap lane.
    I2C_WriteByte(device_address, 0x15, 0xa8);     // lane swap: 3210
    printf("%s nmipi basic set: lane swap 3210, %d\n", LOG_FLAG, lane_cnt);
#else
    I2C_WriteByte (device_address, 0x15, 0x00);     // lane swap: 0123
#endif

    I2C_WriteByte (device_address, 0x1a, 0x03);     // hshift 3
    I2C_WriteByte (device_address, 0x1b, 0x03);     // vshift 3
}

void MIPI_Video_Setup(struct video_timing *video_format)
{
    // Endereço 0x92 -> 0x49 (7-bit)
    uint8_t device_address = 0x49;

    I2C_WriteByte (device_address, 0x18, (uint8_t) (video_format->hs & 0xFF));   // H width
    I2C_WriteByte (device_address, 0x19, (uint8_t) (video_format->vs & 0xFF));   // V width
    I2C_WriteByte (device_address, 0x1C, (uint8_t) (video_format->hact & 0xFF)); // H active [7:0]
    I2C_WriteByte (device_address, 0x1D, (uint8_t) (video_format->hact >> 8));   // H active [15:8]
    I2C_WriteByte (device_address, 0x2F, 0x0C);                                 // FIFO buffer length = 12
    I2C_WriteByte (device_address, 0x34, (uint8_t) (video_format->htotal & 0xFF)); // H total [7:0]
    I2C_WriteByte (device_address, 0x35, (uint8_t) (video_format->htotal >> 8));   // H total [15:8]
    I2C_WriteByte (device_address, 0x36, (uint8_t) (video_format->vtotal & 0xFF)); // V total [7:0]
    I2C_WriteByte (device_address, 0x37, (uint8_t) (video_format->vtotal >> 8));   // V total [15:8]
    I2C_WriteByte (device_address, 0x38, (uint8_t) (video_format->vbp & 0xFF));    // VBP [7:0]
    I2C_WriteByte (device_address, 0x39, (uint8_t) (video_format->vbp >> 8));      // VBP [15:8]
    I2C_WriteByte (device_address, 0x3A, (uint8_t) (video_format->vfp & 0xFF));    // VFP [7:0]
    I2C_WriteByte (device_address, 0x3B, (uint8_t) (video_format->vfp >> 8));      // VFP [15:8]
    I2C_WriteByte (device_address, 0x3C, (uint8_t) (video_format->hbp & 0xFF));    // HBP [7:0]
    I2C_WriteByte (device_address, 0x3D, (uint8_t) (video_format->hbp >> 8));      // HBP [15:8]
    I2C_WriteByte (device_address, 0x3E, (uint8_t) (video_format->hfp & 0xFF));    // HFP [7:0]
    I2C_WriteByte (device_address, 0x3F, (uint8_t) (video_format->hfp >> 8));      // HFP [15:8]
}

void MIPIRxLogicRes(void)
{
    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

    I2C_WriteByte (device_address, 0x03, 0x7F); // MIPI RX reset
    R_BSP_SoftwareDelay (10, BSP_DELAY_UNITS_MILLISECONDS);
    I2C_WriteByte (device_address, 0x03, 0xFF);

    I2C_WriteByte (device_address, 0x05, 0xFB); // DDS reset
    R_BSP_SoftwareDelay (10, BSP_DELAY_UNITS_MILLISECONDS);
    I2C_WriteByte (device_address, 0x05, 0xFF);
}

void LT8912_DDS_Update(struct video_timing *video_format)
{
    uint8_t device_address = 0x49; // Endereço do MIPI/DDS
    uint32_t dds_val;
    uint8_t pclk_mhz;

    // 1. Calcula o valor do DDS baseado no clock do vídeo
    // Sua struct usa kHz, então dividimos por 1000
    pclk_mhz = (uint8_t) (video_format->pclk_khz / 1000);

    // Constante 0x16C16 (93206) derivada dos drivers da Lontium
    dds_val = pclk_mhz * 0x16C16;

    printf ("[LT8912] Configurando DDS para %d MHz. Val: 0x%06X\r\n", pclk_mhz, dds_val);

    // 2. Escreve os registradores de Frequência
    I2C_WriteByte (device_address, 0x4E, (uint8_t) (dds_val & 0xFF));        // LSB
    I2C_WriteByte (device_address, 0x4F, (uint8_t) ((dds_val >> 8) & 0xFF)); // MID
    I2C_WriteByte (device_address, 0x50, (uint8_t) ((dds_val >> 16) & 0xFF)); // MSB

    // 3. Configura o MUX de Entrada (CRÍTICO!)
    // Bit 6 = 0 -> MIPI Input
    // Bit 6 = 1 -> Pattern Generator
    I2C_WriteByte (device_address, 0x1E, 0x0F);

    // 4. Habilita o DDS
    I2C_WriteByte (device_address, 0x51, 0x80);

    // NOTA SOBRE OS OUTROS REGISTRADORES (FIFO):
    // Os registradores de 0x1F a 0x2E controlam thresholds do FIFO.
    // Em clocks baixos (40MHz), os valores padrão geralmente funcionam.
    // Se a imagem piscar, precisaremos ajustar 0x1F-0x2E proporcionalmente,
    // mas com o clock certo (passo 2) e o mux certo (passo 3), deve dar vídeo.
}

void AudioIIsEn(void)
{
    // Endereços 0x90 -> 0x48 (7-bit) e 0x94 -> 0x4A (7-bit)
    uint8_t device_address_1 = 0x48;
    uint8_t device_address_2 = 0x4A;

    printf ("Configurando áudio I2S...\r\n");

    // Configurações de modo HDMI/DVI
    I2C_WriteByte (device_address_1, 0xB2, 0x01); // DVI mode:0x00; HDMI mode:0x01;

    // Configuração de parâmetros de áudio
    I2C_WriteByte (device_address_2, 0x06, 0x08);
    I2C_WriteByte (device_address_2, 0x07, 0xF0);
    I2C_WriteByte (device_address_2, 0x34, 0xD2); // 0xE2:32FS; 0xD2:64FS
    I2C_WriteByte (device_address_2, 0x0F, 0x2B);

    printf ("Áudio I2S habilitado.\r\n");
}

void AudioSpdifEn(void)
{
    // Endereços 0x90 -> 0x48 (7-bit) e 0x94 -> 0x4A (7-bit)
    uint8_t device_address_1 = 0x48;
    uint8_t device_address_2 = 0x4A;

    printf ("Configurando saída SPDIF...\r\n");

    // Configuração do modo HDMI/DVI
    I2C_WriteByte (device_address_1, 0xB2, 0x01);

    // Configuração dos registradores SPDIF
    I2C_WriteByte (device_address_2, 0x06, 0x0E);
    I2C_WriteByte (device_address_2, 0x07, 0x00);
    I2C_WriteByte (device_address_2, 0x34, 0xD2); // 0xE2:32FS; 0xD2:64FS

    printf ("Saída SPDIF habilitada.\r\n");
}

void Core_Pll_setup(struct panel_parameter *panel)
{
    uint8_t cpll_m, cpll_k1, cpll_k2;
    uint32_t temp;

    printf ("Configurando Core PLL...\r\n");

    // Cálculo dos parâmetros do PLL baseado no clock do painel
    temp = (30000 * 7) / 25;
    cpll_m = (uint8_t) (temp / 1000);

    temp = (30000 * 7) / 25;
    temp = temp % 1000;
    temp = temp * 16384 / 1000;

    cpll_k1 = temp % 256;
    cpll_k2 = temp / 256;

    // Endereço 0x90 -> 0x48 (7-bit)
    uint8_t device_address = 0x48;

    // Configuração dos registradores do Core PLL
    I2C_WriteByte (device_address, 0x50, 0x24);               // cp = 50µA
    I2C_WriteByte (device_address, 0x51, 0x05);               // xtal_clk como ref, filtro passivo 2ª ordem
    I2C_WriteByte (device_address, 0x52, 0x14);               // usa PLL de 2ª ordem
    I2C_WriteByte (device_address, 0x69, cpll_m);             // CP_PRESET_DIV_RATIO
    I2C_WriteByte (device_address, 0x69, cpll_m | 0x80);
    I2C_WriteByte (device_address, 0x6C, cpll_k2 | 0x80);     // RGD_CP_SOFT_K_EN, RGD_CP_SOFT_K[13:8]
    I2C_WriteByte (device_address, 0x6B, cpll_k1);

    // Reset do Core PLL
    I2C_WriteByte (device_address, 0x04, 0xFB);
    I2C_WriteByte (device_address, 0x04, 0xFF);

    printf ("Core PLL configurado: M=%u, K1=%u, K2=%u\r\n", cpll_m, cpll_k1, cpll_k2);
}

void Core_Pll_bypass(void)
{
    printf ("Configurando Core PLL em modo BYPASS...\r\n");

    // Endereço 8-bit original = 0x90 → 7-bit = 0x48
    uint8_t device_address = 0x48;

    // Configuração do PLL para modo de bypass
    I2C_WriteByte (device_address, 0x50, 0x24);   // CP = 50µA
    I2C_WriteByte (device_address, 0x51, 0x2D);   // Pixel clock como referência, 2ª ordem passiva
    I2C_WriteByte (device_address, 0x52, 0x04);   // loopdiv=0, usa PLL de 2ª ordem
    I2C_WriteByte (device_address, 0x69, 0x0E);   // CP_PRESET_DIV_RATIO
    I2C_WriteByte (device_address, 0x69, 0x8E);   // Habilita bit 7 (PLL write)
    I2C_WriteByte (device_address, 0x6A, 0x00);   // K[7:0]
    I2C_WriteByte (device_address, 0x6C, 0xB8);   // RGD_CP_SOFT_K_EN + RGD_CP_SOFT_K[13:8]
    I2C_WriteByte (device_address, 0x6B, 0x51);   // K[7:0]

    // Reset do Core PLL
    I2C_WriteByte (device_address, 0x04, 0xFB);
    I2C_WriteByte (device_address, 0x04, 0xFF);

    printf ("Core PLL configurado em modo BYPASS.\r\n");
}

void Lvds_Pll_Reset(void)
{
    printf ("Reinicializando LVDS PLL...\r\n");

    // Endereço original 8-bit = 0x90 → 7-bit = 0x48
    uint8_t device_address = 0x48;

    // Sequência de reset do PLL LVDS
    I2C_WriteByte (device_address, 0x02, 0xF7);  // Ativa reset do LVDS PLL
    I2C_WriteByte (device_address, 0x02, 0xFF);  // Libera reset

    printf ("LVDS PLL reset concluído.\r\n");
}

void Scaler_bypass(void)
{
    printf ("Desativando o scaler (modo bypass)...\r\n");

    // Endereço original 8-bit = 0x90 → 7-bit = 0x48
    uint8_t device_address = 0x48;

    // Configuração para desativar o scaler
    I2C_WriteByte (device_address, 0x7F, 0x00); // Desativa o scaler
    I2C_WriteByte (device_address, 0xA8, 0x13); // Configuração auxiliar (modo bypass)

    printf ("Scaler desativado (modo bypass ativo).\r\n");
}

void Scaler_setup(struct video_timing *input_video, struct panel_parameter *panel)
{
    uint32_t h_ratio, v_ratio;
    uint32_t htotal;
    uint8_t i;

    if (input_video == NULL || panel == NULL)
    {
        printf ("Scaler_setup: ponteiro nulo\r\n");
        return;
    }

    /* Cálculo das proporções (fixed point 12.4): */
    h_ratio = (input_video->hact * 4096) / panel->hact;
    v_ratio = (input_video->vact * 4096) / panel->vact;

    /* Endereço 8-bit original 0x90 -> 7-bit = 0x48 */
    uint8_t device_address = 0x48;

    printf ("Configurando Scaler... h_ratio=%lu v_ratio=%lu\r\n", h_ratio, v_ratio);

    I2C_WriteByte (device_address, 0x80, 0x00);
    I2C_WriteByte (device_address, 0x81, 0xFF);
    I2C_WriteByte (device_address, 0x82, 0x03);
    I2C_WriteByte (device_address, 0x83, (uint8_t) (input_video->hact & 0xFF));
    I2C_WriteByte (device_address, 0x84, (uint8_t) (input_video->hact >> 8));
    I2C_WriteByte (device_address, 0x85, 0x80);
    I2C_WriteByte (device_address, 0x86, 0x10);
    I2C_WriteByte (device_address, 0x87, (uint8_t) (panel->htotal & 0xFF));
    I2C_WriteByte (device_address, 0x88, (uint8_t) (panel->htotal >> 8));
    I2C_WriteByte (device_address, 0x89, (uint8_t) (panel->hs & 0xFF));
    I2C_WriteByte (device_address, 0x8A, (uint8_t) (panel->hbp & 0xFF));
    I2C_WriteByte (device_address, 0x8B, (uint8_t) (panel->vs & 0xFF));
    I2C_WriteByte (device_address, 0x8C, (uint8_t) (panel->hact & 0xFF));
    I2C_WriteByte (device_address, 0x8D, (uint8_t) (panel->vact & 0xFF));
    I2C_WriteByte (device_address, 0x8E, (uint8_t) ((panel->vact >> 8) * 16 + (panel->hact >> 8)));
    I2C_WriteByte (device_address, 0x8F, (uint8_t) (h_ratio & 0xFF));
    I2C_WriteByte (device_address, 0x90, (uint8_t) (h_ratio >> 8));
    I2C_WriteByte (device_address, 0x91, (uint8_t) (v_ratio & 0xFF));
    I2C_WriteByte (device_address, 0x92, (uint8_t) (v_ratio >> 8));
    I2C_WriteByte (device_address, 0x7F, 0x96);
    I2C_WriteByte (device_address, 0xA8, 0x13);

    /* Reset PLL LVDS e scaler */
    I2C_WriteByte (device_address, 0x02, 0xF7);
    I2C_WriteByte (device_address, 0x02, 0xFF);

    I2C_WriteByte (device_address, 0x03, 0xCF);
    I2C_WriteByte (device_address, 0x03, 0xFF);

    I2C_WriteByte (device_address, 0x7F, 0xB0);

    /* Loop esperando o flag do scaler; usando a sua função I2C_ReadByte com ponteiro */
    for (i = 0; i < 300; i++)
    {
        uint8_t status = 0;
        fsp_err_t err = I2C_ReadByte (device_address, 0xA7, &status);
        if (err != FSP_SUCCESS)
        {
            printf ("Scaler_setup: falha leitura 0xA7 (erro %d). tentando novamente... loop=%d\r\n", (int) err, i);
            R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
            continue;
        }

        if (status & 0x20)
        {
            uint8_t a6 = 0;
            err = I2C_ReadByte (device_address, 0xA6, &a6);
            if (err != FSP_SUCCESS)
            {
                printf ("Scaler_setup: falha leitura 0xA6 (erro %d). loop=%d\r\n", (int) err, i);
                R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
                continue;
            }

            htotal = ((uint32_t) (status & 0x0F) << 8) | (uint32_t) a6;
            printf ("Scaler configurado: htotal = %lu (loop=%d)\r\n", htotal, i);
            break;
        }

        if ((i & 0x0F) == 0) /* log menos verboso — mostra a cada 16 loops */
        {
            printf ("Aguardando travamento do scaler... loop=%d\r\n", i);
        }
        R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

void LvdsPowerUp(void)
{
    uint8_t device_address = 0x48;
    I2C_WriteByte (device_address, 0x44, 0x30);
    I2C_WriteByte (device_address, 0x51, 0x05);
}

void LvdsPowerDown(void)
{
    uint8_t device_address = 0x48;
    // I2C_WriteByte(device_address, 0x44, 0x31);
    I2C_WriteByte (device_address, 0x51, 0x15);
    // I2C_WriteByte(device_address, 0x03, 0xfb);
}

void LvdsBypass(void)
{
    uint8_t device_address = 0x48;

    I2C_WriteByte (device_address, 0x50, 0x24); // cp=50uA
    I2C_WriteByte (device_address, 0x51, 0x2d); // Pix_clk as reference, second order passive LPF PLL
    I2C_WriteByte (device_address, 0x52, 0x04); // loopdiv=0; use second-order PLL
    I2C_WriteByte (device_address, 0x69, 0x0e); // CP_PRESET_DIV_RATIO
    I2C_WriteByte (device_address, 0x69, 0x8e);
    I2C_WriteByte (device_address, 0x6a, 0x00);
    I2C_WriteByte (device_address, 0x6c, 0xb8); // RGD_CP_SOFT_K_EN, RGD_CP_SOFT_K[13:8]
    I2C_WriteByte (device_address, 0x6b, 0x51);

    I2C_WriteByte (device_address, 0x04, 0xfb); // core pll reset
    I2C_WriteByte (device_address, 0x04, 0xff);

    I2C_WriteByte (device_address, 0x7f, 0x00); // disable scaler
    I2C_WriteByte (device_address, 0xa8, 0x13); // 0x13:VESA; 0x33:JEIDA
}

void LvdsOutput(_Bool on)
{
    uint8_t device_address = 0x48;

    if (on)
    {
        I2C_WriteByte (device_address, 0x02, 0xf7); // lvds pll reset
        I2C_WriteByte (device_address, 0x02, 0xff); // scaler module reset
        I2C_WriteByte (device_address, 0x03, 0xcb); // lvds tx module reset
        I2C_WriteByte (device_address, 0x03, 0xfb);
        I2C_WriteByte (device_address, 0x03, 0xff);
        I2C_WriteByte (device_address, 0x44, 0x30); // enable lvds output
        printf ("LT8912_lvds_output_enable!\r\n");
    }
    else
    {
        I2C_WriteByte (device_address, 0x44, 0x31);
    }
}

void HdmiOutput(_Bool on)
{
    uint8_t device_address = 0x48;

    if (on)
    {
        I2C_WriteByte (device_address, 0x33, 0x0e); // enable HDMI output
        printf ("HDMI output Enable.\r\n");
    }
    else
    {
        I2C_WriteByte (device_address, 0x33, 0x0c); // disable HDMI output
        printf ("HDMI output Disable.\r\n");
    }
}

void LvdsScalerResult(void)
{
    uint8_t device_address = 0x48;
    I2C_WriteByte (device_address, 0x7f, 0xb0);
}

void ScalerReset(void)
{
    uint8_t device_address = 0x48;
    I2C_WriteByte (device_address, 0x03, 0xcf);
    I2C_WriteByte (device_address, 0x03, 0xff);
}

void lt8912_check_dds(void)
{
    uint8_t device_address = 0x49;
    uint8_t reg_0c, reg_0d, reg_0e, reg_0f;
    uint8_t i;

    for (i = 0; i < 10; i++)
    {
        I2C_ReadByte (device_address, 0x0c, &reg_0c);
        I2C_ReadByte (device_address, 0x0d, &reg_0d);
        I2C_ReadByte (device_address, 0x0e, &reg_0e);
        I2C_ReadByte (device_address, 0x0f, &reg_0f);

        printf ("0x0c~0f = %02x, %02x, %02x, %02x\r\n", reg_0c, reg_0d, reg_0e, reg_0f);
        // if ((reg_0e == 0xd2) && (reg_0d < 0xff) && (reg_0d > 0xd0))
        // {
        //     printf("lvds_check_dds: stable!\n");
        //     break;
        // }
        R_BSP_SoftwareDelay (500, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

void lvds_output_cfg(void)
{
    LvdsPowerUp ();

#ifdef _lvds_bypass
    LvdsBypass();
#else
//    Core_Pll_setup(&KD101FM_1_C001A);
//    Scaler_setup(&video_1280x720_60Hz, &KD101FM_1_C001A);
#endif
}

void MIPI_Input_det(void)
{
    uint8_t device_address = 0x48;
    uint8_t Hsync_L, Hsync_H, Vsync_L, Vsync_H;
    static uint8_t Hsync_L_last = 0, Hsync_H_last = 0, Vsync_L_last = 0, Vsync_H_last = 0;

    I2C_ReadByte (device_address, 0x9c, &Hsync_L);
    I2C_ReadByte (device_address, 0x9d, &Hsync_H);
    I2C_ReadByte (device_address, 0x9e, &Vsync_L);
    I2C_ReadByte (device_address, 0x9f, &Vsync_H);

    printf ("0x9c~9f = %x, %x, %x, %x.\r\n", Hsync_H, Hsync_L, Vsync_H, Vsync_L);
    if ((Hsync_H != Hsync_H_last) || (Vsync_H != Vsync_H_last))
    {
        printf ("0x9c~9f = %x, %x, %x, %x.\r\n", Hsync_H, Hsync_L, Vsync_H, Vsync_L);

        if (Vsync_H == 0x02 && Vsync_L <= 0xef && Vsync_L >= 0xec)
        {
            video = &video_1280x720_60Hz;
            printf ("videoformat = VESA_1280x720_60\r\n");
        }
        else if (Vsync_H == 0x03 && Vsync_L <= 0x3a && Vsync_L >= 0x34)
        {
            video = &video_1280x800_60Hz;
            printf ("videoformat = VESA_1280x800_60\r\n");
        }
        else if (Vsync_H == 0x04 && Vsync_L <= 0x67 && Vsync_L >= 0x63)
        {
            video = &video_1920x1080_60Hz;
            printf ("videoformat = VESA_1920x1080_60\r\n");
        }
        else
        {
            printf ("videoformat = video_none\r\n");
        }

        Hsync_L_last = Hsync_L;
        Hsync_H_last = Hsync_H;
        Vsync_L_last = Vsync_L;
        Vsync_H_last = Vsync_H;

        MIPI_Video_Setup (video);
        AviInfoframe (video);
        MIPIRxLogicRes ();
    }
}

void pattern_test(void)
{
    uint8_t device_address;
    uint32_t DDS_initial_value;
    uint8_t pclk_Mhz;

    // Selecionar resolução (exemplo: 1920x1080@60Hz)
    // video = &video_640x480_60Hz;
    // video = &video_720x480_60Hz;
    // video = &video_800x600_60Hz;
//     video = &video_1280x720_60Hz;
    // video = &video_1280x800_60Hz;
    video = &video_1920x1080_60Hz;

    DigitalClockEn ();
    TxAnalog ();
    CbusAnalog ();
    HDMIPllAnalog ();

    AudioIIsEn ();
    AviInfoframe (video);
    lvds_output_cfg ();

    //////////////////////////////////////////////////////
    // Pattern Resolution Setup
    //////////////////////////////////////////////////////
    device_address = 0x49;

    I2C_WriteByte (device_address, 0x72, 0x12);
    I2C_WriteByte (device_address, 0x73, (uint8_t) ((video->hs + video->hbp) % 256));   // RGD_PTN_DE_DLY[7:0]
    I2C_WriteByte (device_address, 0x74, (uint8_t) ((video->hs + video->hbp) / 256));   // RGD_PTN_DE_DLY[11:8]
    I2C_WriteByte (device_address, 0x75, (uint8_t) ((video->vs + video->vbp) % 256));   // RGD_PTN_DE_TOP[6:0]
    I2C_WriteByte (device_address, 0x76, (uint8_t) (video->hact % 256));                // RGD_PTN_DE_CNT[7:0]
    I2C_WriteByte (device_address, 0x77, (uint8_t) (video->vact % 256));                // RGD_PTN_DE_LIN[7:0]
    I2C_WriteByte (device_address, 0x78, (uint8_t) (((video->vact / 256) << 4) + (video->hact / 256))); // DE_LIN[10:8],DE_CNT[11:8]
    I2C_WriteByte (device_address, 0x79, (uint8_t) (video->htotal % 256));              // RGD_PTN_H_TOTAL[7:0]
    I2C_WriteByte (device_address, 0x7A, (uint8_t) (video->vtotal % 256));              // RGD_PTN_V_TOTAL[7:0]
    I2C_WriteByte (device_address, 0x7B, (uint8_t) (((video->vtotal / 256) << 4) + (video->htotal / 256))); // V_TOTAL[10:8],H_TOTAL[11:8]
    I2C_WriteByte (device_address, 0x7C, (uint8_t) (video->hs % 256));                  // RGD_PTN_HWIDTH[7:0]
    I2C_WriteByte (device_address, 0x7D, (uint8_t) (((video->hs / 256) << 6) + (video->vs % 256))); // HWIDTH[9:8],VWIDTH[5:0]
    I2C_WriteByte (device_address, 0x70, 0x80);  // Pattern enable
    I2C_WriteByte (device_address, 0x71, 0x51);
    I2C_WriteByte (device_address, 0x42, 0x12);

    I2C_WriteByte (device_address, 0x1E, 0x67);  // HV DPol, HDMI Sel, PLL Sel

    //////////////////////////////////////////////////////
    // Pattern Pixel Clock Setup
    //////////////////////////////////////////////////////
    pclk_Mhz = (uint8_t) (video->pclk_khz / 1000);
    DDS_initial_value = (uint32_t) (pclk_Mhz * 0x16C16);

    I2C_WriteByte (device_address, 0x4E, (uint8_t) (DDS_initial_value & 0x000000FF));          // strm_sw_freq_word[7:0]
    I2C_WriteByte (device_address, 0x4F, (uint8_t) ((DDS_initial_value & 0x0000FF00) >> 8));  // strm_sw_freq_word[15:8]
    I2C_WriteByte (device_address, 0x50, (uint8_t) ((DDS_initial_value & 0x00FF0000) >> 16)); // strm_sw_freq_word[23:16]
    I2C_WriteByte (device_address, 0x51, 0x80);                                               // Pattern enable
//
//        I2C_WriteByte(device_address, 0x4E, 0x3E);          // strm_sw_freq_word[7:0]
//        I2C_WriteByte(device_address, 0x4F, 0xE9);   // strm_sw_freq_word[15:8]
//        I2C_WriteByte(device_address, 0x50, 0xD3);  // strm_sw_freq_word[23:16]
//        I2C_WriteByte(device_address, 0x51, 0x80);

    //////////////////////////////////////////////////////
    // Saída HDMI e LVDS
    //////////////////////////////////////////////////////
    HdmiOutput (1);
    LvdsOutput (1);
}

uint8_t LT8912_Get_HPD(void)
{
    uint8_t device_address = 0x48;
    uint8_t data = 0;

    // (0x90) 0xC1[bit7] — HPD High ou Low
    if (I2C_ReadByte (device_address, 0xC1, &data) == FSP_SUCCESS)
    {
        if ((data & 0x80) == 0x80)
        {
            printf ("LT8912_Get_HPD: high\r\n");
            return 1;
        }
        else
        {
            printf ("LT8912_Get_HPD: low\r\n");
            return 0;
        }

        return data;
    }
    else
    {
        printf ("LT8912_Get_HPD: erro na leitura I2C\r\n");
        return 0;
    }
}

uint16_t LT8912B_GetChipID(void)
{
    uint8_t device_address = 0x48;
    uint8_t id_high = 0, id_low = 0;

    if (I2C_ReadByte (device_address, 0x00, &id_high) == FSP_SUCCESS
            && I2C_ReadByte (device_address, 0x01, &id_low) == FSP_SUCCESS)
    {
        printf ("LT8912B chip ID: 0x%02X, 0x%02X\r\n", id_high, id_low);
    }
    else
    {
        printf ("LT8912B chip ID: erro na leitura I2C\r\n");
    }

    return (uint16_t) id_high << 8 | id_low;
}

void LT8912_Sleep_exit_HDMI(void)
{
    I2C_WriteByte (0x48, 0x08, 0xff); //enable clk gating
    I2C_WriteByte (0x48, 0x41, 0xbc); //MIPI Rx Power On
    I2C_WriteByte (0x48, 0x05, 0xfb); //DDS logical reset
    I2C_WriteByte (0x48, 0x05, 0xff);
    I2C_WriteByte (0x48, 0x03, 0x7f); //MIPI RX logical reset
    R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
    I2C_WriteByte (0x48, 0x03, 0xff);
    I2C_WriteByte (0x48, 0x32, 0xa1);
    I2C_WriteByte (0x48, 0x33, 0x03);
}

void LT8912B_Suspend(bool on)
{
    uint8_t device_address = 0x48;

    if (on)
    {
        if (!suspend_on)
        {
            // Enter suspend mode
            I2C_WriteByte (device_address, 0x54, 0x1d);
            I2C_WriteByte (device_address, 0x51, 0x15);
            I2C_WriteByte (device_address, 0x44, 0x31);
            I2C_WriteByte (device_address, 0x41, 0xbd);
            I2C_WriteByte (device_address, 0x5c, 0x11);

            suspend_on = 1;
            printf ("%s suspend on.\r\n", LOG_FLAG);
        }
    }
    else
    {
        if (suspend_on)
        {
            // Exit suspend mode
            I2C_WriteByte (device_address, 0x5c, 0x10);
            I2C_WriteByte (device_address, 0x54, 0x1c);
            I2C_WriteByte (device_address, 0x51, 0x2d);
            I2C_WriteByte (device_address, 0x44, 0x30);
            I2C_WriteByte (device_address, 0x41, 0xbc);

            R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
            I2C_WriteByte (device_address, 0x03, 0x7f);
            R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
            I2C_WriteByte (device_address, 0x03, 0xff);

            I2C_WriteByte (device_address, 0x05, 0xfb);
            R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
            I2C_WriteByte (device_address, 0x05, 0xff);

            suspend_on = 0;
            printf ("%s suspend off.\r\n", LOG_FLAG);
        }
    }
}

void MIPIDig480P(void)
{

    I2C_WriteByte (0x49, 0x18, 0x3e);
    I2C_WriteByte (0x49, 0x19, 0x06);
    I2C_WriteByte (0x49, 0x1c, 0xd0); // H_active[7:0]
    I2C_WriteByte (0x49, 0x1d, 0x02);  // H_active[15:8]
    I2C_WriteByte (0x49, 0x2f, 0x0c);
    I2C_WriteByte (0x49, 0x34, 0x5a);  // H_total[7:0]
    I2C_WriteByte (0x49, 0x35, 0x03);  // H_total[15:8]
    I2C_WriteByte (0x49, 0x36, 0x0d); // V_total[7:0]
    I2C_WriteByte (0x49, 0x37, 0x02); // V_total[15:8]
    I2C_WriteByte (0x49, 0x38, 0x1e);
    I2C_WriteByte (0x49, 0x39, 0x00);
    I2C_WriteByte (0x49, 0x3a, 0x09);
    I2C_WriteByte (0x49, 0x3b, 0x00);
    I2C_WriteByte (0x49, 0x3c, 0x3c);
    I2C_WriteByte (0x49, 0x3d, 0x00);
    I2C_WriteByte (0x49, 0x3e, 0x10);
    I2C_WriteByte (0x49, 0x3f, 0x00);
}

void LT8912B_Config(void)
{
    LT8912B_GetChipID ();

    DigitalClockEn ();

    TxAnalog ();
    CbusAnalog ();
    HDMIPllAnalog ();
    MipiAnalog ();
    MipiBasicSet ();

    struct video_timing *my_video = &video_800x600_60Hz;

    MIPI_Video_Setup (my_video);
    LT8912_DDS_Update (my_video);
    AviInfoframe (my_video);


    AudioIIsEn ();
    MIPIRxLogicRes ();

    // Reset do DDS para garantir
    I2C_WriteByte(0x48, 0x05, 0xFB);
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
    I2C_WriteByte(0x48, 0x05, 0xFF);

    HdmiOutput (1);

}

void HDMI_Test_Pattern(void)
{
    uint8_t device_address;

    // LT8912 I2C address 0x90 for analog / control registers
    device_address = 0x48;

    I2C_WriteByte (0x48, 0x54, 0x1d);
    I2C_WriteByte (0x48, 0x51, 0x15);
    I2C_WriteByte (0x48, 0x44, 0x31);
    I2C_WriteByte (0x48, 0x41, 0xbd);
    I2C_WriteByte (0x48, 0x5c, 0x11);

    // General control registers
    I2C_WriteByte (device_address, 0x08, 0xff);
    I2C_WriteByte (device_address, 0x09, 0xff);
    I2C_WriteByte (device_address, 0x0a, 0xff);
    I2C_WriteByte (device_address, 0x0b, 0xff);
    I2C_WriteByte (device_address, 0x0c, 0xff);

    // Analog PHY / lane / output control
    I2C_WriteByte (device_address, 0x31, 0xa1);
    I2C_WriteByte (device_address, 0x32, 0xa1);
    I2C_WriteByte (device_address, 0x33, 0x03);
    I2C_WriteByte (device_address, 0x37, 0x00);
    I2C_WriteByte (device_address, 0x38, 0x22);
    I2C_WriteByte (device_address, 0x60, 0x82);
    I2C_WriteByte (device_address, 0x39, 0x45);
    I2C_WriteByte (device_address, 0x3b, 0x00);
    I2C_WriteByte (device_address, 0x44, 0x31);
    I2C_WriteByte (device_address, 0x55, 0x44);
    I2C_WriteByte (device_address, 0x57, 0x01);
    I2C_WriteByte (device_address, 0x5a, 0x02);

    // MIPI PHY settings (I2C address 0x92)
    device_address = 0x49;
    I2C_WriteByte (device_address, 0x10, 0x20);  // Term enable: LP->HS mode
    I2C_WriteByte (device_address, 0x11, 0x04);  // Settle timing PRPR->SOT
    I2C_WriteByte (device_address, 0x12, 0x04);  // Trail
    I2C_WriteByte (device_address, 0x13, 0x02);  // Lane config: 0=4 lanes
    I2C_WriteByte (device_address, 0x14, 0x00);  // Debug mux
    I2C_WriteByte (device_address, 0x15, 0x00);
    I2C_WriteByte (device_address, 0x1a, 0x03);  // Hshift
    I2C_WriteByte (device_address, 0x1b, 0x03);  // Vshift
    I2C_WriteByte (device_address, 0x18, 0x3e);  // Hwidth
    I2C_WriteByte (device_address, 0x19, 0x06);  // Vwidth
    I2C_WriteByte (device_address, 0x1c, 0xd0);  // Pixel num Hactive LSB
    I2C_WriteByte (device_address, 0x1d, 0x02);  // Pixel num Hactive MSB
    I2C_WriteByte (device_address, 0x1e, 0x67);  // H/V/D polarity, HDMI sel, PLL sel
    I2C_WriteByte (device_address, 0x2f, 0x0c);  // FIFO buffer length

    // Timing settings
    I2C_WriteByte (device_address, 0x34, 0x5a); // Htotal LSB
    I2C_WriteByte (device_address, 0x35, 0x03); // Htotal MSB
    I2C_WriteByte (device_address, 0x36, 0x0d); // Vtotal LSB
    I2C_WriteByte (device_address, 0x37, 0x02); // Vtotal MSB
    I2C_WriteByte (device_address, 0x38, 0x1e); // VBP LSB
    I2C_WriteByte (device_address, 0x39, 0x00); // VBP MSB
    I2C_WriteByte (device_address, 0x3a, 0x09); // VFP LSB
    I2C_WriteByte (device_address, 0x3b, 0x00); // VFP MSB
    I2C_WriteByte (device_address, 0x3c, 0x3c); // HBP LSB
    I2C_WriteByte (device_address, 0x3d, 0x00); // HBP MSB
    I2C_WriteByte (device_address, 0x3e, 0x10); // HFP LSB
    I2C_WriteByte (device_address, 0x3f, 0x00); // HFP MSB

    // Pattern generator
    I2C_WriteByte (device_address, 0x72, 0x12);
    I2C_WriteByte (device_address, 0x73, 0x7a); // DE delay LSB
    I2C_WriteByte (device_address, 0x74, 0x00); // DE delay MSB
    I2C_WriteByte (device_address, 0x75, 0x24); // DE top
    I2C_WriteByte (device_address, 0x76, 0xd0); // DE count LSB
    I2C_WriteByte (device_address, 0x77, 0xe0); // DE line LSB
    I2C_WriteByte (device_address, 0x78, 0x12); // DE line / count MSB
    I2C_WriteByte (device_address, 0x79, 0x5a); // H total LSB
    I2C_WriteByte (device_address, 0x7a, 0x0d); // V total LSB
    I2C_WriteByte (device_address, 0x7b, 0x23); // V/H total MSB
    I2C_WriteByte (device_address, 0x7c, 0x3e); // Hwidth LSB
    I2C_WriteByte (device_address, 0x7d, 0x06); // Hwidth/Vwidth MSB
    I2C_WriteByte (device_address, 0x70, 0x80); // Pattern enable
    I2C_WriteByte (device_address, 0x71, 0x51);

    // DDS / pixel clock setup
    I2C_WriteByte (device_address, 0x4e, 0x66); // freq word LSB
    I2C_WriteByte (device_address, 0x4f, 0x66); // freq word MID
    I2C_WriteByte (device_address, 0x50, 0x26); // freq word MSB
    I2C_WriteByte (device_address, 0x51, 0x80); // DDS enable / pattern enable
}

