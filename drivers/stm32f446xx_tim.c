#include "drivers/stm32f446xx_tim.h"

void stm32f446_tim_timer_handler(void *args);

void stm32f446xx_tim_pwm_init(uint32_t const address, uint32_t const cc,
  stm32f446xx_tim_pwm_config_t const * const config)
{
  TIM_CMSIS(address)->CR1 |= TIM_CR1_DIR;

  /*CC PWM mode select*/
  switch(cc)
  {
    case TIM_CC_1:
      TIM_CMSIS(address)->CCMR1 |= (config->pwm_mode << TIM_CCMR1_OC1M_Pos);
      break;
    case TIM_CC_2:
      TIM_CMSIS(address)->CCMR1 |= (config->pwm_mode << TIM_CCMR1_OC2M_Pos);
      break;
    case TIM_CC_3:
      TIM_CMSIS(address)->CCMR2 |= (config->pwm_mode << TIM_CCMR2_OC3M_Pos);
      break;
    case TIM_CC_4:
      TIM_CMSIS(address)->CCMR2 |= (config->pwm_mode << TIM_CCMR2_OC4M_Pos);
      break;
  }

  TIM_CMSIS(address)->CCER |= 1 << (cc*4UL);
  /* PWM frequency */
  uint32_t frequency = stm32f446xx_tim_pwm_frequency(address);
  TIM_CMSIS(address)->ARR = SystemCoreClock / (frequency - 1);
  /* Set duty cycle to 0 */
  TIM_CC(address, cc) = 0;

  /*Enable TIM*/
  TIM_CMSIS(address)->CR1 |= TIM_CR1_CEN;
}

void stm32f446xx_tim_pwm_duty(uint32_t const address, 
  uint32_t const cc, 
  uint32_t duty)
{
  TIM_CC(address, cc) = duty;
}

uint32_t stm32f446xx_tim_pwm_frequency(uint32_t const address)
{
  uint32_t frequency;
  switch(address)
  {
    case TIM1_BASE:
      frequency = TIM_1_PWM_FREQUENCY;
      break;
    case TIM2_BASE:
      frequency = TIM_2_PWM_FREQUENCY;
      break;
    case TIM3_BASE:
      frequency = TIM_3_PWM_FREQUENCY;
      break;
    case TIM4_BASE:
      frequency = TIM_4_PWM_FREQUENCY;
      break;
    case TIM5_BASE:
      frequency = TIM_5_PWM_FREQUENCY;
      break;
    case TIM6_BASE:
      frequency = TIM_6_PWM_FREQUENCY;
      break;
    case TIM7_BASE:
      frequency = TIM_7_PWM_FREQUENCY;
      break;
    case TIM8_BASE:
      frequency = TIM_8_PWM_FREQUENCY;
      break;
    case TIM9_BASE:
      frequency = TIM_9_PWM_FREQUENCY;
      break;
    case TIM10_BASE:
      frequency = TIM_10_PWM_FREQUENCY;
      break;
    case TIM11_BASE:
      frequency = TIM_11_PWM_FREQUENCY;
      break;
    default:
      frequency = 0;
      break;
  }

  return frequency;
}

void stm32f446xx_tim_enc_init(uint32_t const address,
  stm32f446xx_tim_enc_config_t const * const config)
{
  /* Enable counter */
  TIM_CMSIS(address)->CR1 |= TIM_CR1_CEN;

  /* Set encoder interface mode. Write SMS=011 to count on both edges */
  TIM_CMSIS(address)->SMCR |= (3UL << TIM_SMCR_SMS_Pos);
  /* Set CC1 to input TI1, and CC2 to input TI2*/
  TIM_CMSIS(address)->CCMR1 |= (TIM_CCMR1_CC1S_0 |
                                      TIM_CCMR1_CC2S_0);
  /* Select TI1 and TI2 polarity */
  /* TODO: Add polarity interface */
  TIM_CMSIS(address)->CCER |= TIM_CCER_CC1P;
  /* Set counter limit and count values*/
  TIM_CMSIS(address)->ARR = 0xFFFFFFFF;
  TIM_CMSIS(address)->CNT = 0x00000000;
}

uint32_t stm32f446xx_tim_enc_count(uint32_t const address)
{
  uint32_t count = TIM_CMSIS(address)->CNT;
  return count;
}

void stm32f446xx_tim_timer_init(stm32f446xx_tim_timer_t * const self,
  stm32f446xx_tim_timer_config_t const * const config)
{
  self->callback = config->callback;

  /* Set timer frequency */
  TIM_CMSIS(self->address)->ARR = (SystemCoreClock / config->frequency) - 1;
  /*Enable UIE interrutpt*/
  TIM_CMSIS(self->address)->DIER |= TIM_DIER_UIE;
  /*Enable counter*/
  TIM_CMSIS(self->address)->CR1 |= TIM_CR1_CEN;
  
  /*Register ISR event*/
  stm32f446xx_isr_register(self->isr, stm32f446_tim_timer_handler,
    self, config->irq);
}

void stm32f446_tim_timer_handler(void *args)
{
  stm32f446xx_tim_timer_t *self = (stm32f446xx_tim_timer_t*)args;

  if(TIM_CMSIS(self->address)->SR & TIM_SR_UIF)
  {
    if(self->callback)
    {
      self->callback();
    }
    TIM_CMSIS(self->address)->SR &= TIM_SR_UIF;
  }
}

stm32f446xx_isr_t stm32f446xx_tim9_isr;
stm32f446xx_tim_timer_t stm32f446xx_tim_9 = 
{
  .address = TIM9_BASE,
  .isr = &stm32f446xx_tim9_isr,
  .callback = 0
};

stm32f446xx_tim_timer_t * const TIMER_0 = &stm32f446xx_tim_9;