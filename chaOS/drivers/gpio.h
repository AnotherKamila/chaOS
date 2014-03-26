#ifndef DRIVERS_GPIO_H
#define DRIVERS_GPIO_H

#include "device/stm32f0.h"
#include "util/bit_manip.h"

inline static void GPIO_init(const Port port) {
    bit_on(RCC->AHBENR, port._GPIO_RCC_bit);  // enable clock on that port
}

// TODO use a struct to initialize - somehow
// TODO I should most probably make these accept a mask of pins instead of a single number, this is stupid

inline static void GPIO_setup_pin(const Port port, uint8_t pin, enum GPIO_mode mode, enum GPIO_otype otype, enum GPIO_PuPd pupd, enum GPIO_ospeed ospeed) {
    bit_mset(port.GPIO->MODER,   0x3 << 2*pin, mode   << 2*pin);  // 2 bits per pin
    bit_mset(port.GPIO->PUPDR,   0x3 << 2*pin, pupd   << 2*pin);  // 2 bits per pin
    bit_mset(port.GPIO->OTYPER,  0x1 <<   pin, otype  <<   pin);  // 1 bit per pin
    bit_mset(port.GPIO->OSPEEDR, 0x3 << 2*pin, ospeed << 2*pin);  // 2 bits per pin
}

// TODO
inline static void GPIO_setup_alt(const Port port, uint8_t pin, uint32_t mode) {
    // AFR is a 2x32bit register, with AFR[0] for lower pins, AFR[1] for higher ones, so the following select the right thing depending on
    bit_mset(port.GPIO->AFR[(1<<pin)>>0x3], 0x3 << 2*pin, mode << 2*pin);
}

// the following are atomic access (rather than read-modify-write)
inline static void GPIO_pin_on(const Port port, uint8_t pin) {
    // TODO assert that it is set as output
    port.GPIO->BSRR = 1 << pin;
}
inline static void GPIO_pin_off(const Port port, uint8_t pin) {
    // TODO assert that it is set as output
    port.GPIO->BRR = 1 << pin;
}
inline static void GPIO_pin_set(const Port port, uint8_t pin, bool value) {
    if (value) GPIO_pin_on(port, pin);
    else GPIO_pin_off(port, pin);
}


#endif
