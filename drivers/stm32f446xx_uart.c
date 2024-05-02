#include "drivers/stm32f446xx_uart.h"

void stm32f446xx_usart_handler(void *args);

void stm32f446xx_uart_init(stm32f446xx_usart_t * const self,
  stm32f446xx_usart_config_t *config)
{
  /* TODO: add stop, data, parity and other parameters */
  /* TODO: Add UART clock division table */
  USART_CMSIS(self->address)->BRR = (104 << USART_BRR_DIV_Mantissa_Pos) |
                                    (3 << USART_BRR_DIV_Fraction_Pos);
  USART_CMSIS(self->address)->CR1 |= (USART_CR1_UE |
                                      USART_CR1_RE |
                                      USART_CR1_TE);
  /*Enabled TXEIE and RXNEIE interrupts*/
  USART_CMSIS(self->address)->CR1 |=  USART_CR1_RXNEIE;

  /*Intialize ringbuffers*/
  ringbuffer_init(self->tx_ringbuffer, 
    self->tx_buffer,
    self->tx_buffer_length);
  ringbuffer_init(self->rx_ringbuffer, 
    self->rx_buffer,
    self->rx_buffer_length);

  /*Register ISR event*/
  stm32f446xx_isr_register(self->isr, stm32f446xx_usart_handler,
    self, config->irqn, config->prio);
}

uint32_t stm32f446xx_uart_write(stm32f446xx_usart_t * const self, 
  uint8_t const * bytes,
  uint32_t length)
{
  uint8_t c;
  /*Wait until there is space on the ringbuffer*/
  uint32_t space;
  do
  {
    space = ringbuffer_space(self->tx_ringbuffer);
  }while(space < length);

  /*Write bytes to ringbuffer*/
  for(uint32_t i = 0; i < length; i++)
  {
    ringbuffer_write(self->tx_ringbuffer, bytes[i]);
  }

  /*Place first byte on USART and wait for interrupt */
  if(USART_CMSIS(self->address)->SR & USART_SR_TXE)
  {
    ringbuffer_read(self->tx_ringbuffer, &c);
    USART_CMSIS(self->address)->DR = c;
  }
  
  if(!(USART_CMSIS(self->address)->CR1 & USART_CR1_TCIE))
  {
    USART_CMSIS(self->address)->CR1 |= USART_CR1_TCIE;
  }

  return 0;
}

uint32_t stm32f446xx_uart_read(stm32f446xx_usart_t * const self,
  uint8_t * bytes,
  uint32_t length)
{
  uint32_t space;
  do
  {
    space = ringbuffer_space(self->rx_ringbuffer);
  }while(space < length);

  for(uint32_t i = 0; i < length; i++)
  {
    ringbuffer_read(self->rx_ringbuffer, &bytes[i]);
  }

  return 0;
}

void stm32f446xx_usart_handler(void *args)
{
  stm32f446xx_usart_t *self = (stm32f446xx_usart_t*)args;
  uint32_t status = USART_CMSIS(self->address)->SR;

  uint8_t c;
  if(status & USART_SR_TC)
  {
    if(ringbuffer_read(self->tx_ringbuffer, &c))
    {
      USART_CMSIS(self->address)->DR = c;
    }
    else
    {
      USART_CMSIS(self->address)->SR &= ~USART_SR_TC;
    }
  }
  
  if(status & USART_SR_RXNE)
  {
    c = USART_CMSIS(self->address)->DR;
    ringbuffer_write(self->rx_ringbuffer, c);
  }
}