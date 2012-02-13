#include <uTPlib.h>

void font_string_printX(coord_t x, coord_t y, color_t color, char *s)
{
    for(; *s && x < DISPLAY_WIDTH; x += FONT_WIDTH, s++)
    {
        font_char_print(x, y, color, *s);
    }
}
