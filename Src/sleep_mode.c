#include "sleep_mode.h"
#include "button.h"
#include "main.h"
#include "oled_sh1107.h"
#include "screens/player.h"
#include "stm32f4xx_hal.h"

extern uint32_t sleep_timer_tick;
extern uint32_t screen_sleep_timer_tick;
extern Buttons_Set_t buttons_set;
extern Player_state_t player_state;

static uint8_t is_screensaving = 0;
static void (*button_click_handler)(uint32_t);

static void setup_wakeup_button() {
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  save_original_button_click_handler();
}

static void save_original_button_click_handler() {
  Button_t *button = &buttons_set.buttons[0];

  if (button->onclick_handler == button_click_handler_dummy) {
    return;
  }

  button_click_handler = button->onclick_handler;
  button->onclick_handler = button_click_handler_dummy;
}

static void restore_original_button_click_handler() {
  Button_t *button = &buttons_set.buttons[0];

  button->onclick_handler = button_click_handler;
  button_click_handler = button_click_handler_dummy;
}

void clear_sleep_timers() {
  sleep_timer_tick = 0;
  screen_sleep_timer_tick = 0;
}

void listen_for_sleep_mode() {
  if (player_state.is_playing) {
    sleep_timer_tick = 0;
    return;
  }

  if (sleep_timer_tick > SLEEP_MODE_TIMEOUT) {
    sleep_timer_tick = 0;
    enter_sleep_mode();
  }
}

void listen_for_screensave() {
  if (screen_sleep_timer_tick < SLEEP_SCREEN_TIMEOUT && is_screensaving) {
    restore_original_button_click_handler();
    OLED_Wakeup();
    is_screensaving = 0;
  }

  if (screen_sleep_timer_tick > SLEEP_SCREEN_TIMEOUT && !is_screensaving) {
    save_original_button_click_handler();
    OLED_Sleep();
    is_screensaving = 1;
  }
}

static void enter_sleep_mode() {
  setup_wakeup_button();

  HAL_SuspendTick();

  OLED_Sleep();

  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

  while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) {
  }

  wakeup_from_sleep_mode();
}

static void wakeup_from_sleep_mode() {
  SystemClock_Config();

  restore_original_button_click_handler();
  is_screensaving = 0;

  OLED_Wakeup();

  HAL_ResumeTick();
}
