#include "uTPlib.h"

buffer_t display_buffer_active_get()
{
    buffer_t tmp = display_active - display;
    if( (tmp >= DISPLAY_BUFFERS) )
    {
        tmp = 0;
        display_active = &display[0];
    }
    return tmp;
}
