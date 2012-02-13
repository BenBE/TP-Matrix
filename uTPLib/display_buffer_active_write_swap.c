#include "uTPlib.h"

void display_buffer_active_write_swap()
{
    screen_t *tmp = display_active;
    display_active = display_write;
    display_write = tmp;
}
