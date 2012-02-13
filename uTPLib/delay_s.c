#include "uTPlib.h"

void delay_s(timebase_t time)
{
    while(time > 10) 
    {
        delay_ms(10000);
        time -= 10;
    }
    if(time)
    {
        delay_ms(time * 1000);
    }
}
