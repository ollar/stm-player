#include "button.h"
#include "sleep_mode.h"
#include "stm32f4xx_hal.h"
#include "usart_init.h"

Buttons_Set_t buttons_set = {0};

Button_t *button_init(GPIO_TypeDef *port, uint16_t pin, uint32_t mode) {
  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = pin;
  gpio.Mode = mode;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(port, &gpio);

  Button_t button = {0};
  button.pin = pin;
  button.port = port;
  button.onclick_handler = &button_click_handler_dummy;
  button.onpress_handler = &button_press_handler_dummy;
  button.onrelease_handler = &button_press_handler_dummy;

  buttons_set.buttons[buttons_set.length] = button;
  buttons_set.length++;

  return &buttons_set.buttons[buttons_set.length - 1];
}

static uint8_t is_low_to_high(GPIO_PinState prev_state,
                              GPIO_PinState new_state) {
  return prev_state == GPIO_PIN_SET && new_state == GPIO_PIN_RESET;
}

static uint8_t is_high_to_low(GPIO_PinState prev_state,
                              GPIO_PinState new_state) {
  return prev_state == GPIO_PIN_RESET && new_state == GPIO_PIN_SET;
}

void buttons_listen_change(void) {
  for (uint8_t i = 0; i < buttons_set.length; i++) {
    Button_t *button = &buttons_set.buttons[i];

    GPIO_PinState button_new_state =
        HAL_GPIO_ReadPin(button->port, button->pin);

    if (is_low_to_high(button->state, button_new_state)) {
      button->press_start = HAL_GetTick();
      button->onpress_handler();
    }

    if (is_high_to_low(button->state, button_new_state)) {
      clear_sleep_timers();
      uint32_t button_press_end = HAL_GetTick();
      uint32_t pressed_time_delta = button_press_end - button->press_start;

      button->onrelease_handler();
      button->onclick_handler(pressed_time_delta);
    }

    button->state = button_new_state;
  }
}

void set_button_onclick_handler(Button_t *button,
                                void (*new_onclick_handler)(uint32_t)) {
  button->onclick_handler = new_onclick_handler;
}

void set_button_onpress_handler(Button_t *button,
                                void (*new_onpress_handler)(void)) {
  button->onpress_handler = new_onpress_handler;
}

void set_button_onrelease_handler(Button_t *button,
                                  void (*new_onrelease_handler)(void)) {
  button->onrelease_handler = new_onrelease_handler;
}

void clear_button_event_handlers(Button_t *button) {
  button->onclick_handler = &button_click_handler_dummy;
  button->onpress_handler = &button_press_handler_dummy;
  button->onrelease_handler = &button_press_handler_dummy;
}

void clear_buttons_event_handlers(void) {
  for (uint8_t i = 0; i < buttons_set.length; i++) {
    Button_t *button = &buttons_set.buttons[i];

    clear_button_event_handlers(button);
  }
}
