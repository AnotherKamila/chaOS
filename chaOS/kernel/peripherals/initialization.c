#include "initialization.h"
#include "inc/gpio.h"
#include "board.h"

void GPIO_init(void) {
    GPIO_enable();
    for (int port = 0; port <= PORT_MAX; ++port) {
        if (port_connected[port]) GPIO_enable_port(port);
    }
}

void all_peripherals_init(void) {
    GPIO_init();
}
