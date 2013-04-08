#include <avr/io.h>

#include "time.h"
#include "status.h"

typedef struct {
    uint8_t total_states;
    uint8_t current_state;
    uint16_t states[6];
} led_state_t;

static volatile STATUS status;

static led_state_t LED_STATE[3] = {
    { 6, 0, { 250, 250, 500, 500, 750, 750 } },
    { 2, 0, { 100, 2900, 0 } },
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

    uint8_t i = LED_STATE[status].current_state;
    if (diff >= LED_STATE[status].states[i]) {
        PORTE ^= (1 << PORTE6);
        LED_STATE[status].current_state = ((i + 1) % LED_STATE[status].total_states);
        last_change = now;
    }
}

void status_led_change_status(STATUS s)
{
    if (s != status) {
        LED_STATE[s].current_state = 0;
        status = s;
        last_change = millis_get();
    }
}

