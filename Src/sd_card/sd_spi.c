#include "sd_spi.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <string.h>

#include "usart_init.h"

SPI_HandleTypeDef h_sd_spi2;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef hdma_spi2_tx;

void SD_InitSPI(void) {
  GPIO_InitTypeDef g = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_SPI2_CLK_ENABLE();

  // SCK, MOSI, MISO
  g.Pin = SD_SCK_PIN | SD_MOSI_PIN | SD_MISO_PIN;
  g.Mode = GPIO_MODE_AF_PP;
  g.Pull = GPIO_NOPULL;
  g.Speed = GPIO_SPEED_FREQ_HIGH;
  g.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(SD_CARD_PORT, &g);

  // CS
  g.Pin = SD_CS_PIN;
  g.Mode = GPIO_MODE_OUTPUT_PP;
  g.Pull = GPIO_PULLUP;
  g.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_CARD_CS_PORT, &g);
  HAL_GPIO_WritePin(SD_CARD_PORT, SD_CS_PIN, GPIO_PIN_SET);

  h_sd_spi2.Instance = SPI2;
  h_sd_spi2.Init.Mode = SPI_MODE_MASTER;
  h_sd_spi2.Init.Direction = SPI_DIRECTION_2LINES;
  h_sd_spi2.Init.DataSize = SPI_DATASIZE_8BIT;
  h_sd_spi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  h_sd_spi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  h_sd_spi2.Init.NSS = SPI_NSS_SOFT;
  h_sd_spi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // медленно
  h_sd_spi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  h_sd_spi2.Init.TIMode = SPI_TIMODE_DISABLE;
  h_sd_spi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  HAL_SPI_Init(&h_sd_spi2);
}

void SD_InitDMA(void) {
  __HAL_RCC_DMA1_CLK_ENABLE();

  // RX: DMA1 Stream3 Channel0 (SPI2_RX)
  hdma_spi2_rx.Instance = DMA1_Stream3;
  hdma_spi2_rx.Init.Channel = DMA_CHANNEL_0;
  hdma_spi2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_spi2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_spi2_rx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_spi2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_spi2_rx.Init.Mode = DMA_NORMAL;
  hdma_spi2_rx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_spi2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_spi2_rx);
  __HAL_LINKDMA(&h_sd_spi2, hdmarx, hdma_spi2_rx);

  // TX: DMA1 Stream4 Channel0 (SPI2_TX)
  hdma_spi2_tx.Instance = DMA1_Stream4;
  hdma_spi2_tx.Init.Channel = DMA_CHANNEL_0;
  hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_spi2_tx.Init.Mode = DMA_NORMAL;
  hdma_spi2_tx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_spi2_tx);
  __HAL_LINKDMA(&h_sd_spi2, hdmatx, hdma_spi2_tx);

  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
}

void SD_Increase_Speed(void) {
  h_sd_spi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  HAL_SPI_Init(&h_sd_spi2);
}

void DMA1_Stream3_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_spi2_rx); }
void DMA1_Stream4_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_spi2_tx); }
