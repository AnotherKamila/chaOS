#include "vendor/stm32f0xx.h"

int main(void) {

    GPIOC->MODER = (1 << 16) | (1 << 18);

    int i = 0;
    while (1) {
        if (++i == 1000000) {
            i = 0;
            GPIOC->ODR ^= (1 << 8);
        }
    }

    return 0;
}
