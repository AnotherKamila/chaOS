/* defines STM32F0 hardware interrupt numbers */

#ifndef MCUS_CORTEXM0_STM32F0_HW_INTERRUPTS_H
#define MCUS_CORTEXM0_STM32F0_HW_INTERRUPTS_H


#define INT_WWDG                  0 // Window watchdog interrupt
#define INT_PVD_VDDIO2            1 // PVD and V_{ddio2} comparator interrupt (EXTI lines 16 and 31)
#define INT_RTC                   2 // RTC interrupts (EXTI lines 17, 19 and 20)
#define INT_FLASH                 3 // Flash global interrupt
#define INT_RCC_CRS               4 // RCC and CRS global interrupts
#define INT_EXTI0_1               5 // EXTI 0 and 1 lines
#define INT_EXTI2_3               6 // EXTI 2 and 3 lines
#define INT_EXTI4_15              7 // EXTI 4 to 15 lines
#define INT_TSC                   8 // Touch sensing interrupt
#define INT_DMA_CH1               9 // DMA Channel 1 interrupt
#define INT_DMA_CH2_3            10 // DMA Channel 2 and 3 interrupts
#define INT_DMA_CH4_5_6_7        11 // DMA Channel 4, 5, 6 and 7 interrupts
#define INT_ADC_COMP             12 // ADC and COMP interrupts (ADC int and EXTI lines 21 and 22)
#define INT_TIM1_BRK_UP_TRG_COM  13 // TIM1 break, update, trigger and commutation interrupt
#define INT_TIM1_CC              14 // TIM1 capture compare interrupt
#define INT_TIM2                 15 // TIM2 global interrupt
#define INT_TIM3                 16 // TIM3 global interrupt
#define INT_TIM6_DAC             17 // TIM6 global interrupts and DAC underrun interrupt
#define INT_TIM7                 18 // TIM7 global interrupts
#define INT_TIM14                19 // TIM14 global interrupts
#define INT_TIM15                20 // TIM15 global interrupts
#define INT_TIM16                21 // TIM16 global interrupts
#define INT_TIM17                22 // TIM17 global interrupts
#define INT_I2C1                 23 // I^2C 1 global interrupt (combined with EXTI line 23)
#define INT_I2C2                 24 // I^2C 2 global interrupt
#define INT_SPI1                 25 // SPI 1 global interrupt
#define INT_SPI2                 26 // SPI 2 global interrupt
#define INT_USART1               27 // USART 1 global interrupt (combined with EXTI line 25)
#define INT_USART2               28 // USART 2 global interrupt (combined with EXTI line 26)
#define INT_USART3_4             29 // USART 3 and 4 global interrupt
#define INT_CEC_CAN              30 // CEC and CAN global interrupts (combined with EXTI line 27)
#define INT_USB                  31 // USB global interrupt (combined with EXTI line 18)


#endif
