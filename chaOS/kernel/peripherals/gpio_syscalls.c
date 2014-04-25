#include "inc/syscalls.h"
#include "inc/gpio.h"
#include "board.h"


int do_ledsoff(void) {
    GPIO_set_pins_mode(LED_PORT, BLUE_LED | GREEN_LED, GPIO_OUTPUT);
    GPIO_write(LED_PORT, BLUE_LED | GREEN_LED, ALL_OFF);
    return 0;
}

int do_led1on(void) {
    GPIO_set_pins_mode(LED_PORT, BLUE_LED, GPIO_OUTPUT);
    GPIO_write(LED_PORT, BLUE_LED, ALL_ON);
    return 0;
}
int do_led2on(void) {
    GPIO_set_pins_mode(LED_PORT, GREEN_LED, GPIO_OUTPUT);
    GPIO_write(LED_PORT, GREEN_LED, ALL_ON);
    return 0;
}
