#include "process.h"
#include "scheduler.h"
#include "kernel/mm/mm.h"
#include "stack_manip.h"
#include "util/bit_manip.h"

process process_table[DEFAULT_PROCESS_TABLE_SIZE]; // TODO malloc this if it needs to be resizable
int current_process_table_size = DEFAULT_PROCESS_TABLE_SIZE;
int max_running_pid;

intern void *_fromfunc(void func(void)) {
// hopefully the compiler knows about the last bit of the function address... TODO make sure :D
    return (void*)(uint32_t)func; // double cast to avoid warning (I know I'm being mean here)
    // TODO maybe I'd be better off avoiding the nasty cast
}

void del_current_process() {
    pid_t pid = sched_get_current_process();
    kfree(process_table[pid].mem_start);
    bits_off(process_table[pid].pflags, PFLAG_ALIVE);
    if (pid == max_running_pid) { // update max_running_pid if necessary
        while (!process_table[max_running_pid].pflags & PFLAG_ALIVE) --max_running_pid;
    }
    sched_run_next_task();
}

pid_t new_process(const exec_img *ximg, pid_t parent) {
    // find an unused PID (=> a free slot in the process table)
    pid_t pid = 0;
    for (int i = 1; i < current_process_table_size; ++i) {
        if (!(process_table[i].pflags & PFLAG_USED)) {
            pid = i;
            break;
        }
    }
    if (pid == 0) return 0; // TODO resize process_table instead

    process newp = {
        .mem_start = ximg->start,
        .sp        = ximg->end, // TODO think about the funny stack
        .pid       = pid,
        .parent    = parent,
        .pflags    = PFLAG_ALIVE | PFLAG_USED,
    };
    prepare_task_stack(&newp.sp, ximg->entry, _fromfunc(del_current_process));
    process_table[pid] = newp;
    max_running_pid = max(pid, max_running_pid);

    return pid;
}
