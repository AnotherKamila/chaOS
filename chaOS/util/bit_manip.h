/* utility macros for bit manipulation */

#ifndef UTIL_BIT_MANIP_H
#define UTIL_BIT_MANIP_H

#include "stdint.h"

#define bit_mon(x, m)  ((x) |= (m))
#define bit_moff(x, m)  ((x) &= ~(m))
#define bit_mtgl(x, m)  ((x) ^= (m))
#define bit_mset(x, m, v)  bit_moff(x, m); bit_mon(x, v)

#define bit_on(x, i)  bit_mon (x, 1 << (i))
#define bit_off(x, i)  bit_moff(x, 1 << (i))
#define bit_tgl(x, i)  bit_mtgl(x, 1 << (i))

#define bit_get(x, i)  ((x) & (1 << (i)))
#define bit_set(x, i, v)  if (bit_get(x, i) == !v) bit_tgl(x, i)

#define DIV4(x) ((x) >> 2)
#define MOD4(x) ((x) & 0x3)
#define MUL8(x) ((x) << 3)

// align x up to the nearest multiple of `to`; `to` must be a power of 2
#define ALIGN(to, x)  ((x+(to)-1) & ~((to)-1))

uint32_t bits_stretch(uint32_t x);
uint32_t bits_expand(uint32_t x);


#endif
