#include <uTPlib.h>

void font_string_printY(coord_t x, coord_t y, color_t color, char *s)
{
    for(; *s && y < DISPLAY_HEIGHT; y += FONT_HEIGHT + 1, s++)
    {
        font_char_print(x, y, color, *s);
    }
}
