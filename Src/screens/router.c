#include "lvgl.h"

#include "screens/no_card.h"
#include "screens/player.h"
#include "screens/router.h"
#include "screens/tracklist.h"

void transition_to_screen(SCREEN_NAMES_ENUM screen_name) {
  lv_obj_t *screen = {0};

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

  lv_screen_load(screen);
}
