#include "FreeRTOS.h"
#include "task.h"

#include "MicromouseConfig.h"

#include "devices/logger.h"
#include "printf.h"

void vSensorInputTask(void *pvParameters){while(1);}
void vNetworkManagerTask(void *pvParameters){while(1);}
void vTerminalTask(void *pvParameters){while(1);}
void vApplicationTask(void *pvParameters){while(1);}

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
  {vSensorInputTask,"SensorInputTask",TASK_SENSOR_INPUT_STACK_SIZE, NULL, TASK_SENSOR_INPUT_PRIORITY},
  {vNetworkManagerTask,"NetworkManagerTask",TASK_NETWORK_MANAGER_STACK_SIZE, NULL, TASK_NETWORK_MANAGER_PRIORITY},
  {vTerminalTask,"TerminalTask",TASK_TERMINAL_STACK_SIZE, NULL, TASK_TERMINAL_PRIORITY},
  {vApplicationTask,"ApplicationTask",TASK_SENSOR_INPUT_STACK_SIZE, NULL, TASK_SENSOR_INPUT_PRIORITY},
};

const uint32_t TaskInitCount = sizeof(TaskInitParams)/sizeof(TaskInitParams_t);

// extern TaskHandle_t xMotorControlTaskHandle;
// extern void vMotorControlTask(void *pvParameters);

// void vLoggerTask(void *pvParameters)
// {
//   /* Initialize logger */
//   logger_init();

//   while(1)
//   {
//     printf("Hello World");
//     vTaskDelay(100/portTICK_PERIOD_MS);
//   }
// }

void vInitTask(void *pvParameters)
{
  /* Initialize tasks */
  for(uint32_t i = 0; i < TaskInitCount; i++)
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