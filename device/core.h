#ifndef DEVICE_CORE_H
#define DEVICE_CORE_H

#include <stdint.h>

/* --- types ---------------------------------------------------------------- */

#define IO volatile        // read/write registers
#define O  volatile        // read-only registers
#define I  const volatile  // write-only registers

typedef uint32_t size_t;
typedef int32_t  ssize_t;

typedef uint32_t word;

#endif
