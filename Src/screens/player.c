#include "button.h"
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
extern uint8_t is_playing;
extern Buttons_Set_t buttons_set;

static lv_obj_t *track_duration = NULL;

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
    is_playing = !is_playing;
  }
}

lv_obj_t *create_player_screen(void) {
  set_rerender_function(rerender_player);
  Button_t *button = &buttons_set.buttons[0];
  set_button_onclick_handler(button, player_onclick_handler);

  lv_obj_t *player_screen = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(player_screen, 0, 0);

  hprintf_formatted("current_track_name %s\r\n", current_track_name);

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
