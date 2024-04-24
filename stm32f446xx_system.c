#include <stm32f4xx.h>

uint32_t SystemCoreClock = 16000000;

void SystemInit(void)
{
  /*Initialize FPU*/
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

  /*TODO: Intialize system clock*/

  /*Enable peripheral clocks*/
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
  RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
}

void SystemCoreClockUpdate(void)
{
  
}