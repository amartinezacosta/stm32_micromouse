#include "drivers/stm32f446xx_isr.h"

//extern uint32_t __Vectors[STM32F446xx_VTABLE_SIZE];
extern void(*__VECTOR_TABLE[])(void);
uint32_t stm32f446xx_isr_vtable[STM32F446xx_VTABLE_SIZE] __attribute__(( 
  aligned(STM32F446xx_VTABLE_ALIGNMENT) ));

volatile stm32f446xx_isr_t stm32f446xx_isr_events[STM32F446xx_VTABLE_SIZE];

void stm32f446xx_isr_dispatch(void);

void stm32f446xx_isr_vtable_init(void)
{
  /*Copy vector table from flash to ram*/
  for(uint32_t i = 0; i < STM32F446xx_VTABLE_SIZE; i++)
  {
    stm32f446xx_isr_vtable[i] = (uint32_t)__VECTOR_TABLE[i];
  }

  __disable_irq();
  SCB->VTOR = (uint32_t)&stm32f446xx_isr_vtable;
  __DSB();
  __enable_irq();
}

void stm32f446xx_isr_register(void(*function)(void*), 
  void (*callback)(void),
  uint32_t address, 
  IRQn_Type irqn,
  uint32_t prio)
{
  uint32_t isr_index = (uint32_t)irqn + 16;
  stm32f446xx_isr_vtable[isr_index] = (uint32_t)&stm32f446xx_isr_dispatch;
  
  volatile stm32f446xx_isr_t *event = &stm32f446xx_isr_events[isr_index];
  event->function = function;
  event->callback = callback;
  event->address = address;

  /*Set IRQ priority*/
  NVIC_SetPriority(irqn, prio);
  /*Enable IRQ to CPU*/
  NVIC_EnableIRQ(irqn);
}

void stm32f446xx_isr_dispatch(void)
{
  uint32_t irqn = SCB->ICSR & 0xFF;
  volatile stm32f446xx_isr_t *event = &stm32f446xx_isr_events[irqn];
  if(event->function)
  {
    void (*callback)(void) = event->callback;
    uint32_t address = event->address;
    event->function(callback, address);
  }
}