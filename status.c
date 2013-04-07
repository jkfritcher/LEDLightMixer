#include <avr/io.h>

#include "time.h"
#include "status.h"

static volatile STATUS status;

static uint16_t LED_STATUS[][8] = {
    { 6, 0, 250, 250, 500, 500, 750, 750 },
    { 2, 0, 100, 2900, 0 },
    { 0 }
};

static millis_t last_change = 0;

void status_led_init(void)
{
    DDRE |= (1 << DDE6);
    PORTE |= (1 << PORTE6);
    status = STATUS_STARTING;
}

void status_led_update(millis_t now)
{
    millis_t diff = time_difference(now, last_change);

    uint8_t i = LED_STATUS[status][1];
    if (diff >= LED_STATUS[status][2 + i]) {
        PORTE ^= (1 << PORTE6);
        LED_STATUS[status][1] = ((i + 1) % LED_STATUS[status][0]);        
        last_change = now;
    }
}

void status_led_change_status(STATUS s)
{
    if (s != status) {
        LED_STATUS[s][1] = 0;
        status = s;
        last_change = millis_get();
    }
}

