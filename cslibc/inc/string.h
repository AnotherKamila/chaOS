#ifndef _CS_STRING_H
#define _CS_STRING_H


#include "stddef.h"

// TODO memcmp
int memcmp(const void *s1, const void *s2, register size_t n);
void *memcpy(void* const dest, void* const src, register const size_t n);
void *memset(void* const start, register const int f, register const size_t n);


#endif
