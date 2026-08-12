#include "button.h"
#include "encoder.h"
#include "i2s_audio.h"
#include "lvgl.h"
#include "lvgl/widgets/lv_label.h"
#include "oled_sh1107.h"
#include "usart_init.h"

extern char *current_track_name;

uint8_t is_playing = 0;

lv_obj_t *create_player_screen(void) {
  clear_buttons_event_handlers();
  clear_enc_change_handler();

  lv_obj_t *player_screen = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(player_screen, 0, 0);

  hprintf_formatted("current_track_name %s\r\n", current_track_name);

  sd_read_file();

  lv_obj_t *label = lv_label_create(player_screen);
  lv_label_set_text(label, current_track_name);
  lv_obj_set_width(label, OLED_WIDTH);

  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  return player_screen;
}
