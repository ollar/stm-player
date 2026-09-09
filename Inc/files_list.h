#pragma once

#include "ffconf.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
  uint8_t size;
  uint16_t capacity;
  uint32_t string_capacity;
  uint8_t current;
  char **items;
  char *options_string;
} Files_list_t;

HAL_StatusTypeDef get_sd_files_list(void);
char *get_current_track_name(void);
