
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "time.h"

static volatile millis_t milliseconds = 0;

static millis_t max_millis = ((uint64_t)1 << (sizeof(millis_t) * 8)) - 1;

millis_t time_difference(millis_t a, millis_t b)
{
    if (a >= b) {
        return a - b;
    } else {
        return max_millis - b + a;
    }
}

millis_t millis_get(void)
{
    millis_t ms;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        ms = milliseconds;
    }
    return ms;
}

void init_elapsed_timer(void)
{
    TCCR0A = (1 << WGM01); /* CTC */
    TCCR0B = (1 << CS01); /* CLK_IO / 8 */
    TIMSK0 = (1 << OCIE0A);
    OCR0A = F_CPU / 8 / 1000; /* 125 @ 1 MHz */
}

ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
    milliseconds++;
}
