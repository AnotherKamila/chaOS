#include "devices/core.h"
#include "inc/gpio.h"
#include "devices/stm32f0/drivers/gpio.h"

typedef void (*syscall_fun_t)(void);  // syscall_fun_t *f is a pointer to void f(void)

void SVcall_handler(void) __attribute__((interrupt("SVC")));

// test syscalls
void syscall0x00(void) { while (1) ; }
void syscall0x01(void) { GPIO_write(PORTC, (1 << 8), (1 << 8)); }
void syscall0x02(void) { GPIO_write(PORTC, (1 << 8), 0); }

void SVcall_handler(void) {

    const syscall_fun_t syscalls_table[] = {
        syscall0x00,
        syscall0x01,
        syscall0x02,
    };

    register int r0 __asm__("r0");  // r0 is used to pass the syscall type
    syscalls_table[r0]();
}
