#ifndef SYSTEM_MSG_QUEUE_H_
#define SYSTEM_MSG_QUEUE_H_

#include "MicromouseConfig.h"

typedef struct
{
  float position;
  float ir_mm[IR_LED_RX_COUNT];
  uint32_t button;
  float battery_voltage;
  float gyroscope[GYROSCOPE_AXIS_COUNT];
}sensor_msg_t;


void vSensorMsgQueueInit(void);
BaseType_t xSensorMsgQueueSend(sensor_msg_t *msg, TickType_t xTicksToWait);
BaseType_t xSensorMsgQueueReceive(sensor_msg_t *msg, TickType_t xTicksToWait);

#endif