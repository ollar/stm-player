#include "screens/player.h"
#include "button.h"
#include "encoder.h"
#include "files_list.h"
#include "i2s_audio.h"
#include "i2s_common.h"
#include "lvgl.h"
#include "lvgl/core/lv_area.h"
#include "lvgl/draw/lv_color.h"
#include "lvgl/widgets/lv_label.h"
#include "oled_sh1107.h"
#include "screens/router.h"
#include "usart_init.h"

// get_current_track_name
extern Audio_Data_t audio_data;
extern Buttons_Set_t buttons_set;
extern Files_list_t files_list;

static lv_obj_t *label = NULL;
static lv_obj_t *track_duration = NULL;
static const float volumes_table[7] = {0.0f,  0.01f, 0.06f, 0.25f,
                                       0.56f, 0.81f, 1.0f};
static lv_obj_t *volume_bars[7];
static uint8_t current_volume_ind = 5;
static uint8_t is_button_pressed = 0;
static uint8_t is_button_pressed_and_encoder_changed = 0;

Player_state_t player_state = {
    .is_playing = 1,
    .volume = 0.8f,
};

static void rerender_player() {
  if (!track_duration) {
    return;
  }

  lv_label_set_text(label, get_current_track_name());

  uint32_t elapsed_time = audio_data.bytes_read / audio_data.byte_rate;
  uint32_t duration_time = audio_data.chunk_size / audio_data.byte_rate;

  char buffer[16];
  lv_snprintf(buffer, sizeof(buffer), "%02d:%02d / %02d:%02d",
              elapsed_time / 60, elapsed_time % 60, duration_time / 60,
              duration_time % 60);
  lv_label_set_text(track_duration, buffer);

  for (uint8_t i = 0; i < 7; i++) {
    lv_obj_t *rect = volume_bars[i];
    if (i <= current_volume_ind) {
      lv_obj_set_style_bg_color(rect, lv_color_white(), 0);
    } else {
      lv_obj_set_style_bg_color(rect, lv_color_black(), 0);
    }
  }
}

static void player_onclick_handler(uint32_t press_delta) {
  hprintf("player_onclick_handler\r\n");

  if (is_button_pressed_and_encoder_changed) {
    hprintf("is_button_pressed_and_encoder_changed\r\n");
    is_button_pressed_and_encoder_changed = 0;
    return;
  }

  is_button_pressed_and_encoder_changed = 0;

  if (press_delta > 20 && press_delta < 500) {
    player_state.is_playing = !player_state.is_playing;
  }

  if (press_delta > 1000) {
    sd_close_file();
    transition_to_screen(TRACKLIST_SCREEN);
  }
}

static void player_onpress_handler(void) {
  hprintf("player_onpress_handler\r\n");

  is_button_pressed = 1;
}

static void player_onrelease_handler(void) {
  hprintf("player_onrelease_handler\r\n");
  if (is_button_pressed_and_encoder_changed) {
    sd_close_file();
    sd_read_file(get_current_track_name());
  }

  is_button_pressed = 0;
}

static void player_enc_onchange(int32_t enc_delta) {
  if (is_button_pressed) {
    is_button_pressed_and_encoder_changed = 1;
    uint8_t files_list_current = files_list.current;
    files_list_current += enc_delta;
    files_list.current = files_list_current % files_list.size;
  } else {
    if (current_volume_ind == 6 && enc_delta > 0 ||
        current_volume_ind == 0 && enc_delta < 0) {
      current_volume_ind -= enc_delta;
    }

    current_volume_ind += enc_delta;

    player_state.volume = volumes_table[current_volume_ind];
  }
}

lv_obj_t *create_player_screen(void) {
  set_rerender_function(rerender_player);
  Button_t *button = &buttons_set.buttons[0];
  set_button_onpress_handler(button, player_onpress_handler);
  set_button_onrelease_handler(button, player_onrelease_handler);
  set_button_onclick_handler(button, player_onclick_handler);
  set_enc_change_handler(player_enc_onchange);

  lv_obj_t *player_screen = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(player_screen, 0, 0);

  player_state.is_playing = 1;

  char *current_track_name = get_current_track_name();

  sd_read_file(current_track_name);

  // ===================================================
  label = lv_label_create(player_screen);
  lv_label_set_text(label, current_track_name);
  lv_obj_set_width(label, OLED_WIDTH);

  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  // ===================================================
  track_duration = lv_label_create(player_screen);
  char buffer[16];
  lv_snprintf(buffer, sizeof(buffer), "%d",
              audio_data.chunk_size / audio_data.byte_rate);
  lv_label_set_text(track_duration, buffer);
  lv_obj_set_width(track_duration, OLED_WIDTH);

  lv_obj_align(track_duration, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_set_style_text_align(track_duration, LV_TEXT_ALIGN_CENTER, 0);

  // ===================================================
  for (uint8_t i = 0; i < 7; i++) {
    lv_obj_t *rect = lv_obj_create(player_screen);
    volume_bars[i] = rect;

    lv_obj_set_size(rect, 4, 2);
    lv_obj_set_pos(rect, OLED_WIDTH - 5 - 4, OLED_HEIGHT - 5 - 2 * i - 2 * i);

    lv_obj_set_style_border_width(rect, 0, 0);
    lv_obj_set_style_bg_color(rect, lv_color_white(), 0);
    lv_obj_set_style_radius(rect, 0, 0);
  }

  return player_screen;
}
