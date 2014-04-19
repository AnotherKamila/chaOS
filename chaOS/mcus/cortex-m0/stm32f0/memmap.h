/* defines memory map and declares peripherals */

#ifndef MCUS_CORTEXM0_STM32F0_MEMMAP_H
#define MCUS_CORTEXM0_STM32F0_MEMMAP_H

/* --- Peripherals base address ------------------------------------------------------------------*/

#define PERIPH_BASE  0x40000000

/* --- Buses base addresses ----------------------------------------------------------------------*/

#define APB_PERIPH_BASE  (PERIPH_BASE)
#define AHBPERIPH_BASE   (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE  (PERIPH_BASE + 0x08000000)

/* --- Peripheral adress offsets -----------------------------------------------------------------*/

#define GPIO_AHB2_OFFSET_PORTA  0x00000000
#define GPIO_AHB2_OFFSET_PORTB  0x00000400
#define GPIO_AHB2_OFFSET_PORTC  0x00000800
#define GPIO_AHB2_OFFSET_PORTD  0x00000C00
#define GPIO_AHB2_OFFSET_PORTE  0x00001000
#define GPIO_AHB2_OFFSET_PORTF  0x00001400

#define RCC_AHB_OFFSET          0x00001000

/* --- Peripherals declaration -------------------------------------------------------------------*/

extern GPIO_struct * const GPIO[];
extern RCC_struct  * const RCC;


#endif
