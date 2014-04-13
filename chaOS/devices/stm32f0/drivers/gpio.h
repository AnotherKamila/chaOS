#ifndef _DEVICE_GPIO_H
#define _DEVICE_GPIO_H

#include "peripherals.h"

//TODO not portable code warning

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

#endif