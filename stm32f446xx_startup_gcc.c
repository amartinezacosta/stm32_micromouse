#include <stm32f4xx.h>
#include "stm32f446xx_isr.h"

extern void main(void);
extern void SystemInit(void);

extern void __INITIAL_SP(void);
__STATIC_FORCEINLINE void __initialize_data(uint32_t *origin, 
                                            uint32_t *start, 
                                            uint32_t *end);
__STATIC_FORCEINLINE void __initialize_bss(uint32_t *start, 
                                      uint32_t *end);

/* ARM system interrupts */
void Reset_Handler(void);
void NMI_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void PenSV_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)              __attribute__((weak, alias("Default_Handler")));

/*STM32F446xx system interrupts */
void WWDG_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void PVD_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void EXTI0_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void EXTI1_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void EXTI2_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void EXTI3_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void EXTI4_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void ADC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void CAN1_TX_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void CAN1_RX0_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void TIM2_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void TIM4_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void SPI2_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void USART1_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void USART2_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void USART3_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void FMC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void SDIO_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void TIM5_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void SPI3_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void UART4_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void UART5_Handler(void)                __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void TIM7_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void OTG_FS_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void USART6_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void OTG_HS_WKUP_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void OTG_HS_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void DCMI_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void FPU_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
void SPI4_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void SAI1_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void SAI2_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
void QuadSPI_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void HDMI_CEC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void SPIDF_RX_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void FMPI2C1_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void FMPI2C1_Error_Handler(void)        __attribute__((weak, alias("Default_Handler")));

__VECTOR_TABLE_ATTRIBUTE void(*__VECTOR_TABLE[])(void) = 
{
  __INITIAL_SP,               /* -16 - Stack Pointer */
  Reset_Handler,              /* -15 - Reset */
  NMI_Handler,                /* -14 - Non-maskable interrupt */
  HardFault_Handler,          /* -13 - Hard fault */
  MemManage_Handler,          /* -12 - MemManage */
  BusFault_Handler,           /* -11 - BusFault */
  UsageFault_Handler,         /* -10 - UsageFault */
  0,                          /* -9 - Reserved*/
  0,                          /* -8 - Reserved*/
  0,                          /* -7 - Reserved*/
  0,                          /* -6 - Reserved*/
  SVC_Handler,                /* -5 - SVC*/
  DebugMon_Handler,           /* -4 - Debug Monitor*/
  0,                          /* -3 - Reserved*/
  PenSV_Handler,              /* -2 - PendSV*/
  SysTick_Handler,            /* -1 - SysTick*/
  /*STM32F446xx system interrupts */
  WWDG_Handler,               /*0 - WWDG*/
  PVD_Handler,                /*1 - PVD*/
  TAMP_STAMP_Handler,         /*2 -TAMP STAMP*/
  RTC_WKUP_Handler,           /*3 - RTC WKUP*/
  FLASH_Handler,              /*4 - FLASH*/
  RCC_Handler,                /*5 - RCC*/
  EXTI0_Handler,              /*6 - EXTI0*/
  EXTI1_Handler,              /*7 - EXTI1*/
  EXTI2_Handler,              /*8 - EXTI2*/
  EXTI3_Handler,              /*9 - EXTI3*/
  EXTI4_Handler,              /*10 - EXTI4*/ 
  DMA1_Stream0_Handler,       /*11 - DMA1 Stream0*/
  DMA1_Stream1_Handler,       /*12 - DMA1 Stream1*/
  DMA1_Stream2_Handler,       /*13 - DMA1 Stream2*/
  DMA1_Stream3_Handler,       /*14 - DMA1 Stream3*/
  DMA1_Stream4_Handler,       /*15 - DMA1 Stream4*/
  DMA1_Stream5_Handler,       /*16 - DMA1 Stream5*/
  DMA1_Stream6_Handler,       /*17 - DMA1 Stream6*/
  ADC_Handler,                /*18 - ADC*/
  CAN1_TX_Handler,            /*19 - CAN1 TX*/
  CAN1_RX0_Handler,           /*20 - CAN1 RX0*/
  CAN1_RX1_Handler,           /*21 - CAN1 RX1*/
  CAN1_SCE_Handler,           /*22 - CAN1 SCE*/
  EXTI9_5_Handler,            /*23 - EXTI 9-5*/
  TIM1_BRK_TIM9_Handler,      /*24 - TIM1 break TIM9 global*/
  TIM1_UP_TIM10_Handler,      /*25 - TIM1 update TIM10 global*/
  TIM1_TRG_COM_TIM11_Handler, /*26 - TIM1 trigger TIM11 global*/
  TIM1_CC_Handler,            /*27 - TIM1_CC*/
  TIM2_Handler,               /*28 - TIM2*/
  TIM3_Handler,               /*29 - TIM3*/
  TIM4_Handler,               /*30 - TIM4*/
  I2C1_EV_Handler,            /*31 - I2C1_EV*/
  I2C1_ER_Handler,            /*32 - I2C1_ER*/
  I2C2_EV_Handler,            /*33 - I2C2_EV*/
  I2C2_ER_Handler,            /*34 - I2C2_ER*/
  SPI1_Handler,               /*35 - SPI1*/
  SPI2_Handler,               /*36 - SPI2*/
  USART1_Handler,             /*37 - USART1*/
  USART2_Handler,             /*38 - USART2*/
  USART3_Handler,             /*39 - USART3*/
  EXTI15_10_Handler,          /*40 - EXTI15_10*/
  RTC_Alarm_Handler,
  OTG_FS_WKUP_Handler,
  TIM8_BRK_TIM12_Handler,
  TIM8_UP_TIM13_Handler,
  TIM8_TRG_COM_TIM14_Handler,
  TIM8_CC_Handler,
  DMA1_Stream7_Handler,
  FMC_Handler,
  SDIO_Handler,
  TIM5_Handler,
  SPI3_Handler,
  UART4_Handler,
  UART5_Handler,
  TIM6_DAC_Handler,
  TIM7_Handler,
  DMA2_Stream0_Handler,
  DMA2_Stream1_Handler,
  DMA2_Stream2_Handler,
  DMA2_Stream3_Handler,
  DMA2_Stream4_Handler,
  0,
  0,
  CAN2_TX_Handler,
  CAN2_RX0_Handler,
  CAN2_RX1_Handler,
  CAN2_SCE_Handler,
  OTG_FS_Handler,
  DMA2_Stream5_Handler,
  DMA2_Stream6_Handler,
  DMA2_Stream7_Handler,
  USART6_Handler,
  I2C3_EV_Handler,
  I2C3_ER_Handler,
  OTG_HS_EP1_OUT_Handler,
  OTG_HS_EP1_IN_Handler,
  OTG_HS_WKUP_Handler,
  OTG_HS_Handler,
  DCMI_Handler,
  0,
  0,
  FPU_Handler,
  0,
  0,
  SPI4_Handler,
  0,
  0,
  SAI1_Handler,
  0,
  0,
  0,
  SAI2_Handler,
  QuadSPI_Handler,
  HDMI_CEC_Handler,
  SPIDF_RX_Handler,
  FMPI2C1_Handler,
  FMPI2C1_Error_Handler
};

__NO_RETURN void Reset_Handler(void)
{
  /*Intialize board*/
  //SystemInit();

  /*Initialize data and bss sections*/
  extern uint32_t __etext,__data_start__,__data_end__;
  extern uint32_t __bss_start__,__bss_end__;
  __initialize_data(&__etext, &__data_start__, &__data_end__);
  __initialize_bss(&__bss_start__, &__bss_end__);

  /*Intialize vtable*/
  stm32f446xx_isr_vtable_init();

  /*Call main application*/
  main();

  /* Should never hit this point*/
  while(1);
}

void Default_Handler(void)
{
  while(1)
  {

  }
}

__STATIC_FORCEINLINE void __initialize_data(uint32_t *origin, 
                                            uint32_t *start, 
                                            uint32_t *end)
{
  /* Copy data section to RAM*/
  uint32_t *p = start;
  while(p < end)
    *p++ = *origin++;
}

__STATIC_FORCEINLINE void __initialize_bss(uint32_t *start, 
                                      uint32_t *end)
{
  /*Initialize bss section to 0*/
  uint32_t *p = start;
  while(p < end)
    *p++ = 0;
}
