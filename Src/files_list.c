#include "files_list.h"
#include "ff.h"
#include "stm32f4xx_hal.h"
#include "usart_init.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Files_list_t files_list = {0};

static Files_list_t *create_files_list(void) { files_list.size = 0; };

static HAL_StatusTypeDef push_item(char *item) {
  char *copy = strdup(item);
  if (copy == NULL) {
    return HAL_ERROR;
  }
  files_list.items[files_list.size] = copy;
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

  // uint32_t pos = 0;

  while (1) {
    res = f_readdir(&dir, &finfo);
    if (res != FR_OK || finfo.fname[0] == 0)
      break;

    size_t len = strlen(finfo.fname);
    if (len < 4)
      continue;

    if (strncmp(finfo.fname, ".", 1) == 0 ||
        strncmp(finfo.fname, "..", 2) == 0 ||
        strcmp(finfo.fname + len - 4, ".WAV") != 0) {
      continue;
    }

    push_item(finfo.fname);

    // if (files_list.size > 1) {
    //   files_list.options_string[pos++] = '\n';
    // }
    //
    // memcpy(&files_list.options_string[pos], finfo.fname, len);
    //
    // pos += len;
  }
  // files_list.options_string[pos++] = '\0';

  get_files_list_options_string();
  f_closedir(&dir);

  return HAL_OK;
}

void get_files_list_options_string(void) {
  if (files_list.size == 0) {
    return;
  }

  // char *test = "test\0";
  // memcpy(&files_list.options_string[0], test, 5);

  uint32_t pos = 0;

  for (uint8_t i = 0; i < files_list.size; i++) {
    uint8_t len = strlen(files_list.items[i]);

    if (i > 0) {
      files_list.options_string[pos++] = '\n';
    }

    memcpy(&files_list.options_string[pos], files_list.items[i], len);

    pos += len;
  }
  files_list.options_string[pos++] = '\0';
}
