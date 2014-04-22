// TODO this whole thing needs to be re-thought
// TODO get a header file :D

#include "syscall.h"
#include "core.h"
#include "kernel/isr.h"


// extern int do_led1on(void);
// extern int do_led2on(void);

extern int SYSCFN(0) (void);
extern int SYSCFN(1) (void);
extern int SYSCFN(2) (void);


// TODO
intern int (* const syscalls_table[])(void) = {
    SYSCFN(0),
    SYSCFN(1),
    SYSCFN(2),
};

ISR(INT_SVCALL) {
    register int r0 __asm__("r0"); // r0 is used to pass the syscall number
    // TODO arguments
    syscalls_table[r0]();
}
