#include "uTPlib.h"

void display_buffer_write_next()
{
    display_buffer_write_set(
        (display_buffer_write_get() + 1) % DISPLAY_BUFFERS
        );
}
