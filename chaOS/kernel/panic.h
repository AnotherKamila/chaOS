/* defines the kernel panic handler, plus the `kassert` macro to panic when an assertion fails */

#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H


#include "util/stringify.h"

#define panic(msg)  kpanic(__FILE__ ":" STRINGIFY(__LINE__) ": " msg);
void kpanic(const char * const msg) __attribute__((noreturn));

#if NDEBUG
#define kassert(ignore)  ((void) 0) // nothing
#else
#define kassert(x)  if (!(x)) panic("Assertion `" #x "' failed!");
#endif


#endif
