#include "encoder.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

static TIM_HandleTypeDef htim2;
static uint16_t last_counter = 0;
static int16_t remainder = 0; // накапливает "суб-щелчки" (0..3)

void encoder_init(void) {
  /* --- Включаем тактирование --- */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_TIM2_CLK_ENABLE();

  /* --- PA0 / PA1 в режиме альтернативной функции TIM2 --- */
  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = ENCODER_PIN_A | ENCODER_PIN_B;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pull = GPIO_PULLUP; // голое колесико → нужна подтяжка
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  gpio.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(ENCODER_PORT, &gpio);

  /* --- TIM2: Encoder Interface Mode, канал 1 и 2 --- */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  TIM_Encoder_InitTypeDef enc = {0};
  enc.EncoderMode = TIM_ENCODERMODE_TI12; // x4 максимальное разрешение
  enc.IC1Polarity = TIM_ICPOLARITY_RISING;
  enc.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  enc.IC1Prescaler = TIM_ICPSC_DIV1;
  enc.IC1Filter = 6; // аппаратный фильтр дребезга
  enc.IC2Polarity = TIM_ICPOLARITY_RISING;
  enc.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  enc.IC2Prescaler = TIM_ICPSC_DIV1;
  enc.IC2Filter = 6;

  HAL_TIM_Encoder_Init(&htim2, &enc);
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

  /* --- Стартуем из середины диапазона, чтобы сразу не упёрлись в 0/FFFF --- */
  __HAL_TIM_SET_COUNTER(&htim2, 0x8000);
  last_counter = 0x8000;
  remainder = 0;
}

int32_t encoder_get_delta(void) {
  uint16_t current = (uint16_t)__HAL_TIM_GET_COUNTER(&htim2);

  /* Переполнение 16-битного счётчика обрабатывается автоматически
   * благодаря приведению к int16_t                             */
  int16_t delta = (int16_t)(current - last_counter);

  remainder += delta;
  int32_t clicks = remainder / 2;
  remainder %= 2;

  last_counter = current;
  return clicks;
}

void encoder_reset(void) {
  __HAL_TIM_SET_COUNTER(&htim2, 0x8000);
  last_counter = 0x8000;
  remainder = 0;
}

void dummy_enc_change_handler(int32_t enc_delta) { ; }

void (*enc_change_handler)(int32_t enc_delta) = &dummy_enc_change_handler;

void set_enc_change_handler(void (*change_handler)(int32_t enc_delta)) {
  enc_change_handler = change_handler;
}

void clear_enc_change_handler(void) {
  enc_change_handler = dummy_enc_change_handler;
}

void encoder_listen_change(void) {
  int32_t enc_delta = encoder_get_delta();

  if (enc_delta == 0) {
    return;
  }

  enc_change_handler(enc_delta);
}
