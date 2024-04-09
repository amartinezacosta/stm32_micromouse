#include <stm32f4xx.h>

#include "drivers/stm32f446xx_uart.h"
#include "drivers/stm32f446xx_gpio.h"

#include "printf.h"

// void _putchar(char character)
// {
//   stm32f446xx_uart_write(UART_0, 
//     (const uint8_t*)&character, 1);
// }

// static inline void __delay_cycles(uint32_t cycles)
// {
//   while(--cycles) __ASM("nop");
// }

// void hardware_init(void)
// {
//   /* Initialize USART2 */
//   stm32f446xx_gpio_config_t stm32f446xx_usart2_gpio_config = {0};
//   stm32f446xx_usart2_gpio_config.mode = GPIO_MODE_ALTERNATE;
//   stm32f446xx_usart2_gpio_config.alt = GPIO_ALT_7;

//   stm32f446xx_gpio_init(GPIOA_BASE,
//     GPIO_PIN_2 | GPIO_PIN_3, 
//     &stm32f446xx_usart2_gpio_config);

//   stm32f446xx_usart_config_t stm32f446xx_usart2_config = {0};
//   stm32f446xx_usart2_config.baudrate = 9600;
//   stm32f446xx_usart2_config.irqn = USART2_IRQn;

//   stm32f446xx_uart_init(UART_0, &stm32f446xx_usart2_config);

//   /* Initialize PWM */
//   stm32f446xx_gpio_config_t stm32f446xx_pwm_gpio_config = {0};
//   stm32f446xx_pwm_gpio_config.mode = GPIO_MODE_ALTERNATE;
//   stm32f446xx_pwm_gpio_config.alt = GPIO_ALT_2;

//   stm32f446xx_gpio_init(GPIOA_BASE,
//     GPIO_PIN_6 | GPIO_PIN_7,
//     &stm32f446xx_pwm_gpio_config);

//   stm32f446xx_gpio_init(GPIOB_BASE,
//     GPIO_PIN_6 | GPIO_PIN_7,
//     &stm32f446xx_pwm_gpio_config);

//   stm32f446xx_tim_pwm_config_t stm32f446xx_tim_pwm_config = {0};
//   stm32f446xx_tim_pwm_config.pwm_mode = PWM_MODE_1;

//   stm32f446xx_tim_pwm_init(TIM3_BASE, 
//     TIM_CC_1, 
//     &stm32f446xx_tim_pwm_config);
//   stm32f446xx_tim_pwm_init(TIM3_BASE, 
//     TIM_CC_2, 
//     &stm32f446xx_tim_pwm_config);
//   stm32f446xx_tim_pwm_init(TIM4_BASE, 
//     TIM_CC_1, 
//     &stm32f446xx_tim_pwm_config);
//   stm32f446xx_tim_pwm_init(TIM4_BASE, 
//     TIM_CC_2, 
//     &stm32f446xx_tim_pwm_config);

//   /* Initialize encoders */
//   stm32f446xx_gpio_config_t stm32f446xx_enc_0_gpio_config = {0};
//   stm32f446xx_enc_0_gpio_config.mode = GPIO_MODE_ALTERNATE;
//   stm32f446xx_enc_0_gpio_config.alt = GPIO_ALT_1;

//   stm32f446xx_gpio_config_t stm32f446xx_enc_1_gpio_config = {0};
//   stm32f446xx_enc_1_gpio_config.mode = GPIO_MODE_ALTERNATE;
//   stm32f446xx_enc_1_gpio_config.alt = GPIO_ALT_2;
  
//   stm32f446xx_gpio_init(GPIOB_BASE,
//     GPIO_PIN_8 | GPIO_PIN_9,
//     &stm32f446xx_enc_0_gpio_config);

//   stm32f446xx_gpio_init(GPIOA_BASE,
//     GPIO_PIN_0 | GPIO_PIN_1,
//     &stm32f446xx_enc_1_gpio_config);

//   stm32f446xx_tim_enc_init(TIM2_BASE, 0);
//   stm32f446xx_tim_enc_init(TIM5_BASE, 0);

//   /*Initialize GPIO outputs/inputs*/

//   /*Initialize ADC*/

//   /*Initialize I2C*/
// }

int main(void)
{
  while(1)
  {
    //printf("Hello world, plus counting %i\r\n", index++);
  
  }
}