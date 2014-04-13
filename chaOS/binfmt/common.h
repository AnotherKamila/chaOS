/* definitions common for all binary formats (types etc.) */

#ifndef BINFMT_COMMON_H
#define BINFMT_COMMON_H


#include "devices/core.h"

// should get arguments + env + stuff one day
typedef void func(void);  // func *f is a pointer to void f(void)

intern inline func *_tofunc(const uintptr_t addr) {
#if ARM_BLX_SHIT != 0  // see ARM_BLX_SHIT in devices/*/cpu.h
    return (func*)(addr | 0x1);
#else
    return (func*)addr;
#endif
}

// TODO should contain a file pointer or something, not a memory address one day
typedef struct {
    void *img;
} program_img;

typedef struct {
    void *begin, *end;
    func *entry;
} exec_img;


#endif
