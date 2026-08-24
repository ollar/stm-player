#pragma once

#include "lvgl.h"

typedef enum {
  TRACKLIST_SCREEN = 0,
  NO_SD_CARD_SCREEN,
  PLAYER_SCREEN
} SCREEN_NAMES_ENUM;

lv_obj_t *transition_to_screen(SCREEN_NAMES_ENUM);
extern void (*rerender_func)(void);
void set_rerender_function(void (*)(void));
lv_obj_t *fallback_to_nocard_screen(void);
