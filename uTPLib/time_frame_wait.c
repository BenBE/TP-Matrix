#include "uTPlib.h"

void time_frame_wait(timebase_t frame) 
{
    while(time_frame != frame)
    {
        time_sync();
    }
}
