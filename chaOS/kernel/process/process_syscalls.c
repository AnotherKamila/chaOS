#include "process_syscalls.h"
#include "process.h"
#include "scheduler.h"
#include "binfmt/common.h"
#include "binfmt/elf.h"


/* something like the POSIX `spawn` extension:
   http://support.sas.com/documentation/onlinedoc/sasc/doc700/html/lr2/zid-9275.htm
   (simply: async, returns the child's PID, the child is run whenever the scheduler wants to */
// TODO actual process insertion should go into process.c, really, but I want to sleep now :D
int do_spawn(const program_img *file) {
    // load the executable image
    exec_img ximg;
    int r = load_elf(file, &ximg); // currently only ELF executables are supported
    if (r) return -1; // TODO errno

    return new_process(&ximg, sched_get_current_process());
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
