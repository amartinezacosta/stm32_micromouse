#include "devices/logger.h"
#include "drivers/stm32f446xx_uart.h"
#include "drivers/stm32f446xx_gpio.h"
#include "printf.h"
#include <stdarg.h>

uint8_t stm32f446xx_usart2_tx_buffer[STM32F466XX_USART2_TX_BUFFER_SIZE];
uint8_t stm32f446xx_usart2_rx_buffer[STM32F466XX_USART2_RX_BUFFER_SIZE];

ringbuffer_t stm32f446xx_usart2_tx_ringbuffer;
ringbuffer_t stm32f446xx_usart2_rx_ringbuffer;

stm32f446xx_usart_t stm32f446xx_usart_2 = 
{
  .address = USART2_BASE,
  .rx_ringbuffer = &stm32f446xx_usart2_rx_ringbuffer,
  .tx_ringbuffer = &stm32f446xx_usart2_tx_ringbuffer,
  .tx_buffer = &stm32f446xx_usart2_tx_buffer[0],
  .rx_buffer = &stm32f446xx_usart2_rx_buffer[0],
  .tx_buffer_length = STM32F466XX_USART2_TX_BUFFER_SIZE,
  .rx_buffer_length = STM32F466XX_USART2_RX_BUFFER_SIZE
};

static const char *levels[] = 
{
  "DEBUG" ,"INFO", "WARN", "ERROR"
};

static const char *colors[] = 
{
  "","","",""
};

void _putchar(char character)
{
  stm32f446xx_uart_write(&stm32f446xx_usart_2,
    (const uint8_t * const)&character, 1);
}

void logger_init(void)
{
  /* Initialize USART2 */
  stm32f446xx_gpio_config_t stm32f446xx_usart2_gpio_config = {0};
  stm32f446xx_usart2_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_usart2_gpio_config.alt = GPIO_ALT_7;

  stm32f446xx_gpio_init(GPIOA_BASE,
    GPIO_PIN_2 | GPIO_PIN_3, 
    &stm32f446xx_usart2_gpio_config);

  stm32f446xx_usart_config_t stm32f446xx_usart2_config = {0};
  stm32f446xx_usart2_config.baudrate = 9600;
  stm32f446xx_usart2_config.irqn = USART2_IRQn;
  stm32f446xx_usart2_config.prio = 2;

  stm32f446xx_uart_init(&stm32f446xx_usart_2, &stm32f446xx_usart2_config);
}

// void logger_printf(uint32_t level,
//   const char *fstr, ...)
// {
//   va_list valist;
//   va_start(valist, fstr);
//   printf("%s%s: \x1B[0m", 
//     colors[level],
//     levels[level]);
//   printf(fstr, valist);
//   printf("\r\n");
//   va_end(valist);
// }