#include "files_list.h"
#include "ff.h"
#include "lvgl/stdlib/lv_string.h"
#include "stm32f4xx_hal.h"
// #include "usart_init.h"
#include <stdint.h>

Files_list_t files_list = {0};

static Files_list_t *create_files_list(void) { files_list.size = 0; };

static HAL_StatusTypeDef push_item(char *item) {
  char *copy = lv_strdup(item);
  if (copy == NULL) {
    return HAL_ERROR;
  }
  files_list.items[files_list.size] = copy;

  uint8_t len = lv_strlen(copy);
  uint16_t options_string_len = lv_strlen(files_list.options_string);
  uint16_t pos = options_string_len;

  if (files_list.size > 0) {
    files_list.options_string[pos++] = '\n';
  }

  lv_memcpy(&files_list.options_string[pos++], copy, len);

  files_list.size++;

  return HAL_OK;
}

HAL_StatusTypeDef get_sd_files_list(void) {
  FRESULT res;
  DIR dir;
  FILINFO finfo;
  FATFS fs;

  res = f_mount(&fs, "", 1);

  if (res != FR_OK) {
    return HAL_ERROR;
  }

  create_files_list();

  res = f_opendir(&dir, "0:/");

  if (res != FR_OK) {
    return HAL_ERROR;
  }

  while (1) {
    res = f_readdir(&dir, &finfo);
    if (res != FR_OK || finfo.fname[0] == 0)
      break;

    size_t len = lv_strlen(finfo.fname);
    if (len < 4)
      continue;

    if (lv_strncmp(finfo.fname, ".", 1) == 0 ||
        lv_strncmp(finfo.fname, "..", 2) == 0 ||
        lv_strcmp(finfo.fname + len - 4, ".WAV") != 0) {
      continue;
    }

    push_item(finfo.fname);
  }

  // files_list.options_string[pos++] = '\0';   // TODO: check this

  f_closedir(&dir);

  return HAL_OK;
}
