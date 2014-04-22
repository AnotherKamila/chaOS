#include "inc/syscalls.h"
#include "inc/gpio.h"
#include "board.h"


int do_ledsoff(void) {
    GPIO_set_pins_mode(LED_PORT, LED1 | LED2, GPIO_OUTPUT);
    GPIO_write(LED_PORT, LED1 | LED2, ALL_OFF);
    return 0;
}

int do_led1on(void) {
    GPIO_set_pins_mode(LED_PORT, LED1, GPIO_OUTPUT);
    GPIO_write(LED_PORT, LED1, ALL_ON);
    return 0;
}
int do_led2on(void) {
    GPIO_set_pins_mode(LED_PORT, LED2, GPIO_OUTPUT);
    GPIO_write(LED_PORT, LED2, ALL_ON);
    return 0;
}
