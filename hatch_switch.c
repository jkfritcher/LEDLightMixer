#include <avr/io.h>
#include <stdbool.h>

#include "hatch_switch.h"

void hatch_switch_init(void)
{
    /* Init switch input */
    DDRB &= ~(1 << DDB4); /* Set B4 as input */
    PORTB |= (1 << PORTB4); /* Enable pull-up */
}

bool hatch_switch_get_value(void)
{
    return ((PINB & (1 << PORTB4)) != 0);
}
