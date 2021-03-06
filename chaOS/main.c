/* kernel initialization */

#include "string.h"
#include "core.h"
#include "kernel/mm/mm.h"
#include "kernel/process/scheduler.h"
#include "kernel/peripherals/initialization.h"
#include "kernel/panic.h"

/* linker-supplied addresses */
extern byte _sidata, _sdata, _edata, _sbss, _ebss;

void _start(void) __attribute__((noreturn));

/* --- here starts the lame init (TODO get a real userspace init once the spawn syscall works) -- */
#define FROM_ADDR_1  (FLASH_BASE + 0x8000)
#define FROM_ADDR_2  (FLASH_BASE + 0x9000)
#define FROM_ADDR_3  (FLASH_BASE + 0xA000)
#include "binfmt/common.h"

static void lame_init(void) {
    extern int do_spawn(program_img*);
    program_img prg1 = { .img = (void*)FROM_ADDR_1 };
    do_spawn(&prg1);
    program_img prg2 = { .img = (void*)FROM_ADDR_2 };
    do_spawn(&prg2);
    program_img prg3 = { .img = (void*)FROM_ADDR_3 };
    do_spawn(&prg3);
}
/* --- here it ends ----------------------------------------------------------------------------- */

static void kmain(void) {
    // initialize kernel subsystems
    mm_init();
    sched_init();
    all_peripherals_init();

    lame_init();
    sched_run();
}

void _start(void) {
    memcpy(&_sdata, &_sidata, &_edata - &_sdata);  // copy .data section to RAM
    memset(&_sbss, 0, &_ebss - &_sbss);  // initialize .bss section

    kmain();

    while (1) ; // TODO sleep/shutdown
}
