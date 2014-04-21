#ifndef BOARDS_DISCOVERYF0_BOARD_H
#define BOARDS_DISCOVERYF0_BOARD_H


#include "drivers/gpio.h"

//                                               PORTA  PORTB  PORTC  PORTD  PORTE  PORTF
static const bool port_connected[PORT_MAX+1] = {  true,  true,  true, false, false, false };

#define LED_PORT  PORTC
#define LED1      PIN(8)
#define LED2      PIN(9)


#endif
