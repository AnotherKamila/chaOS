#ifndef DEVICES_STM32F0_DRIVERS_GPIO_H
#define DEVICES_STM32F0_DRIVERS_GPIO_H

#include "inc/gpio.h"
#include "peripherals.h"

#if !CHAOS_KERNEL
#pragma message "including device-specific driver (" __FILE__ ") -- your code will not be portable!"
#endif

#define  NPINS  16  // pins per port

typedef struct {
    GPIO_struct* GPIO;
    enum RCC_ahbenr _GPIO_RCC_mask;
} Port;

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define PORT_MAX 5

#define LED_PORT  PORTC
#define LED1      PIN(8)
#define LED2      PIN(9)

#endif
