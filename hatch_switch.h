#ifndef _LM_HATCH_SWITCH_H_
#define _LM_HATCH_SWITCH_H_

enum {
    HATCH_VALUE_OPEN   = 0,
    HATCH_VALUE_CLOSED = 1
};

void hatch_switch_init(void);
bool hatch_switch_get_value(void);

#endif /* _LM_HATCH_SWITCH_H_ */
