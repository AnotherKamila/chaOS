#ifndef _DEVICES_CORE_H
#define _DEVICES_CORE_H


#include "Csucks.h"
#include "stdint.h"
#include "stddef.h"

/* --- types ----------------------------------------------------------------------------------- */

#define _IO volatile           // read/write registers
#define _I  volatile           // write-only registers
#define _O  readonly volatile  // read-only registers

typedef uint32_t word;

/* --- common setup ---------------------------------------------------------------------------- */
extern const void *_FLASH_BASE_L, *_RAM_BASE_L;
#define FLASH_BASE  ((uintptr_t)&_FLASH_BASE_L)
#define RAM_BASE    ((uintptr_t)&_RAM_BASE_L)

/* --- debug macros ---------------------------------------------------------------------------- */

#ifdef DEBUG
// TODO
//#define ASSERT(x)
#else
#endif


#endif
