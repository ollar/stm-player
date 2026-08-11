#include "oled_sh1107.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"
#include <string.h>

#define SH1107_COL_OFFSET 2

SPI_HandleTypeDef h_oled_spi1;

uint8_t framebuffer[OLED_BUFFER_SIZE] = {0};

static void MX_SPI1_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();

  // SPI пины
  GPIO_InitStruct.Pin = OLED_SCK_PIN | OLED_MOSI_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(OLED_PORT, &GPIO_InitStruct);

  // CS, DC, RES как обычные выходы
  GPIO_InitStruct.Pin = OLED_DC_PIN | OLED_CS_PIN | OLED_RES_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OLED_PORT, &GPIO_InitStruct);

  // Изначально CS = 1 (отключено)
  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(OLED_PORT, OLED_RES_PIN, GPIO_PIN_SET);

  __HAL_RCC_SPI1_CLK_ENABLE();

  h_oled_spi1.Instance = SPI1;
  h_oled_spi1.Init.Mode = SPI_MODE_MASTER;
  h_oled_spi1.Init.Direction = SPI_DIRECTION_2LINES;
  h_oled_spi1.Init.DataSize = SPI_DATASIZE_8BIT;
  h_oled_spi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  h_oled_spi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  h_oled_spi1.Init.NSS = SPI_NSS_SOFT;
  h_oled_spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  h_oled_spi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  h_oled_spi1.Init.TIMode = SPI_TIMODE_DISABLE;
  h_oled_spi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  h_oled_spi1.Init.CRCPolynomial = 10;
  HAL_SPI_Init(&h_oled_spi1);
}

void OLED_SendCommand(uint8_t cmd) {
  HAL_GPIO_WritePin(OLED_PORT, OLED_DC_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_RESET);

  HAL_SPI_Transmit(&h_oled_spi1, &cmd, 1, HAL_MAX_DELAY);

  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_SET);
}

void OLED_SendData(uint8_t data) {
  HAL_GPIO_WritePin(OLED_PORT, OLED_DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_RESET);

  HAL_SPI_Transmit(&h_oled_spi1, &data, 1, HAL_MAX_DELAY);

  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_SET);
}

void OLED_SendDataBuffer(uint8_t *buffer, uint16_t size) {
  HAL_GPIO_WritePin(OLED_PORT, OLED_DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_RESET);

  HAL_SPI_Transmit(&h_oled_spi1, buffer, size, HAL_MAX_DELAY);

  HAL_GPIO_WritePin(OLED_PORT, OLED_CS_PIN, GPIO_PIN_SET);
}

// void OLED_Init() {
//   MX_GPIO_Init();
//   MX_SPI1_Init();
//
//   HAL_Delay(100);
//
//   // Аппаратный сброс дисплея
//   HAL_GPIO_WritePin(GPIOB, OLED_RES_PIN, GPIO_PIN_RESET);
//   HAL_Delay(20);
//   HAL_GPIO_WritePin(GPIOB, OLED_RES_PIN, GPIO_PIN_SET);
//   HAL_Delay(50);
//
//   // --- Инициализация SH1107 (128x128) ---
//   OLED_SendCommand(0xAE); // Display OFF
//
//   OLED_SendCommand(0xD5); // Set Osc Frequency
//   OLED_SendCommand(0x50); // Рекомендуемое значение
//
//   OLED_SendCommand(0xA8); // Set Multiplex Ratio
//   OLED_SendCommand(0x7F); // 128 строк (0x7F = 127 + 1)
//
//   OLED_SendCommand(0xD3); // Set Display Offset
//   OLED_SendCommand(0x00); // Без смещения
//
//   // OLED_SendCommand(0x40 | 0x00); // Set Display Start Line = 0     # ?????
//   OLED_SendCommand(0xDC); // ???
//   OLED_SendCommand(0x00); // ???
//
//   OLED_SendCommand(0xAD); // DC/DC Control Mode (SH1107!)
//   // OLED_SendCommand(0x8B); // Internal VCC (встроенный DC/DC включен)
//   OLED_SendCommand(0x8A); // Internal VCC (встроенный DC/DC включен)
//   // Попробуй 0x8A, если 0x8B не заработает (external VCC, но обычно 0x8B)
//
//   OLED_SendCommand(0x81); // Set Contrast
//   OLED_SendCommand(0x7F); // Средний контраст (попробуй 0xFF для максимума)
//
//   OLED_SendCommand(0xA1); // Segment Re-map (инверсия по X)
//   // Попробуй 0xA0, если картинка зеркальная
//
//   OLED_SendCommand(0xC8); // COM Output Scan Direction (снизу вверх)
//   // Попробуй 0xC0, если картинка перевернута
//
//   OLED_SendCommand(0xA6); // Normal display (не инвертированный)
//                           // Попробуй 0xA7, если фон и текст инвертированы
//
//   OLED_SendCommand(0x20); // Set Addressing Mode
//   OLED_SendCommand(0x00); // Set Addressing Mode paged
//
//   // OLED_SendCommand(0x20); // Set Addressing Mode
//   // OLED_SendCommand(0x01); // 00 = Horizontal
//   //
//   // OLED_SendCommand(0x21); // Set Column Address
//   // OLED_SendCommand(0x00); // start
//   // OLED_SendCommand(0x7F); // end (127)
//   //
//   // OLED_SendCommand(0x22); // Set Page Address
//   // OLED_SendCommand(0x00); // start
//   // OLED_SendCommand(0x0F); // end (15)
//   //
//   OLED_SendCommand(0xAF); // Display ON
// }

void OLED_Init() {
  MX_SPI1_Init();

  HAL_Delay(100);

  // Аппаратный сброс дисплея
  HAL_GPIO_WritePin(OLED_PORT, OLED_RES_PIN, GPIO_PIN_RESET);
  HAL_Delay(20);
  HAL_GPIO_WritePin(OLED_PORT, OLED_RES_PIN, GPIO_PIN_SET);
  HAL_Delay(50);

  // --- Инициализация SH1107 (128x128) ---
  OLED_SendCommand(0xAE); // Display OFF

  OLED_SendCommand(0xD5); // Set Osc Frequency
  OLED_SendCommand(0x50); // Рекомендуемое значение

  OLED_SendCommand(0xA8); // Set Multiplex Ratio
  OLED_SendCommand(0x7F); // 128 строк (0x7F = 127 + 1)

  OLED_SendCommand(0xD3); // Set Display Offset
  OLED_SendCommand(0x00); // Без смещения

  OLED_SendCommand(0xA6); // Normal display (не инвертированный)

  OLED_SendCommand(0x81); // Set Contrast
  OLED_SendCommand(0x80); // Средний контраст (попробуй 0xFF для максимума)

  OLED_SendCommand(0xAF); // Display ON
}

void OLED_SetPage(uint8_t page) {
  if (page > 15)
    page = 15;
  OLED_SendCommand(0xB0 | page); // 0xB0 + номер страницы (0-15)
}

void OLED_SetColumn(uint8_t column) {
  OLED_SendCommand(0x00 | (column & 0x0F));
  OLED_SendCommand(0x10 | ((column >> 4) & 0x0F));
}

void OLED_Clear(void) {
  memset(framebuffer, 0, OLED_BUFFER_SIZE);
  OLED_Update();
}

void OLED_Update() {
  uint8_t chunk[128];

  for (uint8_t page = 0; page < 16; page++) {
    OLED_SetPage(page);
    OLED_SetColumn(0);

    for (uint8_t i = 0; i < 128; i++) {
      chunk[i] = framebuffer[page * 128 + i];
    }
    OLED_SendDataBuffer(chunk, 128);
  }
}

void OLED_DrawPixel_Buffered(uint8_t x, uint8_t y, uint8_t color) {
  if (x >= 128 || y >= 128)
    return;

  uint8_t page = y / 8;
  uint8_t bit = y % 8;

  if (color) {
    framebuffer[page * 128 + x] |= (1 << bit);
  } else {
    framebuffer[page * 128 + x] &= ~(1 << bit);
  }
}
