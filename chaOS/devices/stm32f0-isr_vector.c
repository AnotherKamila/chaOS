/* defines the ISR vector */

extern void _estack(void);  // linker-supplied address; this type because of the vector table's type
// TODO no, the above isn't nice -- the conversion should be even more explicit

extern void _start(void) __attribute__((noreturn));  // defined in main.c

// so that the CPU state can be examined after an unexpected interrupt
static void nmi_handler      (void) { while (1) ; }
static void hardfault_handler(void) { while (1) ; }

/* vectors table */
// TODO when more IRQ handlers are needed, either weak aliases or macros should be added for that
void (*isr_vector[])(void)
__attribute__ ((section(".isr_vector"))) = {  // this is stuffed in first (at 0x0)
    &_estack           , // stack top
    &_start            , // entry point
    &nmi_handler       , // NMI handler
    &hardfault_handler   // hardfault handler
};
