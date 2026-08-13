#include "button.h"
#include "encoder.h"
#include "lvgl.h"

#include "screens/no_card.h"
#include "screens/player.h"
#include "screens/router.h"
#include "screens/tracklist.h"

lv_obj_t *prev_screen = NULL;
lv_obj_t *screen = NULL;

static void rerender_dummy_func(void) { ; };

void (*rerender_func)(void) = &rerender_dummy_func;

void set_rerender_function(void (*new_rerender_func)(void)) {
  rerender_func = new_rerender_func;
};

static void clear_rerender_func(void) { rerender_func = rerender_dummy_func; }

void transition_to_screen(SCREEN_NAMES_ENUM screen_name) {
  if (prev_screen) {
    lv_obj_del(prev_screen);
    prev_screen = NULL;
  }

  clear_buttons_event_handlers();
  clear_enc_change_handler();
  clear_rerender_func();

  switch (screen_name) {
  case NO_SD_CARD_SCREEN: {
    screen = create_no_card_screen();
    break;
  }

  case PLAYER_SCREEN: {
    screen = create_player_screen();
    break;
  }

  case TRACKLIST_SCREEN:
  default: {
    screen = create_main_screen();
    break;
  }
  }

  prev_screen = screen;

  lv_screen_load(screen);
}
