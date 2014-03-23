#ifndef UTIL_MEM_H
#define UTIL_MEM_H


#include "device/core.h"

int bcmp(const void* const s1, const void* const s2, register size_t n);
void *memcpy(void* const dest, void* const src, register const size_t n);
void *memset(void* const start, register const int f, register const size_t n);

#endif
