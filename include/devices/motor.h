#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>
#include "drivers/stm32f446xx_tim.h"
#include "drivers/stm32f446xx_gpio.h"

#define MOTOR_0_TIM_BASE        TIM3_BASE
#define MOTOR_0_GPIO_BASE       GPIOA_BASE
#define MOTOR_1_TIM_BASE        TIM4_BASE
#define MOTOR_1_GPIO_BASE       GPIOB_BASE

#define MOTOR_0_PIN_0           GPIO_PIN_6
#define MOTOR_0_PIN_1           GPIO_PIN_7
#define MOTOR_1_PIN_0           GPIO_PIN_6
#define MOTOR_1_PIN_1           GPIO_PIN_7

#define MOTOR_0_TIM_ENC_BASE    TIM2_BASE
#define MOTOR_0_GPIO_ENC_BASE   GPIOB_BASE
#define MOTOR_1_TIM_ENC_BASE    TIM5_BASE
#define MOTOR_1_GPIO_ENC_BASE   GPIOA_BASE

#define MOTOR_0_ENC_GPIO_PIN_0  GPIO_PIN_8
#define MOTOR_0_ENC_GPIO_PIN_1  GPIO_PIN_9
#define MOTOR_1_ENC_GPIO_PIN_0  GPIO_PIN_0
#define MOTOR_1_ENC_GPIO_PIN_1  GPIO_PIN_1

#define MOTOR_DIR_CLOCKWISE     0
#define MOTOR_DIR_CCLOCKWISE    1

void motor_right_init(void);
void left_motor_init(void);
uint32_t motor_left_position(void);
uint32_t motor_right_position(void);
void motor_right_speed(uint32_t speed, uint32_t direction);
void motor_left_speed(uint32_t speed, uint32_t direction);



#endif