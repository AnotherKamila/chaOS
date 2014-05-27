#include "scheduler.h"
#include "context_switching.h"
#include "kernel/isr.h"
#include "common_drivers/systick.h"
#include "common_drivers/nvic.h"

#define TIME_SLICE  1000000 // for now in arbitrary units :D

// idle process -- kind of a sentinel
#define IDLE_PROCESS_STACK_SZ  32
intern word idle_process_stack[IDLE_PROCESS_STACK_SZ];
intern void idle_process(void) { while (true) ; } // TODO sleep instead
intern process idle = {
    .mem_start = NULL, .sp = idle_process_stack+IDLE_PROCESS_STACK_SZ-1,
    .pid = 0, .parent = 0, .pflags = PFLAG_ALIVE | PFLAG_USED,
};

void sched_init(void) {
    prepare_task_stack(&idle.sp, (void*)(uintptr_t)idle_process, NULL);
    process_table[0] = idle;
    max_running_pid = 0;
    current_process = PID_NONE;

    systick_config(SYSTICK_CLOCK_PROCESSOR, true);
    set_interrupt_priority(255, INT_SYSTICK);
    systick_set_top(TIME_SLICE);
}

void sched_run() {
    systick_enable();
    set_interrupt_pending(INT_SYSTICK, true);
}

// TODO should this go into process.[hc] instead?
intern bool is_runnable(pid_t pid) {
    // TODO will need more once tasks can block or sleep
    return (process_table[pid].pflags & PFLAG_USED) && (process_table[pid].pflags & PFLAG_ALIVE);
}

// the actual scheduler algorithm: task selection happens here
// a simple round robin scheme is used here
pid_t select_next_task() {
    pid_t next = (current_process == -1 ? 0 : current_process);
    do {
        ++next; if (next > max_running_pid) next = 1; // skip the idle process (0)
        if (is_runnable(next)) return next;
    } while (next != current_process);
    return 0; // if no runnable process was found above, run the idle process
}

// TODO switch_task() & co should be in process, not here
// handles switching stacks and restoring registers
// will only work when used as an ISR
void INTFN(INT_SYSTICK)(void) __attribute__((interrupt, optimize("omit-frame-pointer"), naked, flatten));
void INTFN(INT_SYSTICK)(void) {
    if (current_process != PID_NONE) {
        SAVE_CONTEXT();
        process_table[current_process].sp = get_psp();
    }
    current_process = select_next_task();
    set_psp(process_table[current_process].sp);
    LOAD_CONTEXT();
    EXC_RET_TO_THREAD();
}

void sched_run_next_task(void) {
    set_interrupt_pending(INT_SYSTICK, true);
}

