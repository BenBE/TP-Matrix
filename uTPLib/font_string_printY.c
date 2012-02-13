#include <uTPlib.h>

void font_string_printY(coord_t x, coord_t y, color_t color, char *s)
{
    for(; *s && y < DISPLAY_HEIGHT; y += FONT_HEIGHT, s++)
    {
        font_char_print(x, y, color, *s);
    }
}
