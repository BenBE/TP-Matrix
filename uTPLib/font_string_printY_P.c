#include <uTPlib.h>

void font_string_printY_P(coord_t x, coord_t y, color_t color, const prog_uint8_t *s)
{
    for(uint8_t t = pgm_read_byte(s); (t = pgm_read_byte(s)) && y < DISPLAY_HEIGHT; y += FONT_HEIGHT, s++)
    {
        font_char_print(x, y, color, t);
    }
}
