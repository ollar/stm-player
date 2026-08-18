/**
 * @file lv_port_disp_template.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable
 * content*/
#include "lvgl/display/lv_display.h"
#include <string.h>
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "oled_sh1107.h"
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define BYTE_PER_PIXEL                                                         \
  (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_I1)) /*will be 2 for RGB565 */
#define PALETTE_SIZE 8

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t *disp, const lv_area_t *area,
                       uint8_t *px_map);

/**********************
 *  STATIC VARIABLES
 **********************/

extern uint8_t framebuffer[OLED_BUFFER_SIZE];
uint8_t lvgl_buffer[LVGL_BUFFER_SIZE] = {0};
extern const lv_font_t ubuntu_mono;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void) {
  /*-------------------------
   * Initialize your display
   * -----------------------*/
  disp_init();
  memset(lvgl_buffer, 0, LVGL_BUFFER_SIZE);

  /*------------------------------------
   * Create a display and set a flush_cb
   * -----------------------------------*/
  lv_display_t *disp = lv_display_create(OLED_HEIGHT, OLED_WIDTH);
  // lv_display_set_rotation(NULL, LV_DISPLAY_ROTATION_270);
  lv_display_set_color_format(disp, LV_COLOR_FORMAT_I1);
  lv_theme_t *th = lv_theme_mono_init(disp, true, LV_FONT_DEFAULT);
  lv_display_set_theme(disp, th);
  lv_display_set_flush_cb(disp, disp_flush);

  /* Example 1
   * One buffer for partial rendering*/
  lv_display_set_buffers(disp, lvgl_buffer, NULL, sizeof(lvgl_buffer),
                         LV_DISPLAY_RENDER_MODE_FULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void) { OLED_Init(); }

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called
 * by LVGL
 */
void disp_enable_update(void) { disp_flush_enabled = true; }

/* Disable updating the screen (the flushing process) when disp_flush() is
 * called by LVGL
 */
void disp_disable_update(void) { disp_flush_enabled = false; }

static void convert_lvgl_to_oled_90cw(const uint8_t *src, uint8_t *dst,
                                      uint32_t w, uint32_t h) {
  const uint32_t src_stride = (w + 7) / 8;

  memset(dst, 0, w * ((h + 7) / 8));

  for (uint32_t y = 0; y < h; y++) {
    for (uint32_t x = 0; x < w; x++) {
      uint8_t src_byte = src[y * src_stride + x / 8];
      uint8_t src_bit = 7 - (x & 7);
      uint8_t pixel = (src_byte >> src_bit) & 1;

      uint32_t oled_x = h - 1 - y;
      uint32_t oled_y = x;

      uint32_t page = oled_y / 8;
      uint32_t bit = oled_y % 8;

      if (pixel)
        dst[page * w + oled_x] |= (1 << bit);
      else
        dst[page * w + oled_x] &= ~(1 << bit);
    }
  }
}

static void convert_lvgl_to_oled_90ccw(const uint8_t *src, uint8_t *dst,
                                       uint32_t w, uint32_t h) {
  const uint32_t src_stride = (w + 7) / 8;

  memset(dst, 0, w * ((h + 7) / 8));

  for (uint32_t y = 0; y < h; y++) {
    for (uint32_t x = 0; x < w; x++) {
      uint8_t src_byte = src[y * src_stride + x / 8];
      uint8_t src_bit = 7 - (x & 7);
      uint8_t pixel = (src_byte >> src_bit) & 1;

      uint32_t oled_x = y;
      uint32_t oled_y = w - 1 - x;

      uint32_t page = oled_y / 8;
      uint32_t bit = oled_y & 7;

      if (pixel)
        dst[page * w + oled_x] |= (1 << bit);
      else
        dst[page * w + oled_x] &= ~(1 << bit);
    }
  }
}

static void convert_lvgl_to_oled(const uint8_t *src, uint8_t *dst, uint32_t w,
                                 uint32_t h) {
  uint32_t src_stride = w / 8; // 16 байт на строку в LVGL I1
  for (uint32_t y = 0; y < h; y++) {
    uint32_t page = y / 8;
    uint32_t bit = y % 8;
    for (uint32_t x = 0; x < w; x++) {
      uint8_t src_byte = src[y * src_stride + x / 8];
      uint8_t src_bit = 7 - (x % 8); // LVGL: MSB = левый пиксель
      uint8_t pixel = (src_byte >> src_bit) & 1;
      if (pixel)
        dst[page * w + x] |= (1 << bit); // OLED: bit0 = верх в page
      else
        dst[page * w + x] &= ~(1 << bit);
    }
  }
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be
 copied
 * to `area` on the display. You can use DMA or any hardware acceleration to
 do
 * this operation in the background but 'lv_display_flush_ready()' has to be
 * called when it's finished.*/
static void disp_flush(lv_display_t *disp, const lv_area_t *area,
                       uint8_t *px_map) {
  convert_lvgl_to_oled_90ccw(px_map + PALETTE_SIZE, framebuffer, OLED_WIDTH,
                             OLED_HEIGHT);
  OLED_Update();
  lv_display_flush_ready(disp);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
