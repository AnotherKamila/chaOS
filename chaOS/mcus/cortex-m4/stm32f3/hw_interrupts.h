/* defines STM32F3 hardware interrupt numbers */

#ifndef MCUS_CORTEXM4_STM32F3_HW_INTERRUPTS_H
#define MCUS_CORTEXM4_STM32F3_HW_INTERRUPTS_H


/*
 * These are numbered according to their exception numbers, in general exception number of
 * IRQ is IRQ number + _IRQ_OFFSET (defined in `system_interrupts.h`).
 * For exception numbers see:
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0553a/BABIFJFG.html
 * For IRQ numbers see Table 30 on page 183 here:
 * http://www.st.com/web/en/resource/technical/document/reference_manual/DM00043574.pdf
 */

#define INT_WWDG                 16 // Window watchdog interrupt
#define INT_PVD                  17 // PVD through EXTI line 16 detection interrupt
#define INT_TAMP_STAMP           18 // Tamper and TimeStamp interrupts through the EXTI line 19
#define INT_RTC_WKUP             19 // RTC Wakeup interrupt through the EXTI line 20
#define INT_FLASH                20 // Flash global interrupt
#define INT_RCC                  21 // RCC global interrupt
#define INT_EXTI0                22 // EXTI Line 0 interrupt
#define INT_EXTI1                23 // EXTI Line 1 interrupt
#define INT_EXTI2_TSC            24 // EXTI Line 2 and Touch sensing interrupts
#define INT_EXTI3                25 // EXTI Line 3
#define INT_EXTI4                26 // EXTI Line 4
#define INT_DMA1_CH1             27 // DMA1 channel 1 interrupt
#define INT_DMA1_CH2             28 // DMA1 channel 2 interrupt
#define INT_DMA1_CH3             29 // DMA1 channel 3 interrupt
#define INT_DMA1_CH4             30 // DMA1 channel 4 interrupt
#define INT_DMA1_CH5             31 // DMA1 channel 5 interrupt
#define INT_DMA1_CH6             32 // DMA1 channel 6 interrupt
#define INT_DMA1_CH7             33 // DMA1 channel 7 interrupt
#define INT_ADC1_2               34 // ADC1 and ADC2 global interrupt
#define INT_USB_HP_CAN_TX        35 // USB High Priority/CAN_TX interrupts
#define INT_USB_LP_CAN_RX0       36 // USB Low Priority/CAN_RX0 interrupts
#define INT_CAN_RX1              37 // CAN_RX1 interrupt
#define INT_CAN_SCE              38 // CAN_SCE interrupt
#define INT_EXTI_9_5             39 // EXTI Line[9:5] interrupts
#define INT_TIM1_BRK_TIM_15      40 // TIM1 Break/TIM15 global interrupts
#define INT_TIM1_UP_TIM_16       41 // TIM1 Update/TIM16 global interrupts
#define INT_TIM1_TRG_COM_TIM_17  42 // TIM1 trigger and commutation/TIM17 interrupts
#define INT_TIM1_CC              43 // TIM1 capture compare interrupt
#define INT_TIM2                 44 // TIM2 global interrupt
#define INT_TIM3                 45 // TIM3 global interrupt
#define INT_TIM4                 46 // TIM4 global interrupt
#define INT_I2C1_EV_EXTI23       47 // I2C1 event interrupt & EXTI Line 23 interrupt
#define INT_I2C1_ER              48 // I2C1 error interrupt
#define INT_I2C2_EV_EXTI24       49 // I2C2 event interrupt & EXTI Line 24 interrupt
#define INT_I2C2_ER              50 // I2C2 error interrupt
#define INT_SPI1                 51 // SPI1 global interrupt
#define INT_SPI2                 52 // SPI2 global interrupt
#define INT_USART1_EXTI25        53 // USART1 global interrupt & EXTI Line 25
#define INT_USART2_EXTI26        54 // USART2 global interrupt & EXTI Line 26
#define INT_USART3_EXTI28        55 // USART3 global interrupt & EXTI Line 28
#define INT_EXTI15_10            56 // EXTI Line[15:10] interrupts
#define INT_RTCALARM             57 // RTC alarm interrupt
#define INT_USB_WKUP             58 // USB wakeup from Suspend (EXTI line 18)
#define INT_TIM8_BRK             59 // TIM8 break interrupt
#define INT_TIM8_UP              60 // TIM8 update interrupt
#define INT_TIM8_TRG_COM         61 // TIM8 Trigger and commutation interrupts
#define INT_TIM8_CC              62 // TIM8 capture compare interrupt
#define INT_ADC3                 63 // ADC3 global interrupt
// 64 - 66: reserved
#define INT_SPI3                 67 // SPI3 global interrupt
#define INT_UART4_EXTI34         68 // UART4 global and EXTI Line 34 interrupts
#define INT_UART5_EXTI35         69 // UART5 global and EXTI Line 35 interrupts
#define INT_TIM6_DACUNDER        70 // TIM6 global and DAC12 underrun interrupts
#define INT_TIM7                 71 // TIM7 global interrupt
#define INT_DMA2_CH1             72 // DMA2 channel 1 global interrupt
#define INT_DMA2_CH2             73 // DMA2 channel 2 global interrupt
#define INT_DMA2_CH3             74 // DMA2 channel 3 global interrupt
#define INT_DMA2_CH4             75 // DMA2 channel 4 global interrupt
#define INT_DMA2_CH5             76 // DMA2 channel 5 global interrupt
#define INT_ADC4                 77 // ADC4 global interrupt
// 78, 79: reserved
#define INT_COMP123              80 // COMP1 & COMP2 & COMP3 interrupts & EXTI Lines 21, 22 and 29
#define INT_COMP456              81 // COMP4 & COMP5 & COMP6 interrupts & EXTI Lines 30, 31 and 32
#define INT_COMP7                82 // COMP7 interrupt combined with EXTI Line 33 interrupt
// 83 - 89: reserved
#define INT_USB_HP_REMAP         90 // USB High priority interrupt (after remap)
#define INT_USB_LP_REMAP         91 // USB Low priority interrupt (after remap)
#define INT_USB_WKUP_REMAP       92 // USB wake up from Suspend and EXTI Line 18 (after remap)
// 94 - 96: reserved
#define INT_FPU                  97 // Floating point interrupt



#endif
