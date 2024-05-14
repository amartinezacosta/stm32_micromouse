# Directories
ARM_GCC_ROOT_DIR = /home/amartinezacosta/gcc-arm-none-eabi-10.3-2021.07
CMSIS_ROOT_DIR = /home/amartinezacosta/CMSIS_5
STM32_CMSIS_ROOT_DIR = /home/amartinezacosta/cmsis-header-stm32
ARM_GCC_BIN_DIR = $(ARM_GCC_ROOT_DIR)/bin
CMSIS_INCLUDE_DIR = $(CMSIS_ROOT_DIR)/CMSIS/Core/Include
STM32F4XX_CMSIS_INCLUDE_DIR = $(STM32_CMSIS_ROOT_DIR)/stm32f4xx/Include
PRINTF_INCLUDE_DIR = ./third_party/printf
FREERTOS_KERNEL_INCLUDE_DIR = ./third_party/FreeRTOS-Kernel/include
FREERTOS_KERNEL_PORT_INCLUDE_DIR = ./third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F

# Project constants
PROJECT_NAME = micromouse

# Project directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIRS = include \
							 $(CMSIS_INCLUDE_DIR) \
							 $(STM32F4XX_CMSIS_INCLUDE_DIR) \
							 $(PRINTF_INCLUDE_DIR) \
							 $(FREERTOS_KERNEL_INCLUDE_DIR) \
							 $(FREERTOS_KERNEL_PORT_INCLUDE_DIR)

# Compiler
CC = $(ARM_GCC_BIN_DIR)/arm-none-eabi-gcc

# GCC utilities
OBJ_COPY = $(ARM_GCC_BIN_DIR)/arm-none-eabi-objcopy

# NOTE: TARGET and SOURCES must be changed accordingly
TARGET = $(BIN_DIR)/$(PROJECT_NAME)
TARGET_ELF = $(TARGET).elf
TARGET_BIN = $(TARGET).bin
DRIVERS_SOURCES = drivers/stm32f446xx_gpio.c 	\
									drivers/stm32f446xx_tim.c 	\
									drivers/stm32f446xx_uart.c 	\
									drivers/stm32f446xx_isr.c 	\
									drivers/ringbuffer.c
DEVICES_SOURCES = devices/led.c	\
									devices/logger.c \
									devices/motor.c
THIRD_PARTY_SOURCES = third_party/printf/printf.c \
											third_party/FreeRTOS-Kernel/tasks.c \
											third_party/FreeRTOS-Kernel/list.c \
											third_party/FreeRTOS-Kernel/queue.c \
											third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c \
											third_party/FreeRTOS-Kernel/portable/MemMang/heap_4.c

SOURCES = main.c \
					sensor_input_task.c \
					network_manager_task.c \
					system_msg_queue.c	\
					stm32f446xx_startup_gcc.c \
					stm32f446xx_system.c \
					$(DRIVERS_SOURCES) \
					$(THIRD_PARTY_SOURCES) \
					$(DEVICES_SOURCES)
OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %, $(OBJ_DIR)/%, $(OBJECT_NAMES))

# Flags
MCU = STM32F446xx
WFLAGS = -Wall -Wextra -Wshadow
CFLAGS = $(WFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -ggdb -O0 -D$(MCU) \
				 -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS = -Tstm32f446xx.ld -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 \
					-nostartfiles -specs nano.specs

# Linking
$(TARGET_ELF): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

# Compiling
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: all clean flash $(TARGET_BIN)

all:$(TARGET_ELF)

clean:
	rm -r $(BUILD_DIR)

$(TARGET_BIN):$(TARGET_ELF)
	$(OBJ_COPY) -O binary $^ $@

flash:$(TARGET_BIN)
	st-flash --reset write $^ 0x8000000