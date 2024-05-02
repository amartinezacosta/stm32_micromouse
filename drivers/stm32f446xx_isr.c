#include "drivers/stm32f446xx_isr.h"

//extern uint32_t __Vectors[STM32F446xx_VTABLE_SIZE];
extern void(*__VECTOR_TABLE[])(void);
uint32_t stm32f446xx_isr_vtable[STM32F446xx_VTABLE_SIZE] __attribute__(( 
  aligned(STM32F446xx_VTABLE_ALIGNMENT) ));

volatile stm32f446xx_isr_t *stm32f446xx_isr_events[STM32F446xx_VTABLE_SIZE];

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

void stm32f446xx_isr_register(stm32f446xx_isr_t * const event,
  void(*function)(void*), 
  void *args, 
  IRQn_Type irqn,
  uint32_t prio)
{
  event->function = function;
  event->args = args;
  event->irqn = irqn;
  event->prio = prio;

  uint32_t isr_index = (uint32_t)event->irqn + 16;
  stm32f446xx_isr_vtable[isr_index] = (uint32_t)&stm32f446xx_isr_dispatch;
  stm32f446xx_isr_events[isr_index] = event;

  /*Set IRQ priority*/
  NVIC_SetPriority(event->irqn, event->prio);
  /*Enable IRQ to CPU*/
  NVIC_EnableIRQ(event->irqn);
}

void stm32f446xx_isr_dispatch(void)
{
  uint32_t irqn = SCB->ICSR & 0xFF;
  volatile stm32f446xx_isr_t *event = stm32f446xx_isr_events[irqn];
  if(event->function)
  {
    event->function(event->args);
  }
}