#ifndef _DEVICES_STM32F0_PERIPHERALS_H
#define _DEVICES_STM32F0_PERIPHERALS_H


#include "devices/core.h"

/* === memory map ============================================================================== */

#define PERIPH_BASE  0x40000000

#define APB_PERIPH_BASE  (PERIPH_BASE)
#define AHBPERIPH_BASE   (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE  (PERIPH_BASE + 0x08000000)

/* --- reset and clock control ----------------------------------------------------------------- */

typedef struct {
    _IO uint32_t CR;        // clock control register                 offset 0x00
    _IO uint32_t CFGR;      // clock configuration register           offset 0x04
    _IO uint32_t CIR;       // clock interrupt register               offset 0x08
    _IO uint32_t APB2RSTR;  // APB2 peripheral reset register         offset 0x0C
    _IO uint32_t APB1RSTR;  // APB1 peripheral reset register         offset 0x10
    _IO uint32_t AHBENR;    // AHB peripheral clock register          offset 0x14
    _IO uint32_t APB2ENR;   // APB2 peripheral clock enable register  offset 0x18
    _IO uint32_t APB1ENR;   // APB1 peripheral clock enable register  offset 0x1C
    _IO uint32_t BDCR;      // Backup domain control register         offset 0x20
    _IO uint32_t CSR;       // clock control & status register        offset 0x24
    _IO uint32_t AHBRSTR;   // AHB peripheral reset register          offset 0x28
    _IO uint32_t CFGR2;     // clock configuration register 2         offset 0x2C
    _IO uint32_t CFGR3;     // clock configuration register 3         offset 0x30
    _IO uint32_t CR2;       // clock control register 2               offset 0x34
} RCC_struct;

#define RCC  ((RCC_struct*)(AHBPERIPH_BASE + 0x00001000))

/* --- GPIO ------------------------------------------------------------------------------------ */

typedef struct {
    _IO uint32_t MODER;       // mode register                   offset 0x00
    _IO uint16_t OTYPER;      // output type register            offset 0x04
    uint16_t    RESERVED0;
    _IO uint32_t OSPEEDR;     // output speed register           offset 0x08
    _IO uint32_t PUPDR;       // pull-up/pull-down register      offset 0x0C
    _IO uint16_t IDR;         // input data register             offset 0x10
    uint16_t    RESERVED1;
    _IO uint16_t ODR;         // output data register            offset 0x14
    uint16_t    RESERVED2;
    _IO uint32_t BSRR;        // bit set/reset register          offset 0x18
    _IO uint32_t LCKR;        // configuration lock register     offset 0x1C
    _IO uint32_t AFR[2];      // alternate function registers    offset 0x20-0x24
    _IO uint16_t BRR;         // bit reset register              offset 0x28
    uint16_t    RESERVED3;
} GPIO_struct;

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
#define GPIO_OSPEED_LOW  GPIO_OSPEED_2MHz
#define GPIO_OSPEED_HIGH GPIO_OSPEED_50MHz

/* === ports definition ======================================================================== */

#define  NPINS  16  // pins per port

typedef struct {
    GPIO_struct* GPIO;
    int _GPIO_RCC_bit;
} Port;

static const Port PORTA = {
    .GPIO = (GPIO_struct*)(AHBPERIPH_BASE),
    ._GPIO_RCC_bit = 17,
};
static const Port PORTB = {
    .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + 0x00000400),
    ._GPIO_RCC_bit = 18,
};
static const Port PORTC = {
    .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + 0x00000800),
    ._GPIO_RCC_bit = 19,
};


#endif
