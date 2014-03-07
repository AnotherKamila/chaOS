#include <stdarg.h>  // TODO learn to use this to make otype and ospeed optional
#include "device/stm32f0.h"
#include "util/bit_manip.h"

inline static void GPIO_init(const Port port) {
    bit_on(RCC->AHBENR, port._GPIO_RCC_bit);  // enable clock on that port
}

inline static void GPIO_setup_pin(const Port port, int pin, GPIO_mode mode, GPIO_otype otype, GPIO_ospeed ospeed) {
    bit_mset(port.GPIO->MODER,   0x3 << 2*pin, mode   << 2*pin);  // 2 bits per pin
    bit_mset(port.GPIO->OTYPER,  0x1 <<   pin, otype  << 2*pin);  // 1 bit per pin
    bit_mset(port.GPIO->OSPEEDR, 0x3 << 2*pin, ospeed << 2*pin);  // 2 bits per pin
}

inline static void GPIO_pin_on(const Port port, int pin) {
    // TODO assert that it is set as output
    port.GPIO->BSRR = 1 << pin;
}

inline static void GPIO_pin_off(const Port port, int pin) {
    // TODO assert that it is set as output
    port.GPIO->BRR = 1 << pin;
}
