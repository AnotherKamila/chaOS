#include "device/stm32f0.h"
#include "drivers/gpio.h"

int main(void) {
    GPIO_init(PORTC);
    GPIO_setup_pin(PORTC, 8, GPIO_MODE_OUTPUT, GPIO_PuPd_NOPULL, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_LOW);

    uint32_t *pattern = &RAM_BASE;
    while (1) {
        for (int i = 0; i < 32; ++i) {
            GPIO_pin_set(PORTC, 8, (*pattern & (1<<i)));
            for (int i = 0; i < 100000; ++i) ;
        }
    }

    return 0;
}
