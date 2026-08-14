#include "i2s_init.h"
#include "i2s_utils.h"
#include "stm32f4xx_hal.h"
#include "usart_init.h"

I2S_HandleTypeDef hi2s = {0};
DMA_HandleTypeDef hdma_spi3_tx = {0};

void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s_ptr) {
  if (hi2s_ptr->Instance != SPI3)
    return;

  /* Clocks */
  __HAL_RCC_SPI3_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* GPIO */
  GPIO_InitTypeDef gpio = {0};

  gpio.Pin = I2S_PIN_LCK;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S_LCK_PORT, &gpio);

  /* PB3 -> I2S3_CK, PB5 -> I2S3_SD (AF6) */
  gpio.Pin = I2S_PIN_BCK | I2S_PIN_DIN;
  HAL_GPIO_Init(I2S_BCK_PORT, &gpio);

  /* DMA1 Stream7 Channel0 */
  hdma_spi3_tx.Instance = DMA1_Stream7;
  hdma_spi3_tx.Init.Channel = DMA_CHANNEL_0;
  hdma_spi3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_spi3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_spi3_tx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_spi3_tx.Init.PeriphDataAlignment =
      DMA_PDATAALIGN_HALFWORD; /* DR 16-bit */
  hdma_spi3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_spi3_tx.Init.Mode = DMA_CIRCULAR;
  hdma_spi3_tx.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_spi3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_spi3_tx);

  __HAL_LINKDMA(hi2s_ptr, hdmatx, hdma_spi3_tx);

  /* NVIC */
  HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
  HAL_NVIC_SetPriority(SPI3_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(SPI3_IRQn);
}

void i2s_init(Wav_Header_t *header) {
  hi2s.Instance = SPI3;
  hi2s.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s.Init.DataFormat = I2S_DATAFORMAT_24B;
  hi2s.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s.Init.AudioFreq = get_i2s_audiofreq(header);
  hi2s.Init.CPOL = I2S_CPOL_LOW;
  hi2s.Init.ClockSource = I2S_CLOCK_PLL;

  if (HAL_I2S_Init(&hi2s) != HAL_OK) {
    hprintf_formatted("I2S init error: %d\r\n", hi2s.ErrorCode);
  } else {
    uint32_t i2spr = SPI3->I2SPR;
    hprintf_formatted("I2S OK, I2SDIV=%lu, ODD=%lu\r\n",
                      i2spr & SPI_I2SPR_I2SDIV,
                      (i2spr & SPI_I2SPR_ODD) ? 1 : 0);
  }
}

void i2s_deinit(void) { HAL_I2S_DeInit(&hi2s); }
