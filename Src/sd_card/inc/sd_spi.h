#include "stm32f4xx_hal.h"
#include <stdint.h>

#define SD_CARD_PORT GPIOB
#define SD_CS_PIN GPIO_PIN_12
#define SD_SCK_PIN GPIO_PIN_13
#define SD_MISO_PIN GPIO_PIN_14
#define SD_MOSI_PIN GPIO_PIN_15

void SD_InitSPI(void);
void SD_InitDMA(void);
void SD_Increase_Speed(void);
