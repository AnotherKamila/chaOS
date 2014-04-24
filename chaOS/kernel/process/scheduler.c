#include "scheduler.h"
#include "core.h"

// idle process -- kind of a sentinel
void idle_process(void) {
    while (true) ;
}
word idle_process_stack[8]; // TODO find out how much stack is needed to make it function properly

void sched_init(void) {
    // insert the idle process as process 0
    process_table[0] = {
        .p = { .pc = idle_process, .sp = idle_process_stack+8 },
        .pid = 0, .parent = 0, .pflags = PFLAG_ALIVE | PFLAG_USED,
    };
    // TODO configure systick :D
}

intern pid_t current_task = 0;

intern bool is_runnable(pid_t pid) {
    // TODO will need more once tasks can block or sleep
    return (process_table[i].pflags & PFLAG_USED) && (process_table[i].pflags && PFLAG_ALIVE);
}

// the actual scheduler algorithm: task selection happens here
// a simple round robin scheme is used here
// I suck so much that it is O(N) where N is the total number of processes -- TODO :D
intern void switch_task(void) {
    // TODO it is quite possible that some state needs to be saved manually here
    if (max_running_pid == 0) context_switch(0); // no running tasks -- switch to the idle task
    pid_t i = current_task;
    pid_t next = 0; // if no runnable task is found below, the idle task will be run
    do {
        ++i; if (i == max_running_pid) i = 1; // skip the idle process (0)
        if (is_runnable(i)) next = i;
    } while (i != current_task);

    context_switch(next);
}

pid_t sched_get_current_process(void) {
    return current_task;
}

void sched_run_next_task(void) {
    // TODO reset timer, as this function may be called anytime
    switch_task();
}

void sched_run() {
    // TODO enable systick
    switch_task();
}

ISR(INT_SYSTICK) {
    switch_task();
}
