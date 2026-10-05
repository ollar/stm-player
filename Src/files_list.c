#include "files_list.h"
#include "ff.h"
#include "lvgl.h"
#include "stm32f4xx_hal.h"
#include "usart_init.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Files_list_t files_list = {0};

static void create_files_list(void) {
  files_list.current = 0;
  files_list.capacity = 10;
  files_list.string_capacity = 100;
  uint8_t files_list_items_initial_size = files_list.capacity * sizeof(char *);
  uint8_t files_list_options_string_initial_size =
      files_list.string_capacity * sizeof(char *);

  for (uint8_t i = 0; i < files_list.size; i++) {
    free(files_list.items[i]);
  }

  free(files_list.items);
  free(files_list.options_string);

  files_list.items = malloc(files_list_items_initial_size);
  files_list.options_string = malloc(files_list_options_string_initial_size);

  files_list.size = 0;

  memset(files_list.items, 0, files_list_items_initial_size);
  memset(files_list.options_string, 0, files_list_options_string_initial_size);
};

static HAL_StatusTypeDef push_item(char *item) {
  char *copy = strdup(item);
  if (copy == NULL) {
    return HAL_ERROR;
  }

  if (files_list.size == files_list.capacity) {
    files_list.capacity = files_list.capacity * 2;
    files_list.items =
        realloc(files_list.items, files_list.capacity * sizeof(char *));
  }

  files_list.items[files_list.size] = copy;

  uint8_t len = strlen(item);
  uint16_t options_string_len = strlen(files_list.options_string);
  uint16_t pos = options_string_len;

  if ((options_string_len + len + 2) > files_list.string_capacity) {
    files_list.string_capacity *= 2;

    char *new_string_capacity =
        realloc(files_list.options_string, files_list.string_capacity);

    if (!new_string_capacity) {
      return HAL_ERROR;
    }

    files_list.options_string = new_string_capacity;
  }

  if (files_list.size > 0) {
    files_list.options_string[pos++] = '\n';
  }

  memcpy(files_list.options_string + pos, item, len);

  pos += len;

  files_list.options_string[pos] = '\0';

  files_list.size++;

  return HAL_OK;
}

HAL_StatusTypeDef get_sd_files_list(void) {
  FRESULT res;
  DIR dir;
  FILINFO finfo;

  create_files_list();

  res = f_opendir(&dir, "0:/");

  if (res != FR_OK) {
    return HAL_ERROR;
  }

  while (1) {
    res = f_readdir(&dir, &finfo);
    if (res != FR_OK || finfo.fname[0] == 0)
      break;

    size_t len = strlen(finfo.fname);
    if (len < 4)
      continue;

    if (strncmp(finfo.fname, ".", 1) == 0 ||
        strncmp(finfo.fname, "..", 2) == 0 ||
        strncmp(finfo.fname, "._", 2) == 0 || finfo.fsize < 10000 ||
        strcmp(finfo.fname + len - 4, ".wav") != 0) {
      continue;
    }

    push_item(finfo.fname);
  }

  f_closedir(&dir);

  return HAL_OK;
}

char *get_current_track_name(void) {
  return files_list.items[files_list.current];
};
