#include "uTPlib.h"

void delay_ms(timebase_t time)
{
    while (time >= 2)
    {
        time -= 2;
        time_sync();
    }
}
