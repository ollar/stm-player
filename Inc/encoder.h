#pragma once

#include <stdint.h>

#define ENCODER_PORT GPIOA
#define ENCODER_PIN_A GPIO_PIN_1
#define ENCODER_PIN_B GPIO_PIN_0

// PA0 → TIM2_CH1 (фаза A), PA1 → TIM2_CH2 (фаза B)
void encoder_init(void);

int32_t encoder_get_delta(void);

void encoder_reset(void);
void encoder_listen_change(void);
void set_enc_change_handler(void (*)(int32_t));
void clear_enc_change_handler(void);
