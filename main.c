#include "FreeRTOS.h"
#include "task.h"

#include "devices/logger.h"
#include "printf.h"

extern TaskHandle_t xMotorControlTaskHandle;
extern void vMotorControlTask(void *pvParameters);

void vLoggerTask(void *pvParameters)
{
  /* Initialize logger */
  logger_init();

  while(1)
  {
    printf("Hello World");
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void vInitTask(void *pvParameters)
{
  /* Initialize system tasks */
  xTaskCreate(vMotorControlTask,
    "MotorControlTask",
    configMINIMAL_STACK_SIZE,
    (void*)0,
    tskIDLE_PRIORITY + 2,
    xMotorControlTaskHandle);

  xTaskCreate(vLoggerTask,
    "LoggerTask",
    configMINIMAL_STACK_SIZE,
    (void*)0,
    tskIDLE_PRIORITY + 1,
    NULL);

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