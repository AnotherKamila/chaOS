/* process management */
// see process-notes.txt

#ifndef KERNEL_PROCESS_H
#define KERNEL_PROCESS_H


#include "core.h"
#include "binfmt/common.h"

typedef int pid_t;
#define PID_NONE  (-1)

#define DEFAULT_PROCESS_TABLE_SIZE  8

#define PFLAG_ALIVE  0x1
#define PFLAG_USED   0x2

typedef struct {
    union {
        struct { // live_process
            void *sp; // updated when context switching
            // other state is not necessary, as everything else (including the PC) is on the stack
            void* mem_start;
            // TODO process state should be here
            // one day stuff like open resources, scheduler info etc might appear here
        };
        struct { // zombie
            int exit_status;
        };
    };
    pid_t pid;
    pid_t parent;
    byte pflags;
} process;

extern process process_table[DEFAULT_PROCESS_TABLE_SIZE];
extern int current_process_table_size;
extern int max_running_pid;

/** initializes a new process from the given executable image */
pid_t new_process(const exec_img *ximg, pid_t parent);

/** frees resources of the current process, and sets its state in the process table to zombie */
void del_current_process();


#endif
