#pragma once

#include <stdint.h>

// PA0 → TIM2_CH1 (фаза A), PA1 → TIM2_CH2 (фаза B)
void encoder_init(void);

// Возвращает число "щелчков" энкодера (+/-) со времени последнего вызова
int32_t encoder_get_delta(void);

// Сброс счётчика в центр (0x8000, чтобы избежать проблем с переполнением сразу
// после старта)
void encoder_reset(void);

void encoder_handle_change(void);
void set_enc_change_handler(void (*)(int32_t));
