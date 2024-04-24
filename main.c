#include "devices/motor.h"
#include "devices/logger.h"
#include "drivers/stm32f446xx_tim.h"
#include "printf.h"

void systick_control(void);

void __delay_cycles(uint32_t cycles)
{
  while(--cycles) __asm("nop");
}

stm32f446xx_isr_t stm32f446xx_tim9_isr;
stm32f446xx_tim_timer_t stm32f446xx_tim_9 = 
{
  .address = TIM9_BASE,
  .isr = &stm32f446xx_tim9_isr,
  .callback = &systick_control
};

uint32_t left_motor_encoder = 0;
uint32_t right_motor_encoder = 0;

void systick_control(void)
{
  /* Update system variables */
  left_motor_encoder = motor_left_position();
  right_motor_encoder = motor_right_position();

  /* Wake up task for motor control */
}

int main(void)
{
  /* Initialize motors */
  left_motor_init();
  motor_right_init();

  /* Initialize logger */
  logger_init();

  /* Initialize systems control SysTick*/
  stm32f446xx_tim_timer_config_t stm32f446xx_timer_9_config = 
  {
    .frequency = 500,
    .irq = TIM1_BRK_TIM9_IRQn
  };

  stm32f446xx_tim_timer_init(&stm32f446xx_tim_9, 
    &stm32f446xx_timer_9_config);

  while(1)
  {
    printf("%i,%i\r\n", left_motor_encoder, right_motor_encoder);
    __delay_cycles(16000);
  }
}