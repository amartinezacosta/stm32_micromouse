#include "devices/motor.h"

void motor_right_init(void)
{
  /*Initialize PWM drivers*/
  stm32f446xx_gpio_config_t stm32f446xx_pwm_gpio_config = {0};
  stm32f446xx_pwm_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_pwm_gpio_config.alt = GPIO_ALT_2;

  stm32f446xx_gpio_init(MOTOR_0_GPIO_BASE,
    MOTOR_0_PIN_0 | MOTOR_0_PIN_1,
    &stm32f446xx_pwm_gpio_config);

  stm32f446xx_tim_pwm_config_t stm32f446xx_tim_pwm_config = {0};
  stm32f446xx_tim_pwm_config.pwm_mode = PWM_MODE_1;

  stm32f446xx_tim_pwm_init(MOTOR_0_TIM_BASE, 
    TIM_CC_1, 
    &stm32f446xx_tim_pwm_config);
  stm32f446xx_tim_pwm_init(MOTOR_0_TIM_BASE, 
    TIM_CC_2, 
    &stm32f446xx_tim_pwm_config);

  /*Initialize TIM encoder drivers*/
  stm32f446xx_gpio_config_t stm32f446xx_enc_0_gpio_config = {0};
  stm32f446xx_enc_0_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_enc_0_gpio_config.alt = GPIO_ALT_1;
  
  stm32f446xx_gpio_init(MOTOR_0_GPIO_ENC_BASE,
    MOTOR_0_ENC_GPIO_PIN_0 | MOTOR_0_ENC_GPIO_PIN_1,
    &stm32f446xx_enc_0_gpio_config);

  stm32f446xx_tim_enc_init(MOTOR_0_TIM_ENC_BASE, 0);
}

void left_motor_init(void)
{
  /*Initialize GPIO drivers*/
  stm32f446xx_gpio_config_t stm32f446xx_pwm_gpio_config = {0};
  stm32f446xx_pwm_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_pwm_gpio_config.alt = GPIO_ALT_2;

  stm32f446xx_gpio_init(MOTOR_1_GPIO_BASE,
    MOTOR_1_PIN_0 | MOTOR_1_PIN_1,
    &stm32f446xx_pwm_gpio_config);

  /*Initialize TIM PWM drivers*/
  stm32f446xx_tim_pwm_config_t stm32f446xx_tim_pwm_config = {0};
  stm32f446xx_tim_pwm_config.pwm_mode = PWM_MODE_1;

  stm32f446xx_tim_pwm_init(MOTOR_1_TIM_BASE, 
    TIM_CC_1, 
    &stm32f446xx_tim_pwm_config);
  stm32f446xx_tim_pwm_init(MOTOR_1_TIM_BASE, 
    TIM_CC_2, 
    &stm32f446xx_tim_pwm_config);

  /*Initialize TIM encoder drivers*/
  stm32f446xx_gpio_config_t stm32f446xx_enc_1_gpio_config = {0};
  stm32f446xx_enc_1_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_enc_1_gpio_config.alt = GPIO_ALT_2;

  stm32f446xx_gpio_init(MOTOR_1_GPIO_ENC_BASE,
    MOTOR_1_ENC_GPIO_PIN_0 | MOTOR_1_ENC_GPIO_PIN_1,
    &stm32f446xx_enc_1_gpio_config);
  stm32f446xx_tim_enc_init(MOTOR_1_TIM_ENC_BASE, 0);
}

uint32_t motor_left_position(void)
{
  uint32_t count = stm32f446xx_tim_enc_count(MOTOR_0_TIM_ENC_BASE);
  return count;
}

uint32_t motor_right_position(void)
{
  uint32_t count = stm32f446xx_tim_enc_count(MOTOR_1_TIM_ENC_BASE);
  return count;
}

void motor_right_pwm_duty(uint32_t duty, uint32_t direction)
{
  if(direction)
  {
    stm32f446xx_tim_pwm_duty(MOTOR_0_TIM_BASE,
      TIM_CC_1, duty);
    stm32f446xx_tim_pwm_duty(MOTOR_0_TIM_BASE,
      TIM_CC_2, 0);
  }
  else
  {
    stm32f446xx_tim_pwm_duty(MOTOR_0_TIM_BASE,
      TIM_CC_1, 0);
    stm32f446xx_tim_pwm_duty(MOTOR_0_TIM_BASE,
      TIM_CC_2, duty);
  }
}

void motor_left_pwm_duty(uint32_t duty, uint32_t direction)
{
  if(direction)
  {
    stm32f446xx_tim_pwm_duty(MOTOR_1_TIM_BASE,
      TIM_CC_1, duty);
    stm32f446xx_tim_pwm_duty(MOTOR_1_TIM_BASE,
      TIM_CC_2, 0);
  }
  else
  {
    stm32f446xx_tim_pwm_duty(MOTOR_1_TIM_BASE,
      TIM_CC_1, 0);
    stm32f446xx_tim_pwm_duty(MOTOR_1_TIM_BASE,
      TIM_CC_2, duty);
  }
}