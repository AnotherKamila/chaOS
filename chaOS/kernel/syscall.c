// TODO this whole thing needs to be re-thought
// TODO get a header file :D

#include "core.h"
#include "inc/gpio.h"
#include "board.h"
#include "inc/interrupt_def.h"

typedef void (*syscall_fun_t)(void); // syscall_fun_t *f is a pointer to void f(void)

// test syscalls
void syscall0x00(void) { while (1) ; }
void syscall0x01(void) { GPIO_write(LED_PORT, LED1, ALL_ON); }
void syscall0x02(void) { GPIO_write(LED_PORT, LED2, ALL_ON); }

ISR(INT_SVCALL) {
    static const syscall_fun_t syscalls_table[] = {
        syscall0x00,
        syscall0x01,
        syscall0x02,
    };

    register int r0 __asm__("r0"); // r0 is used to pass the syscall type
    syscalls_table[r0]();
}
