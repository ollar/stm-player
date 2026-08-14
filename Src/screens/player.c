#include "screens/player.h"
#include "button.h"
#include "encoder.h"
#include "i2s_audio.h"
#include "i2s_common.h"
#include "lvgl.h"
#include "lvgl/core/lv_area.h"
#include "lvgl/widgets/lv_label.h"
#include "oled_sh1107.h"
#include "screens/router.h"
#include "usart_init.h"

extern char *current_track_name;
extern Audio_Data_t audio_data;
extern Buttons_Set_t buttons_set;

static lv_obj_t *track_duration = NULL;
static float volumes_table[7] = {0.0f, 0.01f, 0.06f, 0.25f, 0.56f, 0.81f, 1.0f};
static uint8_t current_volume_ind = 5;

Player_state_t player_state = {
    .is_playing = 1,
    .volume = 0.8f,
};

static void rerender_player() {
  if (!track_duration) {
    return;
  }

  uint32_t elapsed_time = audio_data.bytes_read / audio_data.byte_rate;
  uint32_t duration_time = audio_data.chunk_size / audio_data.byte_rate;

  char buffer[16];
  lv_snprintf(buffer, sizeof(buffer), "%02d:%02d / %02d:%02d",
              elapsed_time / 60, elapsed_time % 60, duration_time / 60,
              duration_time % 60);
  lv_label_set_text(track_duration, buffer);
}

static void player_onclick_handler(uint32_t press_delta) {
  if (press_delta > 20 && press_delta < 500) {
    player_state.is_playing = !player_state.is_playing;
  }

  if (press_delta > 1000) {
    transition_to_screen(TRACKLIST_SCREEN);
  }
}

static void player_enc_onchange(int32_t enc_delta) {

  hprintf_formatted("enc_delta %d\r\n", enc_delta);
}

lv_obj_t *create_player_screen(void) {
  set_rerender_function(rerender_player);
  Button_t *button = &buttons_set.buttons[0];
  set_button_onclick_handler(button, player_onclick_handler);
  set_enc_change_handler(player_enc_onchange);

  lv_obj_t *player_screen = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(player_screen, 0, 0);

  sd_read_file();

  lv_obj_t *label = lv_label_create(player_screen);
  lv_label_set_text(label, current_track_name);
  lv_obj_set_width(label, OLED_WIDTH);

  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  track_duration = lv_label_create(player_screen);
  char buffer[16];
  lv_snprintf(buffer, sizeof(buffer), "%d",
              audio_data.chunk_size / audio_data.byte_rate);
  lv_label_set_text(track_duration, buffer);
  lv_obj_set_width(track_duration, OLED_WIDTH);

  lv_obj_align(track_duration, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_align(track_duration, LV_TEXT_ALIGN_CENTER, 0);

  return player_screen;
}
