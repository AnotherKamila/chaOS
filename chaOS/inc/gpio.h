#ifndef INC_GPIO_H
#define INC_GPIO_H

#include "devices/core.h"
#include "util/bit_manip.h"

//Bit table for GPIO_set_pins_mode mode_flags. (If the conditions are not met the bit is ignored)
/*  Bit     0               1               Conditions
 *  0       GPIO            Alternate
 *  1       Digital         Analog          Not alternate.
 *  2       Input           Output          Not alternate. Analog output mode may be ignored by some devices.
 *  3       Floating        Pulling         Not alternate. Input.
 *  3       Pushpull        Opendrain       Output. Ignored by some devices if configured as Alternate.
 *  4       Pull/Push down  Pull/Push up    Configured as either pulling input or opendrain output.
 */
// 0 defaults to a floating input.
//Rest of the pins may be a device-specific settings documented in each individual driver file.

#define GPIO_ALTERNATE  1
#define GPIO_ANALOG     2
#define GPIO_INPUT      0
#define GPIO_FLOATING   0
#define GPIO_PULLING    8
#define GPIO_PULLDOWN   0
#define GPIO_PULLUP     16
#define GPIO_OUTPUT     4
#define GPIO_PUSHPULL   0
#define GPIO_OPENDRAIN  8

#define GPIO_SUCCESS            0
#define GPIO_PORT_OUT_OF_RANGE  1
#define GPIO_UNSUPPORTED_EXTRA  2

/**
 * Turn on the GPIO peripheral.
 *
 * This function enables the GPIO peripheral on devices where it
 * is applicable. Function call will be ignored on devices where
 * GPIO is enabled by default.
 */
uint32_t GPIO_enable();

/**
 * Enable port.
 *
 * This function enables the port 'port'. Function call will
 * be ignored on devices where all ports are enabled by default.
 * Function will return error if the port is out of range or
 * writing to the GPIO is locked.
 */
uint32_t GPIO_enable_port(const unsigned int port);

/**
 * Configure pins.
 *
 * This function configures pins 'pins' of a port 'port'.
 * There is no sanity checking performed on the mode_flags. Illogical
 * values will have an undefined behaviour. The function will return error
 * value if the port is out of range, pins mask contains pins out of range,
 * selected mode could not be set nor emulated on this particular GPIO or
 * writing to the GPIO is locked.
 * \param mode_flags defaults to a floating input.
 *                   GPIO_INPUT | GPIO_PULLING defaults to a input with pulldown
 *                   GPIO_OUTPUT defaults to a pushpull output
 *                   GPIO_OUTPUT | GPIO_OPENDRAIN defaults to a opendrain output with a pulldown resistor.
 *                   GPIO_INPUT | GPIO_OUTPUT has undefined behaviour (actually the pin will be configured as
 *                   a pushpull output, but why the hell would you do it this way?!)
 * \param pins is a bitmask of pins to configure
 */
uint32_t GPIO_set_pins_mode(const unsigned int port, const uint32_t pins, const uint32_t mode_flags);

/**
 * Write value to the pins.
 *
 * This function sets logical state to the pins. Setting logical state
 * to pins configured as input has undefined behaviour. This function
 * will return error value if the port is out of range or pins mask contains
 * pins out of range, or writing to the GPIO is locked.
 * \param pins is a bitmask of pins to set
 */
uint32_t GPIO_write(const unsigned int port, const uint32_t pins, const uint32_t values);

/**
 * Read the value on the pins.
 *
 * This function reads the digital values present on the input pins.
 * Reading from pins conigured as output has undefined behavior. This
 * function will return error value if the port is out of range or
 * pins mask contains pins out of range.
 * \param pins is a bitmask of pins to set
 * \param *data is pointer to a variable where bitmask of data present on the pins will be written
 */
uint32_t GPIO_read(const unsigned int port, const uint32_t pins, uint32_t * const data);

/**
 * Take a custom action on the GPIO.
 *
 * List of possible actions is documented for each GPIO separately.
 * This function is here to support unusual features of the GPIO which
 * can not be generalized.
 * Example of such feature is STM32's locking of GPIO to prevent writing.
 * \param action is a bitmask of a custom action documented separately
 * \param *response is variable to which an optional response will be written
 */
uint32_t GPIO_extra_action(const unsigned int port, const uint32_t action, uint32_t * const response);

/**
 * convenience macros for manipulating a single pin or all pins, or setting pins to just 0 or 1
 */
#define PIN(i)   (1u<<(i))
#define NONE     ((uint32_t)0u)
#define ALL      (~NONE)
#define ALL_OFF  NONE
#define ALL_ON   ALL


#endif
