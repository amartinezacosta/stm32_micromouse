#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "MicromouseConfig.h"
#include "drivers/stm32f446xx_tim.h"
#include "devices/motor.h"
#include "devices/encoder.h"
#include "motion_profile.h"
#include "system_control_task.h"
#include "pid.h"

QueueHandle_t xSensorRawMsgISRQueue;
motion_profile_t motion_profile;
pid_t forward_control;

void vSensorSysTick(void)
{
  BaseType_t xHigerPriorityTaskWoken = pdFALSE;
  sensor_raw_msg_t sensor_msg = {0};

  sensor_msg.left_encoder = encoder_left_read();
  sensor_msg.right_encoder = encoder_right_read();

  xQueueSendFromISR(xSensorRawMsgISRQueue, 
    &sensor_msg, 
    &xHigerPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigerPriorityTaskWoken); 
}

void vSensorSysTickInit(void)
{
  /* Initialize sensor systick timer*/
  stm32f446xx_tim_timer_config_t stm32f446xx_timer_9_config;
  stm32f446xx_timer_9_config.frequency = SENSOR_SYSTICK_FREQUENCY;
  stm32f446xx_timer_9_config.irq = TIM1_BRK_TIM9_IRQn;
  stm32f446xx_timer_9_config.prio = 1;

  stm32f446xx_tim_timer_init(TIM9_BASE,
    vSensorSysTick, 
    &stm32f446xx_timer_9_config);
}

float fSensorInputPosition(float encoder_left, float encoder_right)
{
  float left_encoder_mm = encoder_left * LEFT_WHEEL_COUNTS_TO_MM;
  float right_encoder_mm = encoder_right * RIGHT_WHEEL_COUNTS_TO_MM;
  float position = 0.5 * (left_encoder_mm + right_encoder_mm);

  return position;
}

void vSystemControlTask(void *pvParameters)
{
  (void)pvParameters;

  /* Initialize sensor's peripheral hardware */
  encoder_left_init();
  encoder_right_init();

  /* Create sensor raw msg queue */
  xSensorRawMsgISRQueue = xQueueCreate(TASK_SENSOR_RAW_MSG_QUEUE, 
    sizeof(sensor_raw_msg_t));

  motion_profile_start(&motion_profile,
    200.0,
    0.0,
    MAZE_CELL_CENTER_DISTANCE,
    FORWARD_ACCELERATION);

  pid_init(&forward_control, 
    FORWARD_CONTROL_KP, 
    FORWARD_CONTROL_KI,
    FORWARD_CONTROL_KD,
    FORWARD_CONTROL_INTEGRAL_MAX,
    SENSOR_SYSTICK_PERIOD,
    FORWARD_CONTROL_MAX_OUTPUT,
    FORWARD_CONTROL_MIN_OUTPUT);

  vSensorSysTickInit();

  while(1)
  {
    sensor_raw_msg_t sensor_raw_msg = {0};
    
    /*1. Receive sensor raw msg from timer ISR*/
    xQueueReceive(xSensorRawMsgISRQueue,
      &sensor_raw_msg,
      portMAX_DELAY);

    /*2. Process variable for state machine */
    float actual_position = fSensorInputPosition(sensor_raw_msg.left_encoder,
      sensor_raw_msg.right_encoder);

    /*3. Update motion profile position */
    float profile_position = motion_profile_update(&motion_profile);

    /*4. PID system control */
    pid_update_setpoint(&forward_control, profile_position);
    float control = pid_update(&forward_control, actual_position);

    /*4. Update motor output */

    /*5. Publish sensor values to other tasks */
  }
}
