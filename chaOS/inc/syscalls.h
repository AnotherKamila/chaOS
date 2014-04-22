/* declares all system calls */

#ifndef INC_SYSCALLS_H
#define INC_SYSCALLS_H


// #if CHAOS_KERNEL
// #include "kernel/syscall.h"
// #else
// #include ""
// #endif
#include "kernel/syscall.h"

/* === process management ======================================================================= */

// SYSCALL(spawn, program_img *file)
// SYSCALL(exit, int retval)
// SYSCALL(wait, pid_t pid)

/* === peripherals ============================================================================== */

/* --- GPIO ------------------------------------------------------------------------------------- */
// TODO not really :D
SYSCALL(0, ledsoff);
SYSCALL(1, led1on);
SYSCALL(2, led2on);


#endif
