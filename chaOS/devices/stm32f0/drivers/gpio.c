#include "inc/gpio.h"
#include "gpio.h"
#include "util/bit_manip.h"

#define in_bounds(X)  ((X) <= PORT_MAX)

const Port ports[] = {
	{ .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTA), ._GPIO_RCC_mask = AHBENR_IOPAEN },
	{ .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTB), ._GPIO_RCC_mask = AHBENR_IOPBEN },
	{ .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTC), ._GPIO_RCC_mask = AHBENR_IOPCEN },
	{ .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTD), ._GPIO_RCC_mask = AHBENR_IOPDEN },
	{ .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTE), ._GPIO_RCC_mask = AHBENR_IOPEEN },
	{ .GPIO = (GPIO_struct*)(AHB2PERIPH_BASE + GPIO_AHB2_OFFSET_PORTF), ._GPIO_RCC_mask = AHBENR_IOPFEN },
};

uint32_t GPIO_enable() {
	//STM32F0 GPIO peripheral is initialized per-port, not as whole
	return GPIO_SUCCESS;
}

uint32_t GPIO_enable_port(uint16_t port) {
	if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;
	bit_mon(RCC->AHBENR, ports[port]._GPIO_RCC_mask);
	return GPIO_SUCCESS;
}

uint32_t GPIO_set_pins_mode(uint16_t port, uint32_t pins, uint16_t mode_flags) {
	if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;
	uint32_t bit_mask = bits_expand(pins); //Interleave pins with themselves, because MODER and PUPDR have 2 bits per pin
	uint32_t settings_mask = 0;

	if (mode_flags & GPIO_OUTPUT)
		settings_mask = GPIO_MODER_OUTPUT_MASK & bit_mask; //Prepare settings mask
	else if (mode_flags & GPIO_ALTERNATE)
		settings_mask = GPIO_MODER_ALT_MASK & bit_mask;
	else if (mode_flags & GPIO_ANALOG)
		settings_mask = GPIO_MODER_ANALOG_MASK & bit_mask;

	//TODO disable interrupts
	uint32_t moder = ports[port].GPIO->MODER;
	bit_moff(moder, bit_mask); //Reset required pins
	bit_mon(moder, settings_mask); //Apply settings mask
	ports[port].GPIO->MODER = moder;
	//TODO enable interrupts

	if ((mode_flags & GPIO_OUTPUT) && (mode_flags & GPIO_OPENDRAIN)) {
		//In case of opendrain output
		//TODO disable interrupts
		bit_mon(ports[port].GPIO->OTYPER, pins);
		//TODO enable interrupts
	} else {
		//Reset to default value
		//TODO disable interrupts
		bit_moff(ports[port].GPIO->OTYPER, pins);
		//TODO enable interrupts
	}

	settings_mask = 0;
	if (mode_flags & (GPIO_PULLING | GPIO_OPENDRAIN)) {
		//If a pullup resistor needs to be set
		if (mode_flags & GPIO_PULLUP)
			settings_mask = GPIO_PUPDR_UP_MASK & bit_mask;
		else
			settings_mask = GPIO_PUPDR_DOWN_MASK & bit_mask;
	}
	//TODO disable interrupts
	uint32_t pupdr = ports[port].GPIO->PUPDR;
	bit_moff(pupdr, bit_mask); //Reset required pins
	bit_mon(pupdr, settings_mask); //Apply settings mask
	ports[port].GPIO->PUPDR = pupdr;
	//TODO enable interrupts

	//TODO speed setting
	
	return GPIO_SUCCESS;
}

uint32_t GPIO_write(uint16_t port, uint32_t pins, bool value) {
	if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;
	uint32_t *atomicRegister = value ? &(ports[port].GPIO->BSRR) : &(ports[port].GPIO->BRR);
	*atomicRegister = pins;
	return GPIO_SUCCESS;
}

uint32_t GPIO_read(uint16_t port, uint32_t pins, uint32_t *data) {
	if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;
	*data = ports[port].GPIO->IDR & pins;
	return GPIO_SUCCESS;
}

uint32_t GPIO_extra_action(uint16_t port, uint32_t action, uint32_t *response) {
	if (!in_bounds(port)) return GPIO_PORT_OUT_OF_RANGE;
	//TODO
	return GPIO_UNSUPPORTED_EXTRA;
}