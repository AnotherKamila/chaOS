/* defines CPU family common memory map and declares peripherals */

#ifndef MCUS_CORTEXM4_COMMON_MEMMAP_H
#define MCUS_CORTEXM4_COMMON_MEMMAP_H


#include "common_peripherals.h"

/* --- Cortex M4 peripherals base address --------------------------------------------------------*/

#define CORE_PERIPH_BASE    0xE0000000

/* --- Cortex M4 peripherals addresses offsets ---------------------------------------------------*/

#define CORE_PBASE_SYSTICK_OFFSET   0x0000E010


#endif
