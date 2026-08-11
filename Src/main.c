#include "main.h"
#include "lv_port_disp.h"
#include "lvgl.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "usart_init.h"
#include <stdint.h>
#include <string.h>

#include "files_list.h"
#include "screens/main.h"
#include "screens/no_card.h"
#include "sd_spi.h"

#include "encoder.h"

uint64_t system_tick = 0;

extern lv_obj_t *screen_main;

static void SystemClock_Config(void);

int main(void) {
  /*
   * Initialize board
   * */
  HAL_Init();
  SystemClock_Config();
  usart1_init();
  encoder_init();

  /**
   * Initialize debugging led
   */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = GPIO_PIN_13;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOC, &gpio);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /**
   * Initialize SD card
   */
  SD_InitSPI();
  HAL_Delay(10);
  SD_InitDMA();

  /**
   * Initialize screen
   */
  lv_init();
  lv_tick_set_cb(HAL_GetTick);
  lv_port_disp_init();

  /**
   * Main program code
   */
  HAL_StatusTypeDef res = get_sd_files_list();

  lv_obj_t *no_card_screen = create_no_card_screen();
  create_main_screen();

  if (res != HAL_OK) {
    lv_screen_load(no_card_screen);
  } else {
    lv_screen_load(screen_main);
  }

  hprintf("mehe");

  while (1) {

    lv_timer_handler();
    encoder_handle_change();

    if (system_tick % 200 == 0) {
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }

    HAL_Delay(5);
  }

  return 0;
}

static void SystemClock_Config(void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  hprintf("SystemClock_Config\r\n");

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = 4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    hprintf("HAL_RCC_OscConfig\r\n");
  }

  // HAL_RCC_OscConfig(&RCC_OscInitStruct);
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
   * clocks dividers
   */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    hprintf("HAL_RCC_ClockConfig\r\n");
  }

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 25;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 246;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    hprintf("PLLI2S init failed\r\n");
  }
}
