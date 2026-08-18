#include "lvgl.h"

typedef struct {
  uint8_t is_playing;
  float volume;
} Player_state_t;

lv_obj_t *create_player_screen(void);
void play_next_track(void);
