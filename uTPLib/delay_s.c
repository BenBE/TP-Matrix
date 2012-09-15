#include "uTPlib.h"

void delay_s(timebase_t time)
{
    #ifndef X86
    while(time > 10) 
    {
        delay_ms(10000);
        time -= 10;
    }
    if(time)
    {
        delay_ms(time * 1000);
    }
    #else
    sleep(time);
    time_sync();
    #endif
}
