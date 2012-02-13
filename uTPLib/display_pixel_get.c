#include "uTPlib.h"

color_t display_pixel_get(coord_t x, coord_t y)
{
    return (*display_write)[x][y];
}
