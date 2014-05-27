#ifndef KERNEL_PROCESS_SCHEDULER_H
#define KERNEL_PROCESS_SCHEDULER_H


#include "process.h"

/** Initializes the scheduler. Must be called before any tasks exist. */
void sched_init(void);

/** starts running tasks, therefore taking control from the kernel */
void sched_run(void);

/**
 * tells the scheduler to immediately switch to another task instead of allowing the current task
 * to run until the end of its time quantum
 */
void sched_run_next_task(void);


#endif
