/* definitions common for all binary formats (types etc.) */

#ifndef BINFMT_COMMON_H
#define BINFMT_COMMON_H


#include "core.h"

intern inline void *_tofunc(const uintptr_t addr) {
#if ARM_BLX_SHIT // see ARM_BLX_SHIT in devices/*/cpu.h
    return (void*)(addr | 0x1);
#else
    return (void*)addr;
#endif
}

// TODO should contain a file pointer or something, not a memory address one day
typedef struct {
    void *img;
} program_img;

typedef struct {
    void *start, *end;
    void *entry;
} exec_img;


#endif
