/* declares interrupt handlers (overridde by declaring a (strong) function with the same name) */

#include "devices/core.h"

#define ISR_NOIMPL(name)  \
        void name(void) __attribute__((weak, alias("default_interrupt_handler")))

#define ISR(name)  \
        void name(void) __attribute__((weak)));                                                   \
        void name(void)  // expects to see { /* implementation */ }

#define EXC_NOIMPL(name)  \
        void name(void) __attribute__((weak, alias("default_exception_handler")))

// must be defined somewhere, e.g. in interrupts.c
void default_exception_handler(void) __attribute__((weak));
void default_interrupt_handler(void) __attribute__((weak));
