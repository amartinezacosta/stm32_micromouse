#include "terminal_task.h"
#include "printf.h"

#include "FreeRTOS.h"
#include "task.h"

void vTerminalTask(void *pvParameters)
{
  (void)pvParameters;

  /* Initialize logger */
  // logger_init();

  while(1)
  {
    // printf("Hello World");
    vTaskDelay(portMAX_DELAY);
  }
}