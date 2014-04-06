#ifndef _CS_STRING_H
#define _CS_STRING_H


#include "stddef.h"

// TODO memcmp
int memcmp(const void* const s1, const void* const s2, size_t n);
void *memcpy(void* const dest, const void* const src, const size_t n);
void *memset(void* const start, const int f, const size_t n);


#endif
