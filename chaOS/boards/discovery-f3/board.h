#ifndef BOARDS_DISCOVERYF3_BOARD_H
#define BOARDS_DISCOVERYF3_BOARD_H


#include "drivers/gpio.h"

//                                               PORTA  PORTB  PORTC  PORTD  PORTE  PORTF
static const bool port_connected[PORT_MAX+1] = {  true,  true,  true,  true,  true,  true };

#define LED_PORT  PORTE
#define LED4      PIN(8)
#define LED3      PIN(9)
#define LED5      PIN(10)
#define LED7      PIN(11)
#define LED9      PIN(12)
#define LED10     PIN(13)
#define LED8      PIN(14)
#define LED6      PIN(15)

#define PANIC_LED   LED3
#define PANIC_PORT  LED_PORT

#define BLUE_LED   LED4
#define GREEN_LED  LED7


#endif
