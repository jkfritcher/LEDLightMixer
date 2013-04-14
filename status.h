#ifndef _LM_STATUS_H_
#define _LM_STATUS_H_

#include "time.h"

typedef enum {
    STATUS_STARTING = 0,
    STATUS_IDLE
} STATUS;

void status_led_init(void);
void status_led_update(millis_t now);
void status_led_change_status(STATUS s);

#endif /* _LM_STATUS_H_ */
