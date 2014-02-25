/*
 * executes right after processor reset - copies data to RAM and sets default
 * IRQ handlers
 */

/* linker-supplied addresses */
extern void _estack(void);
extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

extern int main(void);

void start(void);

// so that the CPU state can be examined after an unexpected interrupt
void nmi_handler      (void) { while (1) ; }
void hardfault_handler(void) { while (1) ; }

/* vectors table */
// TODO when IRQ handlers are needed, they should obviously go somewhere
// else (and a mechanism to do that will be needed)
unsigned int * vectors[]
__attribute__ ((section(".isr_vector"))) = {  // stuff this in first (at 0x0)
    (unsigned int *) _estack,           // stack top
    (unsigned int *) start,             // entry point
    (unsigned int *) nmi_handler,
    (unsigned int *) hardfault_handler
};

/* copies/initializes data and enters `main` */
void start(void) {
    unsigned long *src, *dst;

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
