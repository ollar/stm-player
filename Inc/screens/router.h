#pragma once

typedef enum {
  TRACKLIST_SCREEN = 0,
  NO_SD_CARD_SCREEN,
  PLAYER_SCREEN
} SCREEN_NAMES_ENUM;

void transition_to_screen(SCREEN_NAMES_ENUM);
extern void (*rerender_func)(void);
void set_rerender_function(void (*)(void));
