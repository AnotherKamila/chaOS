#include "inc/gpio.h"
#include "gpio.h"
#include "util/bit_manip.h"

#define in_bounds(X)  ((X) <= PORT_MAX)

const Port ports[] = {
    { .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTA),
      ._GPIO_RCC_mask = AHBENR_IOPAEN },
    { .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTB),
      ._GPIO_RCC_mask = AHBENR_IOPBEN },
    { .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTC),
      ._GPIO_RCC_mask = AHBENR_IOPCEN },
    { .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTD),
      ._GPIO_RCC_mask = AHBENR_IOPDEN },
    { .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTE),
      ._GPIO_RCC_mask = AHBENR_IOPEEN },
    { .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTF),
      ._GPIO_RCC_mask = AHBENR_IOPFEN },
};

uint32_t GPIO_enable() {
    // STM32F0 GPIO peripheral is initialized per-port, not as a whole
    return GPIO_SUCCESS;
}

uint32_t GPIO_enable_port(const unsigned int port) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    bit_mon(RCC->AHBENR, ports[port]._GPIO_RCC_mask);
    return GPIO_SUCCESS;
}

uint32_t GPIO_set_pins_mode(const unsigned int port, const uint32_t pins,
                            const uint32_t mode_flags) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    // Interleave `pins` mask with itself because MODER and PUPDER have 2 bits per pin.
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
    uint32_t moder = ports[port].GPIO->MODER;
    bit_moff(moder, bit_mask);  // Reset required pins
    bit_mon(moder, settings_mask);  // Apply settings mask
    ports[port].GPIO->MODER = moder;
    //TODO enable interrupts


    /* --- OTYPER setting ----------------------------------------------------------------------- */

    if ((mode_flags & GPIO_OUTPUT) && (mode_flags & GPIO_OPENDRAIN)) {
        //TODO disable interrupts
        bit_mon(ports[port].GPIO->OTYPER, pins);
        //TODO enable interrupts
    } else {
        //TODO disable interrupts
        bit_moff(ports[port].GPIO->OTYPER, pins);
        //TODO enable interrupts
    }


    /* --- PUPDR setting ------------------------------------------------------------------------ */

    // Default value: no push/pull resistor
    settings_mask = 0;
    if (mode_flags & (GPIO_PULLING | GPIO_OPENDRAIN)) {
        // If GPIO is pulling intput or opendrain output, we must also set a pull/push resistor
        if (mode_flags & GPIO_PULLUP) {
            settings_mask = GPIO_PUPDR_UP_MASK & bit_mask;
        }
        else {
            settings_mask = GPIO_PUPDR_DOWN_MASK & bit_mask;
        }
    }

    //TODO disable interrupts
    uint32_t pupdr = ports[port].GPIO->PUPDR;
    bit_moff(pupdr, bit_mask); // Reset required pins
    bit_mon(pupdr, settings_mask); // Apply settings mask
    ports[port].GPIO->PUPDR = pupdr;
    //TODO enable interrupts


    /* --- OSPEEDR setting ---------------------------------------------------------------------- */

    //TODO speed setting

    return GPIO_SUCCESS;
}

uint32_t GPIO_write(const unsigned int port, const uint32_t pins, const uint32_t values) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    uint32_t sr = 0;
    // Writing 1 to lower 16 bits of BSRR controls which pins should be turned on
    bit_mon(sr, values & pins);
    // Writing 1 to higher 16 bits of BSRR controls which pins should be turned off
    bit_mon(sr, (~values & pins) << 16);
    ports[port].GPIO->BSRR = sr;
    return GPIO_SUCCESS;
}

uint32_t GPIO_read(const unsigned int port, const uint32_t pins, uint32_t * const data) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    *data = ports[port].GPIO->IDR & pins;
    return GPIO_SUCCESS;
}

uint32_t GPIO_extra_action(const unsigned int port, const uint32_t action,
                           uint32_t * const response) {
    if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;

    //TODO
    return GPIO_UNSUPPORTED_EXTRA;
}
