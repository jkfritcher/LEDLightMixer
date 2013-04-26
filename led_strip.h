#ifndef _LM_LED_STRIP_H_
#define _LM_LED_STRIP_H_

void led_strip_init(void);
void led_strip_set_value(uint8_t red, uint8_t green, uint8_t blue);
void led_strip_on(void);
void led_strip_off(void);

#endif /* _LM_LED_STRIP_H_ */
