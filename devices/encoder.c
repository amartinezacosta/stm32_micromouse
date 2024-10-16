#include "devices/encoder.h"

void encoder_right_init(void)
{
  /*Initialize TIM encoder drivers*/
  stm32f446xx_gpio_config_t stm32f446xx_enc_0_gpio_config = {0};
  stm32f446xx_enc_0_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_enc_0_gpio_config.alt = GPIO_ALT_1;
  
  stm32f446xx_gpio_init(GPIO_ENC_0_BASE,
    ENC_0_GPIO_PIN_0 | ENC_0_GPIO_PIN_1,
    &stm32f446xx_enc_0_gpio_config);

  stm32f446xx_tim_enc_init(TIM_ENC_0_BASE, 0);
}

void encoder_left_init(void)
{
  /*Initialize TIM encoder drivers*/
  stm32f446xx_gpio_config_t stm32f446xx_enc_1_gpio_config = {0};
  stm32f446xx_enc_1_gpio_config.mode = GPIO_MODE_ALTERNATE;
  stm32f446xx_enc_1_gpio_config.alt = GPIO_ALT_2;

  stm32f446xx_gpio_init(GPIO_ENC_1_BASE,
    ENC_1_GPIO_PIN_0 | ENC_1_GPIO_PIN_1,
    &stm32f446xx_enc_1_gpio_config);
  
  stm32f446xx_tim_enc_init(TIM_ENC_1_BASE, 0);
}

uint32_t encoder_right_read(void)
{
  uint32_t count = stm32f446xx_tim_enc_count(TIM_ENC_0_BASE);
  return count;
}

uint32_t encoder_left_read(void)
{
  uint32_t count = stm32f446xx_tim_enc_count(TIM_ENC_1_BASE);
  return count;
}