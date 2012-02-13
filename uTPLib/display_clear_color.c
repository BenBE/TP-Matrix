#include <uTPlib.h>

void display_clear_color(color_t color)
{
    color_t *buf = &(*display_write)[0][0];
    for(coord_t x = 0; x < DISPLAY_WIDTH; x++)
    {
        for(coord_t y = 0; y < DISPLAY_HEIGHT; y++)
        {
            *(buf++) = color;
        }
    }
}
