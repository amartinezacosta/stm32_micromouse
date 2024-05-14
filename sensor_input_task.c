#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "MicromouseConfig.h"
#include "drivers/stm32f446xx_tim.h"
#include "devices/motor.h"
#include "sensor_input_task.h"

QueueHandle_t xSensorRawMsgISRQueue;
QueueHandle_t xSensorMsgQueue;

void SensorSysTick(void)
{
  BaseType_t xHigerPriorityTaskWoken = pdFALSE;
  sensor_raw_msg_t sensor_msg = {0};

  sensor_msg.left_encoder = motor_left_position();
  sensor_msg.right_encoder = motor_right_position();

  xQueueSendFromISR(xSensorRawMsgISRQueue, 
    &sensor_msg, 
    &xHigerPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigerPriorityTaskWoken); 
}

void SensorSysTickInit(void)
{
  /* Initialize sensor systick timer*/
  stm32f446xx_tim_timer_config_t stm32f446xx_timer_9_config;
  stm32f446xx_timer_9_config.frequency = SENSOR_SYSTICK_FREQUENCY;
  stm32f446xx_timer_9_config.irq = TIM1_BRK_TIM9_IRQn;
  stm32f446xx_timer_9_config.prio = 1;

  stm32f446xx_tim_timer_init(TIM9_BASE,
    SensorSysTick, 
    &stm32f446xx_timer_9_config);
}

float SensorInputPosition(float encoder_left, float encoder_right)
{
  float left_encoder_mm = encoder_left * LEFT_WHEEL_COUNTS_TO_MM;
  float right_encoder_mm = encoder_right * RIGHT_WHEEL_COUNTS_TO_MM;
  float position = 0.5 * (left_encoder_mm + right_encoder_mm);

  return position;
}

void vSensorInputTask(void *pvParameters)
{
  /* Initialize sensor's peripheral hardware */
  // left_motor_init();
  // motor_right_init();

  /* Create sensor raw msg queue */
  xSensorRawMsgISRQueue = xQueueCreate(TASK_SENSOR_RAW_MSG_QUEUE, 
    sizeof(sensor_raw_msg_t));

  /* Create sensor msg queue*/
  xSensorMsgQueue = xQueueCreate(TASK_SENSOR_MSG_QUEUE,
    sizeof(sensor_msg_t));

  SensorSysTickInit();

  while(1)
  {
    sensor_raw_msg_t sensor_raw_msg = {0};
    sensor_msg_t sensor_msg = {0};
    
    xQueueReceive(xSensorRawMsgISRQueue,
      &sensor_raw_msg,
      portMAX_DELAY);

    /* Process variable and send it to the application */
    sensor_msg.position = SensorInputPosition(sensor_raw_msg.left_encoder,
      sensor_raw_msg.right_encoder);

    /* Send sensor msg to queue */
  }
}
