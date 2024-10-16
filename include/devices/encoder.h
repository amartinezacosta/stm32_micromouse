#ifndef ENCODER_H_
#define ENCODER_H_

#include "drivers/stm32f446xx_tim.h"
#include "drivers/stm32f446xx_gpio.h"

#define TIM_ENC_0_BASE    TIM2_BASE
#define GPIO_ENC_0_BASE   GPIOB_BASE
#define TIM_ENC_1_BASE    TIM5_BASE
#define GPIO_ENC_1_BASE   GPIOA_BASE

#define ENC_0_GPIO_PIN_0  GPIO_PIN_8
#define ENC_0_GPIO_PIN_1  GPIO_PIN_9
#define ENC_1_GPIO_PIN_0  GPIO_PIN_0
#define ENC_1_GPIO_PIN_1  GPIO_PIN_1

void encoder_right_init(void);
void encoder_left_init(void);
uint32_t encoder_right_read(void);
uint32_t encoder_left_read(void);

#endif