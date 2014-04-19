/* defines common mcu family peripherals and related things like flags */

#ifndef MCUS_CORTEXM0_COMMON_PERIPHERALS_H
#define MCUS_CORTEXM0_COMMON_PERIPHERALS_H

/* --- System Control Block ----------------------------------------------------------------------*/

typedef struct {
    _I  uint32_t CPUID;     // CPU ID register                                      offset 0x00
    _IO uint32_t ICSR;      // Interrupt control and state register                 offset 0x04
    uint32_t     RESERVED0;
    _IO uint32_t AIRCR;     // Application interrupt and reset control register     offset 0x0C
    _IO uint32_t SCR;       // System control register                              offset 0x10
    _IO uint32_t CCR;       // Configuration and control register                   offset 0x14
    uint32_t     RESERVED1;
    _IO uint32_t SPHR[2];   // System priority handle register                      offset 0x1C
} SCB_struct;

/* --- SysTick timer -----------------------------------------------------------------------------*/

typedef struct {
    _IO uint32_t CSR;       // Control and status register                          offset 0x00
    _IO uint32_t RVR;       // Reload value register                                offset 0x04
    _IO uint32_t CVR;       // Current value register                               offset 0x08
    _I  uint32_t CALIB;     // Calibration value register                           offset 0x0C
} STK_struct;

/* --- Nested vectored interrupt controller ------------------------------------------------------*/

typedef struct {
    _IO uint32_t ISER;      // Interrupt set enable register                        offset 0x000
    uint32_t     RESERVED0[19];
    _IO uint32_t ICER;      // Interrupt clear enable register                      offset 0x080
    uint32_t     RESERVED1[4];
    _IO uint32_t ISPR;      // Interrupt set pending register                       offset 0x100
    uint32_t     RESERVED2[19];
    _IO uint32_t ICPR;      // Interrupt clear penging register                     offset 0x180
    uint32_t     RESERVED3[29];
    _IO uint32_t IPR[8];    // Interrupt priority register                          offset 0x300
}

#endif