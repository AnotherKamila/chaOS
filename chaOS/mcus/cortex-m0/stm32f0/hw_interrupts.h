/* defines STM32F0 hardware interrupt numbers */

#ifndef MCUS_CORTEXM0_STM32F0_HW_INTERRUPTS_H
#define MCUS_CORTEXM0_STM32F0_HW_INTERRUPTS_H

/*
 * Those are numbered according to their exception numbers, in general exception number of
 * IRQ is IRQ number + _IRQ_OFFSET (defined in `system_interrupts.h`).
 * For exception numbers see:
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/BABBGBEC.html
 * For IRQ numbers see Table 33 on page 193 here:
 * http://www.st.com/web/en/resource/technical/document/reference_manual/DM00031936.pdf
 */

#define INT_WWDG                 16 // Window watchdog interrupt
#define INT_PVD_VDDIO2           17 // PVD and V_{ddio2} comparator interrupt (EXTI lines 16 and 31)
#define INT_RTC                  18 // RTC interrupts (EXTI lines 17, 19 and 20)
#define INT_FLASH                19 // Flash global interrupt
#define INT_RCC_CRS              20 // RCC and CRS global interrupts
#define INT_EXTI0_1              21 // EXTI 0 and 1 lines
#define INT_EXTI2_3              22 // EXTI 2 and 3 lines
#define INT_EXTI4_15             23 // EXTI 4 to 15 lines
#define INT_TSC                  24 // Touch sensing interrupt
#define INT_DMA_CH1              25 // DMA Channel 1 interrupt
#define INT_DMA_CH2_3            26 // DMA Channel 2 and 3 interrupts
#define INT_DMA_CH4_5_6_7        27 // DMA Channel 4, 5, 6 and 7 interrupts
#define INT_ADC_COMP             28 // ADC and COMP interrupts (ADC int and EXTI lines 21 and 22)
#define INT_TIM1_BRK_UP_TRG_COM  29 // TIM1 break, update, trigger and commutation interrupt
#define INT_TIM1_CC              30 // TIM1 capture compare interrupt
#define INT_TIM2                 31 // TIM2 global interrupt
#define INT_TIM3                 32 // TIM3 global interrupt
#define INT_TIM6_DAC             33 // TIM6 global interrupts and DAC underrun interrupt
#define INT_TIM7                 34 // TIM7 global interrupts
#define INT_TIM14                35 // TIM14 global interrupts
#define INT_TIM15                36 // TIM15 global interrupts
#define INT_TIM16                37 // TIM16 global interrupts
#define INT_TIM17                38 // TIM17 global interrupts
#define INT_I2C1                 39 // I^2C 1 global interrupt (combined with EXTI line 23)
#define INT_I2C2                 40 // I^2C 2 global interrupt
#define INT_SPI1                 41 // SPI 1 global interrupt
#define INT_SPI2                 42 // SPI 2 global interrupt
#define INT_USART1               43 // USART 1 global interrupt (combined with EXTI line 25)
#define INT_USART2               44 // USART 2 global interrupt (combined with EXTI line 26)
#define INT_USART3_4             45 // USART 3 and 4 global interrupt
#define INT_CEC_CAN              46 // CEC and CAN global interrupts (combined with EXTI line 27)
#define INT_USB                  47 // USB global interrupt (combined with EXTI line 18)

#endif
