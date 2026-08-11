#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
  char *items[50];
  uint8_t size;
  // char *options_string;
  char options_string[512];
  // char options_string[];
} Files_list_t;

HAL_StatusTypeDef get_sd_files_list(void);
static void get_files_list_options_string(void);
