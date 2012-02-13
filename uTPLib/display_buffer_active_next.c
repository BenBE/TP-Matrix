#include "uTPlib.h"

void display_buffer_active_next()
{
    display_buffer_active_set(
        (display_buffer_active_get() + 1) % DISPLAY_BUFFERS
        );
}
