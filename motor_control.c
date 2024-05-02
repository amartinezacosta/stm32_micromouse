#include "FreeRTOS.h"
#include "task.h"

#include "MicromouseConfig.h"
#include "drivers/stm32f446xx_tim.h"
#include "devices/motor.h"

typedef enum
{
  ACCELERATING,
  CRUISING,
  DECELERATING
}motion_profile_t;

float forward_position(void);

stm32f446xx_isr_t stm32f446xx_tim9_isr;
void systick_control(void);
stm32f446xx_tim_timer_t stm32f446xx_tim_9 = 
{
  .address = TIM9_BASE,
  .isr = &stm32f446xx_tim9_isr,
  .callback = &systick_control
};

TaskHandle_t xMotorControlTaskHandle;

uint32_t m_left_motor_encoder = 0;
uint32_t m_right_motor_encoder = 0;

void systick_control(void)
{
  /* Update proccess variables */
  m_left_motor_encoder = motor_left_position();
  m_right_motor_encoder = motor_right_position();

  /* Wake up task for motor control */
  /*TODO: Add ADC trigger, and then wake up task from ADC*/
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR(xMotorControlTaskHandle,
    &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void vMotorControlTask(void *pvParameters)
{
  /* Initialize motors */
  left_motor_init();
  motor_right_init();

  /* Initialize systems control SysTick*/
  stm32f446xx_tim_timer_config_t stm32f446xx_timer_9_config;
  stm32f446xx_timer_9_config.frequency = SYSTICK_FREQUENCY;
  stm32f446xx_timer_9_config.irq = TIM1_BRK_TIM9_IRQn;
  stm32f446xx_timer_9_config.prio = 1;

  stm32f446xx_tim_timer_init(&stm32f446xx_tim_9, 
    &stm32f446xx_timer_9_config);

  float position;
  float prev_error;

  float velocity = 0.0;
  float profile_position = 0.0;
  float target_velocity = 10.0;
  float acceleration = 0.0;
  motion_profile_t motion_state = ACCELERATING;
  while(1)
  {
    /* Wait for SysTick control */
    ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

    /* Update forward position */
    position = forward_position();


    /* Update motion control profile */
    switch(motion_state)
    {
      case ACCELERATING:
      velocity += FORWARD_ACCELERATION*SYSTICK_PERIOD;
      if(velocity > target_velocity)
      {
        velocity = target_velocity;
        motion_state = CRUISING;
      }
      break;
      case CRUISING:
      break;
      case DECELERATING:
      break;
    }

    profile_position += velocity*SYSTICK_PERIOD;


    /* Update PD controller */
    float error = profile_position - position;
    float error_diff = error - prev_error;
    prev_error = error;
    float output = FORWARD_KP*error + FORWARD_KD*error_diff;

  }
}

float forward_position(void)
{
    uint32_t left_motor_encoder, right_motor_encoder;
    float left_pos_mm, right_pos_mm, forward_pos_mm;

    /*Update forward position*/
    portENTER_CRITICAL();
    {
      left_motor_encoder = m_left_motor_encoder;
      right_motor_encoder = m_right_motor_encoder;
    }
    portEXIT_CRITICAL();

    left_pos_mm = left_motor_encoder * LEFT_WHEEL_COUNTS_TO_MM;
    right_pos_mm = right_motor_encoder * RIGHT_WHEEL_COUNTS_TO_MM;
    forward_pos_mm = 0.5 * (left_pos_mm + right_pos_mm);

    return forward_pos_mm;
}
