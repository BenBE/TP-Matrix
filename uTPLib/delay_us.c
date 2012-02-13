#include "uTPlib.h"

void delay_us(timebase_t time)
{
    uint32_t time_tmp = (uint32_t)time << 4;
    while(time_tmp > 10) {
        __builtin_avr_delay_cycles(10);
        time_tmp -= 10;
    }
}
