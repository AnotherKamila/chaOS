#include "process_syscalls.h"
#include "process.h"
#include "scheduler.h"
#include "binfmt/common.h"
#include "binfmt/elf.h"


/* something like the POSIX `spawn` extension:
   http://support.sas.com/documentation/onlinedoc/sasc/doc700/html/lr2/zid-9275.htm
   (simply: async, returns the child's PID, the child is run whenever the scheduler wants to */
// TODO actual process insertion should go into process.c, really, but I want to sleep now :D
int do_spawn(program_img *file) {
    // load the executable image
    exec_img ximg;
    int r = load_elf(file, &ximg); // currently only ELF executables are supported
    if (r) return -1; // TODO errno

    // find an unused PID (=> a free slot in the process table)
    int pid = -1;
    for (int i = 0; i < current_process_table_size; ++i) {
        if (!(process_table[i].pflags & PFLAG_USED)) pid = i;
    }
    if (pid == -1) return -1; // TODO resize process_table instead

    process_table[pid] = {
        .p = { .pc = ximg.entry, .sp = ximg.end, .mem_start = ximg.start },
        .pid    = pid,
        .parent = sched_get_current_process(),
        .pflags = PFLAG_ALIVE | PFLAG_USED,
    };
    max_running_pid = max(pid, max_running_pid);
    return pid;
}

// TODO (somehow) make *absolutely* sure everyone executes exit()!
int do_exit(int status) {
    // TODO :D
    // what will happen here:
    //  - free memory
    //  - free process table entry
    //  - call scheduler to run something else
    return 0;
}
