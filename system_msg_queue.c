#include "system_msg_queue.h"

#include "FreeRTOS.h"
#include "queue.h"

/* msgs queue handles for thread communication */
QueueHandle_t xSensorMsgQueue;

void vSensorMsgQueueInit(void)
{
  xSensorMsgQueue = xQueueCreate(TASK_SENSOR_MSG_QUEUE,
    sizeof(sensor_msg_t));
}

BaseType_t xSensorMsgQueueSend(sensor_msg_t *msg, TickType_t xTicksToWait)
{
  BaseType_t xResult = xQueueSend(xSensorMsgQueue, msg, xTicksToWait);
  return xResult;
}

BaseType_t xSensorMsgQueueReceive(sensor_msg_t *msg, TickType_t xTicksToWait)
{
  BaseType_t xResult = xQueueReceive(xSensorMsgQueue, msg, xTicksToWait);
  return xResult;
}
