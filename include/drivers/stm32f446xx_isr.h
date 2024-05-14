#ifndef STM32F446XX_ISR_H_
#define STM32F446XX_ISR_H_

#include <stm32f446xx.h>

#define STM32F446xx_VTABLE_SIZE       113
#define STM32F446xx_VTABLE_ALIGNMENT  128

typedef struct
{
  void (*function)(void(*)(void),uint32_t);
  void (*callback)(void);
  uint32_t address;
}stm32f446xx_isr_t;

void stm32f446xx_isr_vtable_init(void);
void stm32f446xx_isr_register(void(*function)(void*), 
  void (*callback)(void),
  uint32_t address, 
  IRQn_Type irqn,
  uint32_t prio);

#endif