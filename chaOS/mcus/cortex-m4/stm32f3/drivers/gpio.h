#ifndef DEVICES_STM32F3_DRIVERS_GPIO_H
#define DEVICES_STM32F3_DRIVERS_GPIO_H


#include "inc/gpio.h"
#include "peripherals.h"
#include "memmap.h"

#if !CHAOS_KERNEL
#pragma message "including device-specific driver (" __FILE__ ") -- your code will not be portable!"
#endif

#define NPINS 16  // pins per port

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define PORT_MAX 5


#endif
