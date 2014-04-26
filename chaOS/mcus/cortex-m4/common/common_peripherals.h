/* defines common MCU family peripherals and related things like flags */

#ifndef MCUS_CORTEXM4_COMMON_PERIPHERALS_H
#define MCUS_CORTEXM4_COMMON_PERIPHERALS_H


#include "core.h"

/* --- SysTick timer -----------------------------------------------------------------------------*/

typedef struct {
    _IO uint32_t CSR;       // Control and status register                          offset 0x00
    _IO uint32_t RVR;       // Reload value register                                offset 0x04
    _IO uint32_t CVR;       // Current value register                               offset 0x08
    _O  uint32_t CALIB;     // Calibration value register                           offset 0x0C
} STK_struct;

enum STK_CSR_bits {
    CSR_ENABLE      = 0,
    CSR_TICKINT     = 1,
    CSR_CLKSOURCE   = 2,
    CSR_COUNTFLAG   = 16,
};

enum STK_CALIB_bits {
    CALIB_NOREF       = 31,
    CALIB_SKEW        = 30,
};


#endif
