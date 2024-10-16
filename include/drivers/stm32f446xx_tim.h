#ifndef STM32F446XX_TIM_H_
#define STM32F446XX_TIM_H_

#include <stm32f446xx.h>
#include "stm32f446xx_isr.h"

#define TIM_1_PWM_FREQUENCY     10000
#define TIM_2_PWM_FREQUENCY     10000
#define TIM_3_PWM_FREQUENCY     10000
#define TIM_4_PWM_FREQUENCY     10000
#define TIM_5_PWM_FREQUENCY     10000
#define TIM_6_PWM_FREQUENCY     10000
#define TIM_7_PWM_FREQUENCY     10000
#define TIM_8_PWM_FREQUENCY     10000
#define TIM_9_PWM_FREQUENCY     10000
#define TIM_10_PWM_FREQUENCY    10000
#define TIM_11_PWM_FREQUENCY    10000

#define TIM_CC_1            0 
#define TIM_CC_2            1
#define TIM_CC_3            2
#define TIM_CC_4            3

typedef enum
{
  PWM_MODE_1 = 6,
  PWM_MODE_2
}pwm_mode_t;

typedef enum
{
  FILTER_0 = 0,
  FILTER_1
}encoder_filter_t;

typedef enum
{
  POLARITY_0 = 0,
  POLARITY_1,
}encoder_polarity_t;

#define TIM_CMSIS(address)    ((TIM_TypeDef*)address)
#define TIM_CC(address,cc)    (*((uint32_t*)(address + 0x34UL + (cc)*4UL)))

typedef struct
{
  uint32_t address;
  stm32f446xx_isr_t *isr;
  void(*callback)(void);
}stm32f446xx_tim_timer_t;

typedef struct
{
  pwm_mode_t pwm_mode;
}stm32f446xx_tim_pwm_config_t;

typedef struct
{
  encoder_filter_t filter;
  encoder_polarity_t polarity;
}stm32f446xx_tim_enc_config_t;

typedef struct
{
  uint32_t frequency;
  IRQn_Type irq;
  uint32_t prio;
}stm32f446xx_tim_timer_config_t;

typedef void(*tim_timer_callback_t)(void);

void stm32f446xx_tim_pwm_init(uint32_t const address, uint32_t const cc,
  stm32f446xx_tim_pwm_config_t const * const config);
void stm32f446xx_tim_enc_init(uint32_t const address,
  stm32f446xx_tim_enc_config_t const * const config);
void stm32f446xx_tim_timer_init(uint32_t const address,
  tim_timer_callback_t callback,
  stm32f446xx_tim_timer_config_t const * const config);
uint32_t stm32f446xx_tim_pwm_frequency(uint32_t address);
void stm32f446xx_tim_pwm_duty(uint32_t const address, 
  uint32_t const cc, 
  uint32_t const duty);
uint32_t stm32f446xx_tim_enc_count(uint32_t const address);

#endif