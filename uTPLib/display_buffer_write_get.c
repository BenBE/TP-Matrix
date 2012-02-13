#include "uTPlib.h"

buffer_t display_buffer_write_get()
{
    buffer_t tmp = display_write - display;
    if( (tmp >= DISPLAY_BUFFERS) )
    {
        tmp = 0;
        display_write = display;
    }
    return tmp;
}
