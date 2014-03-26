/*
 * kernel initialization
 */

#include "device/core.h"
#include "util/mem.h"


/* --- here starts bullshit ------------------------------------------------- */
#include "device/stm32f0.h"
#include "drivers/gpio.h"
#include "binfmt/elf.h"

#define FROM_ADDR  (FLASH_BASE + 0x8000)

#pragma GCC diagnostic ignored "-Wmain"  // this `main` is different!
void main(void) {
    GPIO_init(PORTC);
    GPIO_setup_pin(PORTC, 9, GPIO_MODE_OUTPUT, GPIO_PuPd_NOPULL, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_LOW);

    program_img program = { .img = (void*)FROM_ADDR };
    exec_img ximg;
    if (load_elf(&program, &ximg) == 0) {
        int ret = ximg.entry();
        if (ret == 42)
            GPIO_pin_on(PORTC, 9);
    }
}
/* --- here it ends --------------------------------------------------------- */


/* linker-supplied addresses */
extern void _estack(void);  // this type because of the vector table's type
extern word _sidata, _sdata, _edata, _sbss, _ebss;

static void _start(void) __attribute__((noreturn));

// so that the CPU state can be examined after an unexpected interrupt
static void nmi_handler      (void) { while (1) ; }
static void hardfault_handler(void) { while (1) ; }

/* vectors table */
// TODO when IRQ handlers are needed, they should obviously go somewhere
// else (and a mechanism to do that will be needed)
// TODO also, these are device-specific, put them somewhere suitable
void (*vectors[])(void)
__attribute__ ((section(".isr_vector"))) = {  // this is stuffed in first (at 0x0)
    &_estack           , // stack top
    &_start            , // entry point
    &nmi_handler       , // NMI handler
    &hardfault_handler   // hardfault handler
};

void _start(void) {
    memcpy(&_sdata, &_sidata, &_edata - &_sdata);  // copy .data section to RAM
    memset(&_sbss, 0, &_ebss - &_sbss);  // initialize .bss section

    main();

    while (1) ;  /* TODO sleep */
}
