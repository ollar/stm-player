#pragma once

#include "lvgl.h"

#define SOUND_VOLUME_NORMALIZER 8388607

typedef struct {
  uint8_t is_playing;
  float volume;
} Player_state_t;

lv_obj_t *create_player_screen(void);
void play_next_track(void);
