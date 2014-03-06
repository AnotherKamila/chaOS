/*
 * executes right after processor reset - copies data to RAM and sets default
 * IRQ handlers
 */

#include "core.h"
#include "binfmt/util.h"

/* linker-supplied addresses */
extern void _estack(void);
extern word _sidata;
extern word _sdata;
extern word _edata;
extern word _sbss;
extern word _ebss;

extern int main(void);

static void _start(void) __attribute__((noreturn));

// so that the CPU state can be examined after an unexpected interrupt
static void nmi_handler      (void) { while (1) ; }
static void hardfault_handler(void) { while (1) ; }

/* vectors table */
// TODO when IRQ handlers are needed, they should obviously go somewhere
// else (and a mechanism to do that will be needed)
word* vectors[]
__attribute__ ((section(".isr_vector"))) = {  // stuff this in first (at 0x0)
    (word*) _estack,           // stack top
    (word*) _start,            // entry point
    (word*) nmi_handler,       // NMI handler
    (word*) hardfault_handler  // hardfault handler
};

/* copies/initializes data and enters `main` */
void _start(void) {
    copy_region(&_sidata, &_sdata, &_edata);  // copy .data section to RAM
    padzero(&_sbss, &_ebss);  // initialize .bss section

    main();

    while (1) ;  /* TODO vypni periferie a sleep */
}
