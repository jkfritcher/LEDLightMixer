#ifndef _LM_TIME_H_
#define _LM_TIME_H_

typedef uint16_t millis_t;

void init_elapsed_timer(void);
millis_t time_difference(millis_t a, millis_t b);
millis_t millis_get(void);

#endif /* _LM_TIME_H_ */
