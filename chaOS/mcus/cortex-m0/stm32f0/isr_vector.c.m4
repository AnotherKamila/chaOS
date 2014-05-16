/* specifies the layout of the ISR vector table */

include(forloop.m4)

#include "core.h"
#include "kernel/panic.h"
#include "kernel/isr.h"

extern void _estack(void); // linker-supplied address; this type because of the vector table's type
// TODO no, the above isn't nice -- the conversion should be more explicit

extern void _start(void) __attribute__((noreturn)); // defined in main.c

// create default implementations for all system interrupt handlers -- will cause a panic if the
// exception occurs unless they are overriden
ISR_UNEXPECTED( INT_NMI       )
ISR_UNEXPECTED( INT_HARDFAULT )
ISR_UNEXPECTED( INT_SVCALL    )
ISR_UNEXPECTED( INT_PENDSV    )
ISR_UNEXPECTED( INT_SYSTICK   )

// declare hardware interrupt handlers (note: the CPU will hardfault when an interrupt without an
// implementation occurs)
// HW interrupts are numbers 16 to 47 on this MCU
pp_forloop(i, 16, 47, ISR_NULL(i)` ')

// the linker script puts .isr_vector at 0x0
void (*isr_vector[])(void) __attribute__((section(".isr_vector"))) = {
    _estack ,// stack top
    _start  ,// entry point

    // system interrupts
    INTFN(INT_NMI),
    INTFN(INT_HARDFAULT),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    INTFN(INT_SVCALL),
    NULL,
    NULL,
    INTFN(INT_PENDSV),
    INTFN(INT_SYSTICK),

    // hardware interrupts (numbers 16 to 47 on this MCU)
    pp_forloop(i, 16, 47, INTFN(i)`, ')
};
