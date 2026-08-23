#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define OLED_HEIGHT 128
#define OLED_WIDTH 128
#define OLED_BUFFER_SIZE (OLED_HEIGHT * OLED_WIDTH) / 8
#define LVGL_BUFFER_SIZE OLED_BUFFER_SIZE + 8

#define OLED_PORT GPIOA
#define OLED_RES_PIN GPIO_PIN_2
#define OLED_CS_PIN GPIO_PIN_3
#define OLED_DC_PIN GPIO_PIN_4
#define OLED_SCK_PIN GPIO_PIN_5
#define OLED_MOSI_PIN GPIO_PIN_7

static void MX_SPI1_Init();

void OLED_SendCommand(uint8_t cmd);
void OLED_SendData(uint8_t data);

void OLED_Init();
void OLED_SetPage(uint8_t page);
void OLED_SetColumn(uint8_t column);
void OLED_Update(void);
void OLED_DrawPixel_Buffered(uint8_t x, uint8_t y, uint8_t color);
void OLED_SendDataBuffer(uint8_t *buffer, uint16_t size);
void OLED_Clear(void);
void OLED_Sleep(void);
void OLED_Wakeup(void);
