#include "stm32f446xx_gpio.h"

void stm32f446xx_gpio_init(const uint32_t address,
  const uint16_t pins,
  stm32f446xx_gpio_config_t * const config)
{
  for(uint8_t pin = 0; pin < GPIO_PIN_COUNT; pin++)
  {
    uint16_t mask = 1 << pin;
    if(pins & mask)
    {
      uint8_t pin_shift =  pin * 2;
      /* GPIO mode */ 
      GPIO_CMSIS(address)->MODER |= (config->mode << pin_shift);
      /*Output type*/
      GPIO_CMSIS(address)->OTYPER |= (config->otype << pin); 
      /*Speed type*/
      GPIO_CMSIS(address)->OSPEEDR |= (config->ospeed << pin_shift);
      /*Pull up-down*/
      GPIO_CMSIS(address)->PUPDR |= (config->pull << pin_shift);
      /*Alternate function*/
      GPIO_CMSIS(address)->AFR[pin >> 3UL] |= (config->alt << ((pin & 0x07U)*4));
    }
  }

  /*TODO: add ISR support*/
}

void stm32f446xx_gpio_write(const uint32_t address, 
  const uint16_t pin, const uint32_t state)
{
  if(state == GPIO_HIGH)
  { 
    GPIO_CMSIS(address)->BSRR |= pin;
  }
  else
  {
    GPIO_CMSIS(address)->BSRR |= 16 << pin;
  }
}

uint16_t stm32f446xx_gpio_read(const uint32_t address,
  const uint16_t pin)
{
  uint32_t value = GPIO_CMSIS(address)->IDR & pin;

  return value;
}

void stm32f446xx_gpio_toggle(const uint32_t address,
 const uint16_t pin)
{
  GPIO_CMSIS(address)->ODR ^= pin;
}
