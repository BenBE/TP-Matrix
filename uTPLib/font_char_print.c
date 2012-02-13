#include "uTPlib.h"

void font_char_print(coord_t x, coord_t y, color_t color, char c)
{
    if( (c < 32) || (c >= 128 + 32) )
    {
        return;
    }

    const prog_uint8_t *font_data = &font[(int)c-32][0];

    if( x < -FONT_WIDTH) {
        return;
    }

    if( x >= DISPLAY_WIDTH) {
        return;
    }

    if( y < -FONT_HEIGHT) {
        return;
    }

    if( y >= DISPLAY_HEIGHT) {
        return;
    }

    for(coord_t dx = 0; dx < FONT_WIDTH; dx++)
    {
        if(x + dx < 0)
        {
            continue;
        }
        if(x + dx >= DISPLAY_WIDTH)
        {
            break;
        }

        uint8_t pxl = pgm_read_byte(&font_data[dx]);
        for(coord_t dy = 0; dy < FONT_HEIGHT; dy++)
        {
            if(pxl & 1)
            {
                if(y + dy < 0)
                {
                    continue;
                }
                if(y + dy >= DISPLAY_HEIGHT)
                {
                    break;
                }
                display_pixel_set(x + dx, y+dy, color);
            }
            pxl >>= 1;
        }
    }
}
