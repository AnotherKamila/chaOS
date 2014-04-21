/* provides macros for defining interrupt service routines */

#ifndef KERNEL_ISR_H
#define KERNEL_ISR_H


#include "kernel/panic.h"

/**
 * Use this if you need to refer to an interrupt handler function by name. `INTFN(n)` resolves to
 * the internal name for the interrupt handler servicing interrupt `n`.
 */
#define INTFN(num)  _int ## num

/**
 * Use this to implement interrupt handler for the given interrupt number.
 * Usage: ISR(INT_something) { do_something(); ... }
 */
#define ISR(num)                                                                                   \
        void _int ## num (void) __attribute((interrupt));                                          \
        void _int ## num (void) /* { ... implementation ... } */

/**
 * Use this to explicitly not provide a default implementation for the given IRQ number.
 * When using this any code referencing the given IRQ handler will compile, but the function will be
 * NULL unless overridden somewhere.
 */
#define ISR_NULL(num)                                                                              \
        void _int ## num (void) __attribute__((interrupt, weak));                                  \

/**
 * Use this to panic on the given interrupt number unless an ISR implementation is provided
 * somewhere.
 */
#define ISR_UNEXPECTED(num)                                                                        \
        void _int ## num (void) __attribute__((interrupt, weak));                                  \
        void _int ## num (void) { chaos("Unexpected interrupt: " #num) }

// include the interrupt numbers right here for convenience
#include "hw_interrupts.h"
#include "system_interrupts.h"


#endif
