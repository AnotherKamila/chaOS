#include "device/stm32f0.h"

int main(void) {
    RCC->AHBENR |= (1 << RCC_AHBENR_GPIOC_BIT);  // enable clock on GPIOC
    GPIOC->MODER = (1 << 2*8);  // set port 8 as output
    while (1) {
        int i = 0; while (++i < 200000) ;
        GPIOC->ODR ^= (1 << 8);
    }

    return 0;
}
