#include <avr/io.h>

#include "led_strip.h"

void led_strip_init(void)
{
    DDRB |= (1 << DDB7) | (1 << DDB6) | (1 << DDB5); /* Set B5-7 as outputs */
    PORTB &= ~((1 << PORTB7) | (1 << PORTB6) | (1 << PORTB5)); /* Disable pull-ups */

    /* Setup Timer 1A-C for PWM mode */
    /* PWM, Phase correct, 8-bit, CLK_IO / 8, PWM @ 245.1 Hz */
    TCCR1B = (1 << CS11);
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1) | (1 << WGM10);
    OCR1A = 0; /* blue */
    OCR1B = 0; /* green */
    OCR1C = 0; /* red */
}

void led_strip_set_value(uint8_t red, uint8_t green, uint8_t blue)
{
    OCR1A = blue;
    OCR1B = green;
    OCR1C = red;
}
