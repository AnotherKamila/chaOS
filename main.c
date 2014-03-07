#include "device/stm32f0.h"
#include "drivers/gpio.h"

int main(void) {
    GPIO_init(PORTC);
    GPIO_setup_pin(PORTC, 8, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_LOW);

    int i;
    while (1) {
        i = 0; while (++i < 50000) ;
        GPIO_pin_on(PORTC, 8);
        i = 0; while (++i < 200000) ;
        GPIO_pin_off(PORTC, 8);
    }

    return 0;
}
