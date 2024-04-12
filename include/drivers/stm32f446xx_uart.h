#ifndef STM32F446XX_UART_H_
#define STM32F446XX_UART_H_

#include <stdint.h>
#include <stm32f4xx.h>

#include "drivers/stm32f446xx_isr.h"
#include "drivers/ringbuffer.h"

#define STM32F466XX_USART2_TX_BUFFER_SIZE     128
#define STM32F466XX_USART2_RX_BUFFER_SIZE     128

typedef struct
{
  uint32_t address;
  ringbuffer_t *tx_ringbuffer;
  ringbuffer_t *rx_ringbuffer;
  uint8_t *tx_buffer;
  uint8_t *rx_buffer;
  uint32_t tx_buffer_length;
  uint32_t rx_buffer_length;
  stm32f446xx_isr_t *isr;
}stm32f446xx_usart_t;

typedef struct
{
  uint32_t baudrate;
  IRQn_Type irqn;
}stm32f446xx_usart_config_t;

extern stm32f446xx_usart_t * const UART_0;

#define USART_CMSIS(address)   ((USART_TypeDef*)address)

void stm32f446xx_uart_init(stm32f446xx_usart_t * const self,
  stm32f446xx_usart_config_t *config);
uint32_t stm32f446xx_uart_write(stm32f446xx_usart_t * const self, 
  uint8_t const * const bytes,
  uint32_t length);
uint32_t stm32f446xx_uart_read(stm32f446xx_usart_t * const self,
  uint8_t * const bytes,
  uint32_t length);

#endif