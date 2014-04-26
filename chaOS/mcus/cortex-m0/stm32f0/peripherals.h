/* defines MCU peripherals and related things like flags */

#ifndef MCUS_CORTEXM0_STM32F0_PERIPHERALS_H
#define MCUS_CORTEXM0_STM32F0_PERIPHERALS_H


#include "core.h"

/* --- reset and clock control ------------------------------------------------------------------ */

typedef struct {
    _IO uint32_t CR;       // clock control register                 offset 0x00
    _IO uint32_t CFGR;     // clock configuration register           offset 0x04
    _IO uint32_t CIR;      // clock interrupt register               offset 0x08
    _IO uint32_t APB2RSTR; // APB2 peripheral reset register         offset 0x0C
    _IO uint32_t APB1RSTR; // APB1 peripheral reset register         offset 0x10
    _IO uint32_t AHBENR;   // AHB peripheral clock register          offset 0x14
    _IO uint32_t APB2ENR;  // APB2 peripheral clock enable register  offset 0x18
    _IO uint32_t APB1ENR;  // APB1 peripheral clock enable register  offset 0x1C
    _IO uint32_t BDCR;     // Backup domain control register         offset 0x20
    _IO uint32_t CSR;      // clock control & status register        offset 0x24
    _IO uint32_t AHBRSTR;  // AHB peripheral reset register          offset 0x28
    _IO uint32_t CFGR2;    // clock configuration register 2         offset 0x2C
    _IO uint32_t CFGR3;    // clock configuration register 3         offset 0x30
    _IO uint32_t CR2;      // clock control register 2               offset 0x34
} RCC_struct;

enum RCC_AHBENR_bits {
    AHBENR_TSCEN   = 24,
    AHBENR_IOPFEN  = 22,
    AHBENR_IOPEEN  = 21,
    AHBENR_IOPDEN  = 20,
    AHBENR_IOPCEN  = 19,
    AHBENR_IOPBEN  = 18,
    AHBENR_IOPAEN  = 17,
    AHBENR_CRCEN   = 6,
    AHBENR_FLITFEN = 4,
    AHBENR_SRAMEN  = 2,
    AHBENR_DMAEN   = 0,
};

/* --- GPIO ------------------------------------------------------------------------------------- */

typedef struct {
    _IO uint32_t MODER;     // mode register                 offset 0x00
    _IO uint16_t OTYPER;    // output type register          offset 0x04
    _RV uint16_t RESERVED0;
    _IO uint32_t OSPEEDR;   // output speed register         offset 0x08
    _IO uint32_t PUPDR;     // pull-up/pull-down register    offset 0x0C
    _IO uint16_t IDR;       // input data register           offset 0x10
    _RV uint16_t RESERVED1;
    _IO uint16_t ODR;       // output data register          offset 0x14
    _RV uint16_t RESERVED2;
    _IO uint32_t BSRR;      // bit set/reset register        offset 0x18
    _IO uint32_t LCKR;      // configuration lock register   offset 0x1C
    _IO uint32_t AFR[2];    // alternate function registers  offset 0x20-0x24
    _IO uint16_t BRR;       // bit reset register            offset 0x28
    _RV uint16_t RESERVED3;
} GPIO_struct;

#define GPIO_MODER_INPUT_MASK   0x00000000
#define GPIO_MODER_OUTPUT_MASK  0x55555555
#define GPIO_MODER_ALT_MASK     0xAAAAAAAA
#define GPIO_MODER_ANALOG_MASK  0xFFFFFFFF

#define GPIO_PUPDR_NOPULL_MASK  0x00000000
#define GPIO_PUPDR_UP_MASK      0x55555555
#define GPIO_PUPDR_DOWN_MASK    0xAAAAAAAA

enum GPIO_mode {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_ANALOG = 0x3,
    GPIO_MODE_ALT    = 0x2,
};

enum GPIO_otype {
    GPIO_OTYPE_PUSHPULL  = 0x0,
    GPIO_OTYPE_OPENDRAIN = 0x1,
};

enum GPIO_PuPd {
    GPIO_PuPd_NOPULL = 0x0,
    GPIO_PuPd_UP     = 0x1,
    GPIO_PuPd_DOWN   = 0x2,
};

enum GPIO_ospeed {
    GPIO_OSPEED_2MHz  = 0x0,
    GPIO_OSPEED_10MHz = 0x1,
    GPIO_OSPEED_50MHz = 0x3,
};


#endif
