#include "screens/player.h"
#include "button.h"
#include "encoder.h"
#include "files_list.h"
#include "i2s_audio.h"
#include "i2s_common.h"
#include "lvgl.h"
#include "oled_sh1107.h"
#include "screens/router.h"
#include "usart_init.h"

extern Audio_Data_t audio_data;
extern Buttons_Set_t buttons_set;
extern Files_list_t files_list;

static lv_obj_t *label = NULL;
static lv_obj_t *track_duration = NULL;
static const float volumes_table[7] = {0.0f,  0.01f, 0.06f, 0.25f,
                                       0.56f, 0.81f, 1.0f};
static lv_obj_t *volume_bars[7];
lv_obj_t *left_bar = {0};
lv_obj_t *right_bar = {0};
static uint8_t current_volume_ind = 5;
static uint8_t is_button_pressed = 0;
static uint8_t is_button_pressed_and_encoder_changed = 0;

Player_state_t player_state = {
    .is_playing = 0,
    .volume = 0.8f,
};

static uint8_t get_channel_level(uint32_t audio_peak) {
  return (uint64_t)audio_peak * 100 / SOUND_VOLUME_NORMALIZER;
}

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

  uint8_t left_level = get_channel_level(audio_data.audio_peak_left);
  uint8_t right_level = get_channel_level(audio_data.audio_peak_right);

  lv_memset(buffer, 0, sizeof(buffer));

  lv_snprintf(buffer, sizeof(buffer), "%04X\n%04X", audio_data.audio_buffer[0],
              audio_data.audio_buffer[4]);
  lv_label_set_text(left_bar, buffer);

  lv_snprintf(buffer, sizeof(buffer), "%04X\n%04X", audio_data.audio_buffer[2],
              audio_data.audio_buffer[6]);
  lv_label_set_text(right_bar, buffer);

  lv_obj_set_size(left_bar, lv_pct(50), lv_pct(left_level));
  lv_obj_set_size(right_bar, lv_pct(50), lv_pct(right_level));
}

static void player_onclick_handler(uint32_t press_delta) {
  if (is_button_pressed_and_encoder_changed) {
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
    player_state.is_playing = 0;
  }
}

static void player_onpress_handler(void) { is_button_pressed = 1; }

static void player_onrelease_handler(void) {
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

void play_next_track(void) {
  uint8_t files_list_current = files_list.current;
  files_list_current += 1;
  files_list.current = files_list_current % files_list.size;

  player_state.is_playing = 0;

  HAL_StatusTypeDef res = sd_read_file(get_current_track_name());

  if (res != HAL_OK) {
    fallback_to_nocard_screen();
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

  HAL_StatusTypeDef res = sd_read_file(current_track_name);

  if (res != HAL_OK) {
    return fallback_to_nocard_screen();
  }

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

  // ===================================================

  lv_obj_t *bars_wrapper = lv_obj_create(player_screen);
  lv_obj_set_size(bars_wrapper, OLED_WIDTH, OLED_HEIGHT / 3);
  lv_obj_align(bars_wrapper, LV_ALIGN_BOTTOM_MID, 0, 0);

  left_bar = lv_label_create(bars_wrapper);

  lv_obj_set_size(left_bar, lv_pct(50), lv_pct(100));
  lv_obj_align(left_bar, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_set_style_text_align(left_bar, LV_TEXT_ALIGN_RIGHT, 0);

  lv_obj_set_style_border_width(left_bar, 0, 0);
  lv_obj_set_style_bg_color(left_bar, lv_color_white(), 0);
  lv_obj_set_style_radius(left_bar, 0, 0);

  right_bar = lv_label_create(bars_wrapper);

  lv_obj_set_size(right_bar, lv_pct(50), lv_pct(100));
  lv_obj_align(right_bar, LV_ALIGN_BOTTOM_LEFT, lv_pct(50), 0);

  lv_obj_set_style_border_width(right_bar, 0, 0);
  lv_obj_set_style_bg_color(right_bar, lv_color_white(), 0);
  lv_obj_set_style_radius(right_bar, 0, 0);

  return player_screen;
}
