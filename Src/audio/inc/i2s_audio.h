#pragma once

#include "stm32f4xx_hal.h"

HAL_StatusTypeDef sd_read_file(char *);
HAL_StatusTypeDef sd_close_file(void);
