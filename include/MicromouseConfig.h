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

/* Sensor systick constanst*/
#define SENSOR_SYSTICK_FREQUENCY         500
#define SENSOR_SYSTICK_PERIOD            (1.0/SENSOR_SYSTICK_FREQUENCY)

/* Motion profile configuration constants */
#define FORWARD_ACCELERATION      1.0

/* System Control configuration constants */
#define FORWARD_CONTROL_KP              0.0 
#define FORWARD_CONTROL_KI              0.0
#define FORWARD_CONTROL_KD              0.0
#define FORWARD_CONTROL_INTEGRAL_MAX    0.0
#define FORWARD_CONTROL_MAX_OUTPUT      0.0
#define FORWARD_CONTROL_MIN_OUTPUT      0.0

/* Maze configuration constants */
#define MAZE_CELL_CENTER_DISTANCE 180.0

/* RTOS tasks configuration constants */
#define TASK_SYSTEM_CONTROL_PRIORITY      (tskIDLE_PRIORITY + 3U)
#define TASK_NETWORK_MANAGER_PRIORITY     (tskIDLE_PRIORITY + 1U)
#define TASK_TERMINAL_PRIORITY            (tskIDLE_PRIORITY + 1U)
#define TASK_APPLICATION_PRIORITY         (tskIDLE_PRIORITY + 2U)

#define TASK_SYSTEM_CONTROL_STACK_SIZE    (configMINIMAL_STACK_SIZE)
#define TASK_NETWORK_MANAGER_STACK_SIZE   (configMINIMAL_STACK_SIZE)
#define TASK_TERMINAL_STACK_SIZE          (configMINIMAL_STACK_SIZE)
#define TASK_APPLICATION_STACK_SIZE       (configMINIMAL_STACK_SIZE)

#define TASK_SYSTEM_TASK_PERIOD_MS        (2U)
#define TASK_NETWORK_MANAGER_PERIOD_MS    (100U)
#define TASK_TERMINAL_PERIOD_MS           (50U)
#define TASK_APPLICATION_PERIOD_MS        (2U)

#define TASK_SENSOR_RAW_MSG_QUEUE         (10U)
#define TASK_SENSOR_MSG_QUEUE             (10U)

#endif