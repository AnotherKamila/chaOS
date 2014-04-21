/* specifies the layout of the ISR vector table */

#include "core.h"
#include "kernel/panic.h"
#include "inc/interrupt_def.h"

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
// TODO either remove the need to do this explicitly, or generate with a preprocessor for loop
ISR_NULL( 0)
ISR_NULL( 1)
ISR_NULL( 2)
ISR_NULL( 3)
ISR_NULL( 4)
ISR_NULL( 5)
ISR_NULL( 6)
ISR_NULL( 7)
ISR_NULL( 8)
ISR_NULL( 9)
ISR_NULL(10)
ISR_NULL(11)
ISR_NULL(12)
ISR_NULL(13)
ISR_NULL(14)
ISR_NULL(15)
ISR_NULL(16)
ISR_NULL(17)
ISR_NULL(18)
ISR_NULL(19)
ISR_NULL(20)
ISR_NULL(21)
ISR_NULL(22)
ISR_NULL(23)
ISR_NULL(24)
ISR_NULL(25)
ISR_NULL(26)
ISR_NULL(27)
ISR_NULL(28)
ISR_NULL(29)
ISR_NULL(30)
ISR_NULL(31)

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
    // hardware interrupts
    // TODO maybe the following should be generated by a preprocessor for loop if I find the courage
    INTFN( 0),
    INTFN( 1),
    INTFN( 2),
    INTFN( 3),
    INTFN( 4),
    INTFN( 5),
    INTFN( 6),
    INTFN( 7),
    INTFN( 8),
    INTFN( 9),
    INTFN(10),
    INTFN(11),
    INTFN(12),
    INTFN(13),
    INTFN(14),
    INTFN(15),
    INTFN(16),
    INTFN(17),
    INTFN(18),
    INTFN(19),
    INTFN(20),
    INTFN(21),
    INTFN(22),
    INTFN(23),
    INTFN(24),
    INTFN(25),
    INTFN(26),
    INTFN(27),
    INTFN(28),
    INTFN(29),
    INTFN(30),
    INTFN(31),
};
