#include "button.h"
#include "encoder.h"
#include "files_list.h"
#include "lvgl.h"
#include "usart_init.h"

#include "screens/router.h"

lv_obj_t *roller_main = NULL;

extern Files_list_t files_list;
extern Buttons_Set_t buttons_set;

uint32_t current;
char *current_track_name;

static void on_encoder_change(int32_t enc_delta) {
  current = lv_roller_get_selected(roller_main);
  int32_t new_sel = (int32_t)current + enc_delta;

  lv_roller_set_selected(roller_main, (uint32_t)new_sel, LV_ANIM_OFF);
}

static void on_click_handler(uint32_t press_delta) {
  if (press_delta > 50 && press_delta < 500) {
    current = lv_roller_get_selected(roller_main);
    current_track_name = files_list.items[current];
    transition_to_screen(PLAYER_SCREEN);
  }
}

lv_obj_t *create_main_screen(void) {
  clear_buttons_event_handlers();
  clear_enc_change_handler();

  set_enc_change_handler(on_encoder_change);
  Button_t *button = &buttons_set.buttons[0];
  set_button_onclick_handler(button, on_click_handler);

  lv_obj_t *screen_main = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(screen_main, 0, 0);

  roller_main = lv_roller_create(screen_main);

  lv_roller_set_options(roller_main, files_list.options_string,
                        LV_ROLLER_MODE_INFINITE);
  lv_obj_set_size(roller_main, 128, 128);
  lv_roller_set_visible_row_count(roller_main, 8);
  lv_obj_align(roller_main, LV_ALIGN_TOP_LEFT, 0, 0);

  return screen_main;
}
