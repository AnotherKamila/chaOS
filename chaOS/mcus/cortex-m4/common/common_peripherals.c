/* define Cortex M4 common peripherals */

#include "common_memmap.h"
#include "common_peripherals.h"

STK_struct * const STK  = (STK_struct*)(CORE_PERIPH_BASE + CORE_PBASE_SYSTICK_OFFSET);
