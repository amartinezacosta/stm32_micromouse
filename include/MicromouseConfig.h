#ifndef MICROMOUSECONFIG_H_
#define MICROMOUSECONFIG_H_

#include "FreeRTOS.h"
#include "task.h"

/* Mouse hardware specific constants */
#define IR_LED_TX_COUNT           4
#define IR_LED_RX_COUNT           4
#define GYROSCOPE_AXIS_COUNT      3
#define LEFT_WHEEL_COUNTS_TO_MM   1.0
#define RIGHT_WHEEL_COUNTS_TO_MM  1.0

/* System control config constants */
#define SYSTICK_FREQUENCY         500
#define SYSTICK_PERIOD            (1.0/SYSTICK_FREQUENCY)

#define FORWARD_KP                1.0
#define FORWARD_KD                0.1

/* Motion profile configuration constants */
#define FORWARD_ACCELERATION      1.0

/* Maze configuration constants */
#define MAZE_CELL_CENTER_DISTANCE 180.0

/* Task configuration constants */
#define TASK_SENSOR_INPUT_PRIORITY        (tskIDLE_PRIORITY + 3U)
#define TASK_NETWORK_MANAGER_PRIORITY     (tskIDLE_PRIORITY + 1U)
#define TASK_TERMINAL_PRIORITY            (tskIDLE_PRIORITY + 1U)
#define TASK_APPLICATION_PRIORITY         (tskIDLE_PRIORITY + 2U)

#define TASK_SENSOR_INPUT_STACK_SIZE      (configMINIMAL_STACK_SIZE)
#define TASK_NETWORK_MANAGER_STACK_SIZE   (configMINIMAL_STACK_SIZE)
#define TASK_TERMINAL_STACK_SIZE          (configMINIMAL_STACK_SIZE)
#define TASK_APPLICATION_STACK_SIZE       (configMINIMAL_STACK_SIZE)

#define TASK_SENSOR_INPUT_PERIOD_MS       (2U)
#define TASK_NETWORK_MANAGER_PERIOD_MS    (100U)
#define TASK_TERMINAL_PERIOD_MS           (50U)
#define TASK_APPLICATION_PERIOD_MS        (2U)

#define TASK_SENSOR_INPUT_QUEUE_SIZE      (10U)

#endif