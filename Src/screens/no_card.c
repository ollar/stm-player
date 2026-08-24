#include "button.h"
#include "lvgl.h"
#include "oled_sh1107.h"

extern Buttons_Set_t buttons_set;

static void no_card_onclick_handler(uint32_t press_delta) {
  NVIC_SystemReset();
}

lv_obj_t *create_no_card_screen(void) {
  Button_t *button = &buttons_set.buttons[0];
  set_button_onclick_handler(button, no_card_onclick_handler);

  lv_obj_t *no_card_screen = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(no_card_screen, 0, 0);

  lv_obj_t *label = lv_label_create(no_card_screen);
  lv_label_set_text(label, "Нет карты");
  lv_obj_set_width(label, OLED_WIDTH);

  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  return no_card_screen;
}
