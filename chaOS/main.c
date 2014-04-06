/*
 * kernel initialization
 */

#include "string.h"
#include "devices/core.h"

/* linker-supplied addresses */
extern word _sidata, _sdata, _edata, _sbss, _ebss;

void _start(void) __attribute__((noreturn));

/* --- here starts bullshit ------------------------------------------------- */
#include "drivers/gpio.h"
#include "binfmt/elf.h"

#define FROM_ADDR  (FLASH_BASE + 0x8000)

#pragma GCC diagnostic ignored "-Wmain"  // this `main` is different!
static void main(void) {
    GPIO_init(PORTC);
    GPIO_setup_pin(PORTC, 9, GPIO_MODE_OUTPUT, GPIO_PuPd_NOPULL, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_LOW);

    program_img program = { .img = (void*)FROM_ADDR };
    exec_img ximg;
    if (load_elf(&program, &ximg) == 0) {
        int ret = ximg.entry();
        if (ret == 42) {
            GPIO_pin_on(PORTC, 9);
        }
    }
}
/* --- here it ends --------------------------------------------------------- */

void _start(void) {
    memcpy(&_sdata, &_sidata, &_edata - &_sdata);  // copy .data section to RAM
    memset(&_sbss, 0, &_ebss - &_sbss);  // initialize .bss section

    main();

    while (1) ;  /* TODO sleep */
}
