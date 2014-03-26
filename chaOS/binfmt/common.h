#ifndef BINFMT_COMMON_H
#define BINFMT_COMMON_H

#include "device/core.h"

// it should be void func(void), and should get arguments + env + stuff one day
typedef int func();  // func *f is a pointer to int f()

inline static func *_tofunc(const uintptr_t addr) {
#ifdef _ARM_BLX_SHIT  // I hate them!
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
