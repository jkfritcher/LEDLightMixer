#include <avr/io.h>
#include <stdbool.h>

#include "led_strip.h"

static bool turned_on = false;
static uint8_t brightness = 255;
static uint8_t red = 127;
static uint8_t green = 127;
static uint8_t blue = 127;

static
void set_outputs(void)
{
    uint32_t t = ((brightness * 1000UL + 254) / 255);
    OCR1A = (uint8_t)((blue * t) / 1000UL);
    OCR1B = (uint8_t)((green * t) / 1000UL);
    OCR1C = (uint8_t)((red * t) / 1000UL);
}

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

void led_strip_set_brightness(uint8_t val)
{
    brightness = val;
    if (turned_on) {
        set_outputs();
    }
}

void led_strip_set_color(uint8_t r, uint8_t g, uint8_t b)
{
    red = r;
    green = g;
    blue = b;
    if (turned_on) {
        set_outputs();
    }
}

void led_strip_on(void)
{
    turned_on = true;
    set_outputs();
}

void led_strip_off(void)
{
    OCR1A = 0;
    OCR1B = 0;
    OCR1C = 0;
    turned_on = false;
}
