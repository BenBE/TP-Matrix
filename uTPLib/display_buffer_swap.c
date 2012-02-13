#include "uTPlib.h"

void display_buffer_swap(uint8_t mode)
{
    switch(mode)
    {
        case 0:
            display_buffer_active_write_swap();
            break;

        case 1:
            display_buffer_active_write_next();
            display_clear_black();
            break;

        case 2:
            display_buffer_active_write_next();
            display_buffer_copy(display_buffer_active_get(), display_buffer_write_get());
            break;

        case 255:	//Fall-through desired
        default:
            display_buffer_active_write_next();
    }
}
