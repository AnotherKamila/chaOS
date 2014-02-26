/*
 * executes right after processor reset - copies data to RAM and sets default
 * IRQ handlers
 */

#include <stdint.h>

/* linker-supplied addresses */
extern void _estack(void);
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void _start(void);

// so that the CPU state can be examined after an unexpected interrupt
void nmi_handler      (void) { while (1) ; }
void hardfault_handler(void) { while (1) ; }

/* vectors table */
// TODO when IRQ handlers are needed, they should obviously go somewhere
// else (and a mechanism to do that will be needed)
uint32_t * vectors[]
__attribute__ ((section(".isr_vector"))) = {  // stuff this in first (at 0x0)
    (uint32_t *) _estack,           // stack top
    (uint32_t *) _start,             // entry point
    (uint32_t *) nmi_handler,
    (uint32_t *) hardfault_handler
};

/* copies/initializes data and enters `main` */
void _start(void) {
    uint32_t *src, *dst;

    // copy .data section to RAM
    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata)
        *(dst++) = *(src++);

    // initialize .bss section
    dst = &_sbss;
    while (dst < &_ebss)
        *(dst++) = 0;

    main();

    while (1) ;
}
