#include "stm32f4xx_hal.h"

#include <stdarg.h>
#include <stdio.h> // для sprintf / snprintf

USART_HandleTypeDef huart1 = {0};

void usart1_init(void) {
  // 1. Включаем тактирование GPIOA и USART1
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART1_CLK_ENABLE();

  // 2. Настраиваем пины на альтернативную функцию AF7 (USART1)
  GPIO_InitTypeDef gpio = {0};

  // PA9  -> TX (передача)
  gpio.Pin = GPIO_PIN_9;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &gpio);

  // PA10 -> RX (приём)
  gpio.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOA, &gpio);

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  HAL_USART_Init(&huart1);
}

void hprintf(const char *str) {
  while (*str) {
    HAL_USART_Transmit(&huart1, (uint8_t *)str, 1, HAL_MAX_DELAY);
    str++;
  }
}

void hprintf_formatted(const char *fmt, ...) {
  char buffer[128]; // размер подберите под свои нужды
  va_list args;

  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args); // безопасное форматирование
  va_end(args);

  hprintf(buffer);
}
