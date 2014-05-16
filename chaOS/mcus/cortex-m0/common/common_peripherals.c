/* define Cortex M0 common peripherals */

#include "common_memmap.h"
#include "common_peripherals.h"

SCB_struct  * const SCB  = (SCB_struct* )(CORE_PERIPH_BASE + CORE_PBASE_SCB2_OFFSET);
STK_struct  * const STK  = (STK_struct* )(CORE_PERIPH_BASE + CORE_PBASE_SYSTICK_OFFSET);
NVIC_struct * const NVIC = (NVIC_struct*)(CORE_PERIPH_BASE + CORE_PBASE_NVIC1_OFFSET);
