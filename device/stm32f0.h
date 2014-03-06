#ifndef DEVICE_STM32F0_H
#define DEVICE_STM32F0_H

#include "core.h"

/* === memory map =========================================================== */

#define PERIPH_BASE  0x40000000

#define APB_PERIPH_BASE  (PERIPH_BASE)
#define AHBPERIPH_BASE   (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE  (PERIPH_BASE + 0x08000000)

/* --- reset and clock control ---------------------------------------------- */

#define RCC_BASE  (AHBPERIPH_BASE + 0x00001000)

typedef struct {
    IO uint32_t CR;        // clock control register                 offset 0x00
    IO uint32_t CFGR;      // clock configuration register           offset 0x04
    IO uint32_t CIR;       // clock interrupt register               offset 0x08
    IO uint32_t APB2RSTR;  // APB2 peripheral reset register         offset 0x0C
    IO uint32_t APB1RSTR;  // APB1 peripheral reset register         offset 0x10
    IO uint32_t AHBENR;    // AHB peripheral clock register          offset 0x14
    IO uint32_t APB2ENR;   // APB2 peripheral clock enable register  offset 0x18
    IO uint32_t APB1ENR;   // APB1 peripheral clock enable register  offset 0x1C
    IO uint32_t BDCR;      // Backup domain control register         offset 0x20 
    IO uint32_t CSR;       // clock control & status register        offset 0x24
    IO uint32_t AHBRSTR;   // AHB peripheral reset register          offset 0x28
    IO uint32_t CFGR2;     // clock configuration register 2         offset 0x2C
    IO uint32_t CFGR3;     // clock configuration register 3         offset 0x30
    IO uint32_t CR2;       // clock control register 2               offset 0x34
} RCC_struct;

#define RCC  ((RCC_struct*)RCC_BASE)

typedef enum {
    RCC_AHBENR_GPIOA_BIT = 17,  // GPIOA clock enable bit
    RCC_AHBENR_GPIOB_BIT = 18,  // GPIOB clock enable bit
    RCC_AHBENR_GPIOC_BIT = 19   // GPIOC clock enable bit
} RCC_register_bits;

/* --- GPIO ----------------------------------------------------------------- */

#define GPIOA_BASE  (AHB2PERIPH_BASE + 0x00000000)
#define GPIOB_BASE  (AHB2PERIPH_BASE + 0x00000400)
#define GPIOC_BASE  (AHB2PERIPH_BASE + 0x00000800)

typedef struct {
    IO uint32_t MODER;       // mode register                   offset 0x00
    IO uint16_t OTYPER;      // output type register            offset 0x04
    uint16_t    RESERVED0;   // reserved
    IO uint32_t OSPEEDR;     // output speed register           offset 0x08
    IO uint32_t PUPDR;       // pull-up/pull-down register      offset 0x0C
    IO uint16_t IDR;         // input data register             offset 0x10
    uint16_t    RESERVED1;   // reserved
    IO uint16_t ODR;         // output data register            offset 0x14
    uint16_t    RESERVED2;   // reserved
    IO uint32_t BSRR;        // bit set/reset register          offset 0x18
    IO uint32_t LCKR;        // configuration lock register     offset 0x1C
    IO uint32_t AFR[2];      // alternate function registers    offset 0x20-0x24
    IO uint16_t BRR;         // bit reset register              offset 0x28
    uint16_t    RESERVED3;   // reserved
} GPIO_struct;

#define GPIOA  ((GPIO_struct*)GPIOA_BASE)
#define GPIOB  ((GPIO_struct*)GPIOB_BASE)
#define GPIOC  ((GPIO_struct*)GPIOC_BASE)

#endif
