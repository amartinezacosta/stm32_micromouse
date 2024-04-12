#ifndef STM32F446XX_GPIO_H_
#define STM32F446XX_GPIO_H_

#include <stdint.h>
#include <stm32f4xx.h>

/*GPIO pins*/
#define GPIO_PIN_COUNT          16
#define GPIO_PIN_0              0x0001
#define GPIO_PIN_1              0x0002
#define GPIO_PIN_2              0x0004
#define GPIO_PIN_3              0x0008
#define GPIO_PIN_4              0x0010
#define GPIO_PIN_5              0x0020
#define GPIO_PIN_6              0x0040
#define GPIO_PIN_7              0x0080
#define GPIO_PIN_8              0x0100
#define GPIO_PIN_9              0x0200
#define GPIO_PIN_10             0x0400
#define GPIO_PIN_11             0x0800
#define GPIO_PIN_12             0x1000
#define GPIO_PIN_13             0x2000
#define GPIO_PIN_14             0x4000
#define GPIO_PIN_15             0x8000

/* GPIO states */
#define GPIO_LOW                0UL
#define GPIO_HIGH               1UL

/*Output port mode */
#define GPIO_MODE_INPUT         0UL
#define GPIO_MODE_OUTPUT        1UL
#define GPIO_MODE_ALTERNATE     2UL
#define GPIO_MODE_ANALOG        3UL

/*Output output type*/
#define  GPIO_OUTPUT_TYPE_PP    0UL
#define GPIO_OUTPUT_TYPE_OD     1UL

/*Output speed*/
#define GPIO_SPEED_LOW          0UL
#define GPIO_SPEED_MEDIUM       1UL
#define GPIO_SPEED_FAST         2UL
#define GPIO_SPEED_HIGH         3UL

/*Pull-up, pull-down*/
#define GPIO_PULL_DISABLE       0UL
#define GPIO_PULL_UP            1UL
#define GPIO_PULL_DOWN          2UL

/*Alternate function*/
#define GPIO_ALT_0              0UL
#define GPIO_ALT_1              1UL
#define GPIO_ALT_2              2UL
#define GPIO_ALT_3              3UL
#define GPIO_ALT_4              4UL
#define GPIO_ALT_5              5UL
#define GPIO_ALT_6              6UL
#define GPIO_ALT_7              7UL
#define GPIO_ALT_8              8UL
#define GPIO_ALT_9              9UL
#define GPIO_ALT_10             10UL
#define GPIO_ALT_11             11UL
#define GPIO_ALT_12             12UL
#define GPIO_ALT_13             13UL
#define GPIO_ALT_14             14UL
#define GPIO_ALT_15             15UL


#define GPIO_CMSIS(address)   ((GPIO_TypeDef*)address)

typedef struct
{
  uint32_t mode;
  uint32_t otype;
  uint32_t ospeed;
  uint32_t pull;
  uint32_t alt;
}stm32f446xx_gpio_config_t;

void stm32f446xx_gpio_init(const uint32_t address,
  const uint16_t pins,
  stm32f446xx_gpio_config_t * const config);
void stm32f446xx_gpio_write(const uint32_t address, 
  const uint16_t pin, const uint32_t state);
uint16_t stm32f446xx_gpio_read(const uint32_t address, const uint16_t pins);
void stm32f446xx_gpio_toggle(const uint32_t address, const uint16_t pins);

#endif