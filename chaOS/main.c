/* kernel initialization */

#include "string.h"
#include "core.h"
#include "kernel/mm/mm.h"
#include "kernel/peripherals/initialization.h"
#include "kernel/panic.h"

/* linker-supplied addresses */
extern word _sidata, _sdata, _edata, _sbss, _ebss;

void _start(void) __attribute__((noreturn));

/* --- here starts bullshit --------------------------------------------------------------------- */
#include "drivers/gpio.h"
#include "binfmt/elf.h"

#define FROM_ADDR  (FLASH_BASE + 0x8000)

static void bullshit(void) {
    int *test = (int*)kmalloc(sizeof(int)); *test = 47;
    void* morestuff = kmalloc(47);
    int *array = (int*)kmalloc(1000*sizeof(int)); for (int i = 0; i < 1000; ++i) array[i] = 3000+i;
    kfree(morestuff);
    bool x = true; for (int i = 0; i < 1000; ++i) x = (array[i] == 3000+i);
    kassert(x);
    kfree(array);
    kassert(*test == 47);
    kfree(test);

    extern int do_spawn(program_img*);
    program_img program = { .img = (void*)FROM_ADDR };
    do_spawn(&program);
}
/* --- here it ends ----------------------------------------------------------------------------- */

static void kmain(void) {
    // initialize kernel subsystems
    mm_init();
    all_peripherals_init();

    bullshit();
}

void _start(void) {
    memcpy(&_sdata, &_sidata, &_edata - &_sdata);  // copy .data section to RAM
    memset(&_sbss, 0, &_ebss - &_sbss);  // initialize .bss section

    kmain();

    while (1) ; // TODO sleep
}
