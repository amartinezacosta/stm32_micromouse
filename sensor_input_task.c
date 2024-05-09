#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "MicromouseConfig.h"
#include "drivers/stm32f446xx_tim.h"
#include "devices/motor.h"

typedef struct 
{
  uint32_t left_encoder;
  uint32_t right_encoder;
  uint32_t ir_rx[IR_LED_TX_COUNT];
  uint32_t button;
  uint32_t battery_voltage;
  uint32_t gyroscope[GYROSCOPE_AXIS_COUNT];
}sensor_raw_msg_t;

QueueHandle_t xSensorMsgISRQueue;

stm32f446xx_isr_t stm32f446xx_tim9_isr;
void sensor_systick(void);
stm32f446xx_tim_timer_t stm32f446xx_tim_9 = 
{
  .address = TIM9_BASE,
  .isr = &stm32f446xx_tim9_isr,
  .callback = &sensor_systick
};

void sensor_systick(void)
{
  BaseType_t xHigerPriorityTaskWoken = pdFALSE;
  sensor_raw_msg_t sensor_msg = {0};

  sensor_msg.left_encoder = motor_left_position();
  sensor_msg.right_encoder = motor_right_position();

  xQueueSendFromISR(xSensorMsgISRQueue, 
    &sensor_msg, 
    &xHigerPriorityTaskWoken);
  if(xHigerPriorityTaskWoken) taskYIELD_FROM_ISR(); 
}

void vSensorInputTask(void *pvParameters)
{
  /* Initialize motors */
  // left_motor_init();
  // motor_right_init();

  /* Create sensor ISR message queue */
  xSensorMsgISRQueue = xQueueCreate(TASK_SENSOR_INPUT_QUEUE_SIZE, 
    sizeof(sensor_raw_msg_t));

  /* Initialize sensor systick timer*/
  stm32f446xx_tim_timer_config_t stm32f446xx_timer_9_config;
  stm32f446xx_timer_9_config.frequency = SYSTICK_FREQUENCY;
  stm32f446xx_timer_9_config.irq = TIM1_BRK_TIM9_IRQn;
  stm32f446xx_timer_9_config.prio = 1;

  stm32f446xx_tim_timer_init(&stm32f446xx_tim_9, 
    &stm32f446xx_timer_9_config);

  sensor_raw_msg_t sensor_msg;
  while(1)
  {
    xQueueReceive(xSensorMsgISRQueue,
      &sensor_msg,
      portMAX_DELAY);

    /* Process variable and send it to the application */
    
  }
}

// float forward_position(void)
// {
//     uint32_t left_motor_encoder, right_motor_encoder;
//     float left_pos_mm, right_pos_mm, forward_pos_mm;

//     /*Update forward position*/
//     portENTER_CRITICAL();
//     {
//       left_motor_encoder = m_left_motor_encoder;
//       right_motor_encoder = m_right_motor_encoder;
//     }
//     portEXIT_CRITICAL();

//     left_pos_mm = left_motor_encoder * LEFT_WHEEL_COUNTS_TO_MM;
//     right_pos_mm = right_motor_encoder * RIGHT_WHEEL_COUNTS_TO_MM;
//     forward_pos_mm = 0.5 * (left_pos_mm + right_pos_mm);

//     return forward_pos_mm;
// }
