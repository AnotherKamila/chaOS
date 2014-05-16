/* defines peripherals */

#include "peripherals.h"
#include "memmap.h"

GPIO_struct* const GPIO[] = {
    (GPIO_struct*)(AHB2_PERIPH_BASE + GPIO_AHB2_OFFSET_PORTA),
    (GPIO_struct*)(AHB2_PERIPH_BASE + GPIO_AHB2_OFFSET_PORTB),
    (GPIO_struct*)(AHB2_PERIPH_BASE + GPIO_AHB2_OFFSET_PORTC),
    (GPIO_struct*)(AHB2_PERIPH_BASE + GPIO_AHB2_OFFSET_PORTD),
    (GPIO_struct*)(AHB2_PERIPH_BASE + GPIO_AHB2_OFFSET_PORTE),
    (GPIO_struct*)(AHB2_PERIPH_BASE + GPIO_AHB2_OFFSET_PORTF)
};

RCC_struct * const RCC = (RCC_struct*)(AHB1_PERIPH_BASE + RCC_AHB1_OFFSET);
