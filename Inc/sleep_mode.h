#pragma once

#define SLEEP_MODE_TIMEOUT 100000
#define SLEEP_SCREEN_TIMEOUT 10000

static void enter_sleep_mode(void);
static void wakeup_from_sleep_mode(void);
static void save_original_button_click_handler(void);
static void restore_original_button_click_handler(void);
void listen_for_sleep_mode(void);
void listen_for_screensave(void);
void clear_sleep_timers(void);
