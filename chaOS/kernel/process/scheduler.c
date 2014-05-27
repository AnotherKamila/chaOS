#include "scheduler.h"
#include "stack_manip.h"
#include "kernel/isr.h"
#include "common_drivers/systick.h"
#include "common_drivers/nvic.h"

#define TICKS  1000000 // determines how fast a task switch happens; for now in arbitrary units :D

intern void *_fromfunc(void func(void)) {
    // TODO last bit
    return (void*)(uint32_t)func; // double cast to avoid warning (I know I'm being mean here)
}

// idle process -- kind of a sentinel
intern void idle_process(void) __attribute__((naked,noreturn));
intern void idle_process(void) { __asm__ volatile ("nop"); while (true) ; } // TODO sleep instead
intern word idle_process_stack[32]; // TODO find out how much stack is needed to make it function properly
                             // note: probably 16 words -- sizeof(registers_frame_hw_t)+sizeof(registers_frame_sw_t)
void sched_init(void) {
    process idle = {
        .mem_start = NULL, .sp = idle_process_stack+31,
        .pid = 0, .parent = 0, .pflags = PFLAG_ALIVE | PFLAG_USED,
    };
    prepare_task_stack(&idle.sp, _fromfunc(idle_process), NULL);
    set_psp(idle.sp);
    process_table[0] = idle;
    max_running_pid = 0;
    current_process = PID_NONE;

    systick_config(SYSTICK_CLOCK_PROCESSOR, true);
    set_interrupt_priority(255, INT_SYSTICK);
    systick_set_top(TICKS);
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
// void INTFN(INT_SYSTICK)(void) __attribute__((interrupt, naked, optimize("omit-frame-pointer")));
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

// task switching should happen on SysTick interrupt (preemption) and PendSV (cooperative)
// void INTFN(INT_SYSTICK) __attribute__((alias("switch_task")));
// void INTFN(INT_PENDSV)  __attribute__((alias("switch_task")));


//     process_table[current_process].p.sp = get_psp();
//     pid_t next = select_next_task();
//     // switch_to_thread_stack();
//     set_psp(process_table[next].p.sp);
// }


// ISR(INT_SYSTICK) {
//     if (current_process != -1) save_registers();
//     switch_task();
//     *stack = THREAD_RETURN;
//     load_registers();
// }
// // TODO make pendsv handler an alias for this

// ISR(INT_PENDSV) { // switch task
//     save_registers();
//     // stack = (word*)get_msp();
//     __asm__ volatile ( "MRS %[stack], MSP" : [stack] "=r" (stack) );
//     switch_task();
//     instruction_sync_barrier();
//     load_registers();
// }

void sched_run_next_task(void) {
    set_interrupt_pending(INT_SYSTICK, true);
}

