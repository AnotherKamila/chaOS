/* includes useful things, defines some types and some constants; included almost everywhere */

#ifndef CORE_H
#define CORE_H


#include "Csucks.h"
#include "stdint.h"

/* --- types ------------------------------------------------------------------------------------ */

#define _IO volatile          // read/write memory-mapped peripherals
#define _I  volatile          // write-only memory-mapped peripherals
#define _O  readonly volatile // read-only memory-mapped peripherals

typedef uint32_t word;

/* --- common setup ----------------------------------------------------------------------------- */

extern const void *_FLASH_BASE_L, *_RAM_BASE_L;
#define FLASH_BASE  ((uintptr_t)&_FLASH_BASE_L)
#define RAM_BASE    ((uintptr_t)&_RAM_BASE_L)


#endif
