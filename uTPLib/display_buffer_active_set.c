#include "uTPlib.h"

void display_buffer_active_set(buffer_t buffer)
{
    if( (buffer >= DISPLAY_BUFFERS) )
    {
        buffer = 0;
    }
    display_active = display + buffer;
}
