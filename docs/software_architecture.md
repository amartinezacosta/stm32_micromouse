# Micromouse Software Architecture 

There should be 3 layers to the software:

1. Drivers
2. Application
3. Maze

Where the drivers are the low level software for handling peripherals, and the 
application layer handles communications, system control, state machine. Lastly
the maze layer will contain all the methods for maze memory layout, maze path-
finding and mouse odometry inside the maze.

## Drivers

The peripherals needed to actuate and sense a micromouse are:

1. 2 Timers using encoder mode
2. 4 PWM for motor speed and direction control
3. 1 I2C for gyroscope
4. 4 ADC for IR led analog read
5. 4 GPIO for IR led toggle
6. 1 ADC for battery voltage level read
7. 1 UART for ESP32 Wi-fi communication
8. 1 SPI for flash storage
9. 1 Timer ISR for system control

# PWM

TIM3 and TIM4 for PWM control

# Incremental Quadrature Encoder

TIM2 and TIM5 for quadrature encoder

# STM32F446RE pins

# LEDs
PA5 - > GPIOA -> GPIO_0

# IR Transmitters
PA9  -> GPIOA -> GPIO_1
PA10 -> GPIOA -> GPIO_2
PA11 -> GPIOA -> GPIO_3
PA12 -> GPIO1 -> GPIO_4

# IR Receivers
PC9  -> ADC1 -> ADC_1
PC10 -> ADC1 -> ADC_2
PC11 -> ADC1 -> ADC_3
PC12 -> ADC1 -> ADC_4

## Battery voltage
PC13 ???

# PWM
PA6 -> TIM3_CH1 -> PWM_0
PA7 -> TIM3_CH2 -> PWM_1
PB6 -> TIM4_CH1 -> PWM_2
PB7 -> TIM4_CH2 -> PWM_3

## Encoders
PA0 -> TIM5_CH1 -> ENC_0_TI1
PA1 -> TIM5_CH2 -> ENC_0_TI2
PB8 -> TIM2_CH1 -> ENC_1_TI1
PB9 -> TIM2_CH2 -> ENC_1_TI2

## UART log
PA2 -> USART2_TX -> UART_0_TX
PA3 -> USART2_RX -> UART_0_RX

## UART ESP32C3
PA9  -> USART1_TX -> UART_1_TX
PA10 -> USART1_RX -> UART_1_RX

## I2C MPU6050
PB10 -> I2C2_SCL -> I2C_0_SCL
PB11 -> I2C2_SDA -> I2C_0_SDA