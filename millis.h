#ifndef _LM_MILLIS_H_
#define _LM_MILLIS_H_

typedef uint16_t millis_t;

void millis_init(void);
millis_t millis_time_difference(millis_t a, millis_t b);
millis_t millis_get_millis(void);

#endif /* _LM_MILLIS_H_ */
