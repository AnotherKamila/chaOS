/* defines cpu family common memory map and declares peripherals */

#ifndef MCUS_CORTEXM0_COMMON_MEMMAP_H
#define MCUS_CORTEXM0_COMMON_MEMMAP_H


#include "comm_peripherals.h"

/* --- Cortex M0 peripherals base address --------------------------------------------------------*/

#define CORE_PERIPH_BASE    0xE0000000

/* --- Cortex M0 peripherals addresses offsets ---------------------------------------------------*/

#define CORE_PBASE_SCB1_OFFSET      0x0000E008
#define CORE_PBASE_SYSTICK_OFFSET   0x0000E010
#define CORE_PBASE_NVIC1_OFFSET     0x0000E100
#define CORE_PBASE_SCB2_OFFSET      0x0000ED00
#define CORE_PBASE_NVIC2_OFFSET     0x0000EF00

/* --- Cortex M0 peripherals declaration ---------------------------------------------------------*/

extern SCB_struct  * const SCB;
extern STK_struct  * const STK;
extern NVIC_struct * const NVIC;


#endif
