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
typedef enum
{
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT,
  GPIO_MODE_ALTERNATE,
  GPIO_MODE_ANALOG
}gpio_mode_t;

/*Output output type*/
typedef enum
{
  GPIO_OUTPUT_TYPE_PP = 0,
  GPIO_OUTPUT_TYPE_OD
}gpio_otype_t;

/*Output speed*/
typedef enum
{
  GPIO_SPEED_LOW = 0,
  GPIO_SPEED_MEDIUM,
  GPIO_SPEED_FAST,
  GPIO_SPEED_HIGH
}gpio_ospeed_t;

/*Pull-up, pull-down*/
typedef enum
{
  GPIO_PULL_DISABLE,
  GPIO_PULL_UP,
  GPIO_PULL_DOWN
}gpio_pull_t;

/*Alternate function*/
typedef enum
{
  GPIO_ALT_0 = 0,
  GPIO_ALT_1,
  GPIO_ALT_2,
  GPIO_ALT_3,
  GPIO_ALT_4,
  GPIO_ALT_5,
  GPIO_ALT_6,
  GPIO_ALT_7,
  GPIO_ALT_8,
  GPIO_ALT_9,
  GPIO_ALT_10,
  GPIO_ALT_11,
  GPIO_ALT_12,
  GPIO_ALT_13,
  GPIO_ALT_14,
  GPIO_ALT_15
}gpio_alt_t;

#define GPIO_CMSIS(address)   ((GPIO_TypeDef*)address)

typedef struct
{
  gpio_mode_t mode;
  gpio_otype_t otype;
  gpio_ospeed_t ospeed;
  gpio_pull_t pull;
  gpio_alt_t alt;
}stm32f446xx_gpio_config_t;

void stm32f446xx_gpio_init(const uint32_t address,
  const uint16_t pins,
  stm32f446xx_gpio_config_t * const config);
void stm32f446xx_gpio_write(const uint32_t address, 
  const uint16_t pin, const uint32_t state);
uint16_t stm32f446xx_gpio_read(const uint32_t address, const uint16_t pins);
void stm32f446xx_gpio_toggle(const uint32_t address, const uint16_t pins);

#endif