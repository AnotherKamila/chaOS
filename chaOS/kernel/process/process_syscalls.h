#ifndef KERNEL_PROCESS_SYSCALLS
#define KERNEL_PROCESS_SYSCALLS


#include "process.h"
#include "binfmt/common.h"

int do_spawn(program_img *file);
int do_exit(int status);

#if HELL_FREEZES
int do_waitpid(void);
#endif


#endif
