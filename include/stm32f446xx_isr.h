#ifndef STM32F446XX_ISR_H_
#define STM32F446XX_ISR_H_

#include <stm32f446xx.h>

#define STM32F446xx_VTABLE_SIZE       113
#define STM32F446xx_VTABLE_ALIGNMENT  128

typedef struct
{
  void (*function)(void*);
  void * args;
  IRQn_Type irqn;
}stm32f446xx_isr_t;

void stm32f446xx_isr_vtable_init(void);
void stm32f446xx_isr_register(stm32f446xx_isr_t * const event,
  void(*function)(void*), 
  void *args, 
  IRQn_Type irqn);

#endif