/* process management */
// see process-notes.txt

#ifndef KERNEL_PROCESS_H
#define KERNEL_PROCESS_H


#include "core.h"

typedef uint8_t pid_t;

#define DEFAULT_PROCESS_TABLE_SIZE  8

typedef struct {
    void *pc; // updated when context switching
    void *sp; // updated when context switching
    // other state is not necessary, as everything else is on the stack
    void* mem_start;
    // TODO process state should be here just about now
    // one day stuff like open resources, scheduler info etc might appear here
} live_process;

typedef struct {
    int exit_status;
} zombie_process;

#define PFLAG_ALIVE  0x1
#define PFLAG_USED   0x2

typedef struct {
    union {
        live_process p;
        zombie_process z;
    };
    pid_t pid;
    pid_t parent;
    byte pflags;
} process;

process process_table[DEFAULT_PROCESS_TABLE_SIZE];
unsigned int current_process_table_size = DEFAULT_PROCESS_TABLE_SIZE;
unsigned int max_running_pid = 0;

void context_switch(pid_t pid);


#endif
