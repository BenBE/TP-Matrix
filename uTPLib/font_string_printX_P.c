#include <uTPlib.h>

void font_string_printX_P(coord_t x, coord_t y, color_t color, const uint8_t *s)
{
    for(uint8_t t = pgm_read_byte(s); (t = pgm_read_byte(s)) && x < DISPLAY_WIDTH; x += FONT_WIDTH + 1, s++)
    {
        font_char_print(x, y, color, t);
    }
}
