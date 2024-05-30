#include "FreeRTOS.h"
#include "task.h"

#include "MicromouseConfig.h"
#include "system_msg_queue.h"
#include "system_control_task.h"
#include "network_manager_task.h"
#include "terminal_task.c"

typedef struct
{
  TaskFunction_t      TaskPtr;
  const char * const  TaskName;
  const size_t        StackSize;
  void * const        ParametersPtr;
  UBaseType_t         TaskPriority; 
}TaskInitParams_t;

TaskInitParams_t TaskInitParams[] =
{
  {vSystemControlTask,  "SystemControlTask",  TASK_SYSTEM_CONTROL_STACK_SIZE, NULL, TASK_SYSTEM_CONTROL_PRIORITY},
  {vNetworkManagerTask, "NetworkManagerTask", TASK_NETWORK_MANAGER_STACK_SIZE, NULL, TASK_NETWORK_MANAGER_PRIORITY},
  {vTerminalTask,       "TerminalTask",       TASK_TERMINAL_STACK_SIZE, NULL, TASK_TERMINAL_PRIORITY},
};
const uint32_t TaskInitParamsCount = sizeof(TaskInitParams) / sizeof(TaskInitParams_t);

void vInitTask(void *pvParameters)
{
  /* Initialize system queues */
  vSensorMsgQueueInit();

  /* Initialize tasks */
  for(uint32_t i = 0; i < TaskInitParamsCount; i++)
  {
    TaskInitParams_t *task = &TaskInitParams[i];
    xTaskCreate(task->TaskPtr,
      task->TaskName,
      task->StackSize,
      task->ParametersPtr,
      task->TaskPriority, 
      NULL);
  }

  /* Delete this task */
  vTaskDelete(NULL);
}

int main(void)
{
  xTaskCreate(vInitTask,
    "InitTask",
    configMINIMAL_STACK_SIZE,
    (void*)0,
    tskIDLE_PRIORITY,
    NULL);

  vTaskStartScheduler();

  /* Should never reach this point*/
  for(;;);
}