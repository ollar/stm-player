#pragma once

#include "i2s_common.h"

#define I2S_LCK_PORT GPIOA
#define I2S_BCK_PORT GPIOB

#define I2S_PIN_LCK GPIO_PIN_15
#define I2S_PIN_BCK GPIO_PIN_3
#define I2S_PIN_DIN GPIO_PIN_5

void i2s_init(Wav_Header_t *header);
void i2s_deinit(void);
