#ifndef SENSOR_INPUT_TASK_H_
#define SENSOR_INPUT_TASK_H_

#include <stdint.h>
#include "MicromouseConfig.h"

typedef struct 
{
  uint32_t left_encoder;
  uint32_t right_encoder;
  uint32_t ir_rx[IR_LED_TX_COUNT];
  uint32_t button;
  uint32_t battery_voltage;
  uint32_t gyroscope[GYROSCOPE_AXIS_COUNT];
}sensor_raw_msg_t;

typedef struct
{
  float position;
}sensor_msg_t;

void vSensorInputTask(void *pvParameters);

#endif