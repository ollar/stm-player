#pragma once

#include "stm32f4xx_hal.h"

typedef struct {
  GPIO_TypeDef *port;
  uint16_t pin;
  uint8_t state;
  uint32_t press_start;
  void (*button_onclick_handler)(uint32_t);
} Button_t;

typedef struct {
  Button_t buttons[5];
  uint8_t length;
} Buttons_Set_t;

static void button_click_handler_dummy(uint32_t) {};

Button_t *button_init(GPIO_TypeDef *, uint16_t);
void buttons_listen_change(void);
void set_button_onclick_handler(Button_t *,
                                void (*new_onclick_handler)(uint32_t));
