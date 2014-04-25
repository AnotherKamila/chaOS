/* implements GPIO for STM32F0 / STM32F3 */

#include "gpio.h"
#include "util/bit_manip.h"

#define in_bounds(X)  ((X) <= PORT_MAX)

static const enum RCC_ahbenr port_enable_bit[] = {
    AHBENR_IOPAEN,
    AHBENR_IOPBEN,
    AHBENR_IOPCEN,
    AHBENR_IOPDEN,
    AHBENR_IOPEEN,
    AHBENR_IOPFEN,
};

uint32_t GPIO_enable() {
    // STM32F0 GPIO peripheral is initialized per-port, not as a whole
    return GPIO_SUCCESS;
}

uint32_t GPIO_enable_port(const unsigned int port) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    bit_mon(RCC->AHBENR, port_enable_bit[port]);
    return GPIO_SUCCESS;
}

uint32_t GPIO_set_pins_mode(const unsigned int port, const uint32_t pins,
                            const uint32_t mode_flags) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    // interleave `pins` mask with itself, (MODER and PUPDER have 2 bits per pin)
    uint32_t bit_mask = bits_expand(pins);

    /* --- MODER setting ------------------------------------------------------------------------ */

    uint32_t settings_mask = 0;

    // Prepare MODER settings mask
    if (mode_flags & GPIO_OUTPUT) {
        settings_mask = GPIO_MODER_OUTPUT_MASK & bit_mask;
    } else if (mode_flags & GPIO_ALTERNATE) {
        settings_mask = GPIO_MODER_ALT_MASK & bit_mask;
    } else if (mode_flags & GPIO_ANALOG) {
        settings_mask = GPIO_MODER_ANALOG_MASK & bit_mask;
    }

    //TODO disable interrupts
    uint32_t moder = GPIO[port]->MODER;
    bit_moff(moder, bit_mask); // Reset required pins
    bit_mon(moder, settings_mask); // Apply settings mask
    GPIO[port]->MODER = moder;
    //TODO enable interrupts


    /* --- OTYPER setting ----------------------------------------------------------------------- */

    if ((mode_flags & GPIO_OUTPUT) && (mode_flags & GPIO_OPENDRAIN)) {
        //TODO disable interrupts
        bit_mon(GPIO[port]->OTYPER, pins);
        //TODO enable interrupts
    } else {
        //TODO disable interrupts
        bit_moff(GPIO[port]->OTYPER, pins);
        //TODO enable interrupts
    }


    /* --- PUPDR setting ------------------------------------------------------------------------ */

    // default value: no push/pull resistor
    settings_mask = 0;
    if (mode_flags & (GPIO_PULLING | GPIO_OPENDRAIN)) {
        // if GPIO is pulling intput or opendrain output, we must also set a pull/push resistor
        if (mode_flags & GPIO_PULLUP) {
            settings_mask = GPIO_PUPDR_UP_MASK & bit_mask;
        }
        else {
            settings_mask = GPIO_PUPDR_DOWN_MASK & bit_mask;
        }
    }

    //TODO disable interrupts
    uint32_t pupdr = GPIO[port]->PUPDR;
    bit_moff(pupdr, bit_mask); // reset required pins
    bit_mon(pupdr, settings_mask); // apply settings mask
    GPIO[port]->PUPDR = pupdr;
    //TODO enable interrupts


    /* --- OSPEEDR setting ---------------------------------------------------------------------- */

    //TODO speed setting

    return GPIO_SUCCESS;
}

uint32_t GPIO_write(const unsigned int port, const uint32_t pins, const uint32_t values) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    uint32_t sr = 0;
    // writing 1 to lower 16 bits of BSRR controls which pins should be turned on
    bit_mon(sr, values & pins);
    // writing 1 to higher 16 bits of BSRR controls which pins should be turned off
    bit_mon(sr, (~values & pins) << 16);
    GPIO[port]->BSRR = sr;
    return GPIO_SUCCESS;
}

uint32_t GPIO_read(const unsigned int port, const uint32_t pins, uint32_t * const data) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    *data = GPIO[port]->IDR & pins;
    return GPIO_SUCCESS;
}

#if NOT_IMPLEMENTED
uint32_t GPIO_extra_action(const unsigned int port, const uint32_t action,
                           uint32_t * const response) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    //TODO
    return GPIO_UNSUPPORTED_EXTRA;
}
#endif
