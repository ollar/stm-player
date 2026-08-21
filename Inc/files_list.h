#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>

// TODO: rewrite to malloc?
typedef struct {
  char *items[50];
  uint8_t size;
  uint8_t current;

  // char *options_string;
  // char options_string[512];
  char options_string[255 * 50 + 50 + 1]; // ??
} Files_list_t;

HAL_StatusTypeDef get_sd_files_list(void);
char *get_current_track_name(void);
