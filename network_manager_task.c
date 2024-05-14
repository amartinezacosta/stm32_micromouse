#include "network_manager_task.h"
#include "FreeRTOS.h"
#include "task.h"

void vNetworkManagerTask(void *pvParameters)
{
  while(1)
  {
    vTaskDelay(portMAX_DELAY);
  }
}