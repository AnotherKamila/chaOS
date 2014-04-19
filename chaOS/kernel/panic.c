#include "panic.h"
#include "drivers/gpio.h"

#pragma GCC diagnostic ignored "-Wunused-parameter" // msg is here to be accessible by the debugger
void panic(const char * const msg) {
    GPIO_enable(); GPIO_enable_port(LED_PORT);
    GPIO_set_pins_mode(LED_PORT, LED1, GPIO_OUTPUT);
    while (1) {
        for (int i = 0; i < 50000; ++i) ;
        GPIO_write(LED_PORT, LED1, ALL_ON);
        for (int i = 0; i < 50000; ++i) ;
        GPIO_write(LED_PORT, LED1, ALL_OFF);
    };
}
