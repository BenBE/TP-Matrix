#include "uTPlib.h"

void display_pixel_set(coord_t x, coord_t y, color_t color)
{
    if((0 > x) || (x >= DISPLAY_WIDTH))
    {
        return;
    }
    if((0 > y) || (y >= DISPLAY_HEIGHT))
    {
        return;
    }

    (*display_write)[x][y] = color;
}
