#include "panic.h"
#include "board.h"
#include "inc/gpio.h"

#pragma GCC diagnostic ignored "-Wunused-parameter" // msg is here to be accessible by the debugger
void panic(const char * const msg) {
    GPIO_enable(); GPIO_enable_port(PANIC_PORT);
    GPIO_set_pins_mode(PANIC_PORT, PANIC_LED, GPIO_OUTPUT);
    while (1) {
        for (int i = 0; i < 50000; ++i) ;
        GPIO_write(PANIC_PORT, PANIC_LED, ALL_ON);
        for (int i = 0; i < 50000; ++i) ;
        GPIO_write(PANIC_PORT, PANIC_LED, ALL_OFF);
    };
}
