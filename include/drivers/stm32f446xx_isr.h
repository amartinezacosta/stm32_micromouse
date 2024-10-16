#ifndef STM32F446XX_ISR_H_
#define STM32F446XX_ISR_H_

#include <stm32f446xx.h>

#define CORTEX_M_ISR_COUNT            16
#define STM32F446xx_VTABLE_SIZE       113
#define STM32F446xx_VTABLE_ALIGNMENT  256

typedef void(*isr_handler_t)(void*,uint32_t);

typedef struct
{
  isr_handler_t isr_handler;
  void *args;
  uint32_t address;
}stm32f446xx_isr_t;

void stm32f446xx_isr_vtable_init(void);
void stm32f446xx_isr_register(isr_handler_t isr_handler, 
  void *args,
  uint32_t address, 
  IRQn_Type irqn,
  uint32_t prio);

#endif