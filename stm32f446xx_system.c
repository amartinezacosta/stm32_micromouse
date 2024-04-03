#include <stm32f4xx.h>

#include "stm32f446xx_gpio.h"
#include "stm32f446xx_uart.h"
#include "stm32f446xx_tim.h"

uint32_t SystemCoreClock = 16000000;

void SystemInit(void)
{
  /*Initialize FPU*/
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

  /*Enable peripheral clocks*/
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

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

  stm32f446xx_uart_init(UART_0, &stm32f446xx_usart2_config);

  /* Initialize PWM */
  stm32f446xx_gpio_config_t stm32f446xx_pwm_gpio_config = {0};
  stm32f446xx_pwm_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_pwm_gpio_config.alt = GPIO_ALT_2;

  stm32f446xx_gpio_init(GPIOA_BASE,
    GPIO_PIN_6 | GPIO_PIN_7,
    &stm32f446xx_pwm_gpio_config);

  stm32f446xx_gpio_init(GPIOB_BASE,
    GPIO_PIN_6 | GPIO_PIN_7,
    &stm32f446xx_pwm_gpio_config);

  stm32f446xx_tim_pwm_config_t stm32f446xx_tim_pwm_config = {0};
  stm32f446xx_tim_pwm_config.pwm_mode = PWM_MODE_1;

  stm32f446xx_tim_pwm_init(TIM3_BASE, 
    TIM_CC_1, 
    &stm32f446xx_tim_pwm_config);
  stm32f446xx_tim_pwm_init(TIM3_BASE, 
    TIM_CC_2, 
    &stm32f446xx_tim_pwm_config);
  stm32f446xx_tim_pwm_init(TIM4_BASE, 
    TIM_CC_1, 
    &stm32f446xx_tim_pwm_config);
  stm32f446xx_tim_pwm_init(TIM4_BASE, 
    TIM_CC_2, 
    &stm32f446xx_tim_pwm_config);

  /* Initialize encoders */
  stm32f446xx_gpio_config_t stm32f446xx_enc_0_gpio_config = {0};
  stm32f446xx_enc_0_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_enc_0_gpio_config.alt = GPIO_ALT_1;

  stm32f446xx_gpio_config_t stm32f446xx_enc_1_gpio_config = {0};
  stm32f446xx_enc_1_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_enc_1_gpio_config.alt = GPIO_ALT_2;
  
  stm32f446xx_gpio_init(GPIOB_BASE,
    GPIO_PIN_8 | GPIO_PIN_9,
    &stm32f446xx_enc_0_gpio_config);

  stm32f446xx_gpio_init(GPIOA_BASE,
    GPIO_PIN_0 | GPIO_PIN_1,
    &stm32f446xx_enc_1_gpio_config);

  stm32f446xx_tim_enc_init(TIM2_BASE, 0);
  stm32f446xx_tim_enc_init(TIM5_BASE, 0);

  /*Initialize GPIO outputs/inputs*/

  /*Initialize ADC*/

  /*Initialize I2C*/
}

void SystemCoreClockUpdate(void)
{
  
}