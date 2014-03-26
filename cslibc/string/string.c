#include <string.h>

// TODO add optimization for word-aligned cases everywhere

int bcmp(const void* const s1, const void* const s2, register size_t n) {
    register char *p1 = (char*)s1, *p2 = (char*)s2;
    while (n--)
        if (*p1++ != *p2++)
            break;
    return n;
}

void *memcpy(void* const dest, void* const src, register const size_t n) {
    register char *ps = src, *pd = dest;
    while ((uintptr_t)ps < (uintptr_t)src+n)
        *pd++ = *ps++;
    return dest;
}

void *memset(void* const start, register const int f, register const size_t n) {
    register char* p = start;
    while ((uintptr_t)p < (uintptr_t)start+n)
        *(p++) = f;
    return start;
}
