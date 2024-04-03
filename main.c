#include <stm32f4xx.h>

#include "stm32f446xx_uart.h"
#include "stm32f446xx_gpio.h"

#include "printf.h"

void _putchar(char character)
{
  stm32f446xx_uart_write(UART_0, 
    (const uint8_t*)&character, 1);
}

static inline void __delay_cycles(uint32_t cycles)
{
  while(--cycles) __ASM("nop");
}

int main(void)
{


  while(1)
  {
    //printf("Hello world, plus counting %i\r\n", index++);
  
  }
}