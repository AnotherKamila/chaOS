#include "process.h"

void context_switch(pid_t pid) {
    // TODO :D
    // the following is copied verbatim from my stack switch experiment for reference

    // TODO hide the following away in processor-specific code
    uint32_t control;
    __asm__ volatile ("mrs %[control], CONTROL" : [control] "=r" (control));
    control |= 1<<1;
    __asm__ volatile ("msr CONTROL, %[control]" : : [control] "r" (control));

    __asm__ volatile ("isb"); // instruction synchronisation barrier -- flushes the pipeline
    __asm__ volatile ("msr psp, %[sp]" : : [sp] "r" (newp.p.sp)); // set stack pointer

    // TODO insert into the table instead of this
    ximg.entry(); // TODO remove this - spawn() should be async, and this process should be run by
                  // the scheduler whenever it wants to (once there is a scheduler :D)

}
