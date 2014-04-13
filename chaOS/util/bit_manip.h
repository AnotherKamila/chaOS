/* utility macros for bit manipulation */

#ifndef _UTIL_BIT_MANIP_H
#define _UTIL_BIT_MANIP_H


#define bit_mon(x, m)  ((x) |= (m))
#define bit_moff(x, m)  ((x) &= ~(m))
#define bit_mtgl(x, m)  ((x) ^= (m))
#define bit_mset(x, m, v)  bit_moff(x, m); bit_mon(x, v)

#define bit_on(x, i)  bit_mon (x, 1 << (i))
#define bit_off(x, i)  bit_moff(x, 1 << (i))
#define bit_tgl(x, i)  bit_mtgl(x, 1 << (i))

#define bit_get(x, i)  ((x) & (1 << (i)))
#define bit_set(x, i, v)  if (bit_get(x, i) == !v) bit_tgl(x, i)


#endif
