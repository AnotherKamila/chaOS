#include "string.h"

// TODO add optimization for word-aligned cases everywhere

int memcmp(const void* const s1, const void* const s2, size_t n) {
    const char *p1 = (char*)s1, *p2 = (char*)s2;
    while (n--) {
        if (*p1 != *p2) {
            return p1 - p2;
        }
        ++p1;
        ++p2;
    }
    return 0;
}

void *memcpy(void* const dest, const void* const src, const size_t n) {
    const char *ps = src;
    char *pd = dest;
    while ((uintptr_t)ps < (uintptr_t)src+n) {
        *pd++ = *ps++;
    }
    return dest;
}

void *memset(void* const start, const int f, const size_t n) {
    char* p = start;
    while ((uintptr_t)p < (uintptr_t)start+n) {
        *(p++) = f;
    }
    return start;
}
