#include "uTPlib.h"

void display_sprite_put_P(coord_t x, coord_t y, coord_t w, coord_t h, color_t c, const uint8_t *sprite)
{
    if(!h)
    {
        return;
    }

    do
    {
        const coord_t dh = ((h-1) & 007)+1;

        for(coord_t dx = 0; dx < w; dx++, sprite++)
        {
            color_t dc = pgm_read_byte(sprite);

            for(coord_t dy = 0; dy < dh; dy++)
            {
                if(dc & 1)
                {
                    display_pixel_set(x + dx, y + dy, c);
                }
                dc >>= 1;
            }
        }

        y += 8;
        h = (h >= 8) ? h - 8 : 0;
    } while(h);
}
