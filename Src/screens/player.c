#include "lvgl.h"
#include "lvgl/widgets/lv_label.h"
#include "oled_sh1107.h"

lv_obj_t *create_no_card_screen(void) {
  lv_obj_t *screen = lv_obj_create(NULL);
  lv_obj_set_style_pad_all(screen, 0, 0);

  lv_obj_t *label = lv_label_create(screen);
  lv_label_set_text(label, "плеер");
  lv_obj_set_width(label, OLED_WIDTH);

  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

  return screen;
}
