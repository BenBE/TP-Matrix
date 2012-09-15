#include "uTPlib.h"

void delay_ms(timebase_t time)
{
    #ifndef X86
    while (time >= 2)
    {
          time -= 2;
          time_sync();
           usleep(
    }
    #else
    usleep((time * 1000) - 2);
    time_sync();
    #endif
}
