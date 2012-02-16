#include <uTPlib.h>

#include "main.h"

void defender()
{
    // ship
    int shipx = 4;
    int shipy = 4;
    int shipdx = 1;
    int shipdy = 1;
    // shot
    int shotx = -100;
    int shotdx = 4;
    int shoty = 0;
    int shotlen = 8;
    // explosion
    int xplx = 0;
    int xply = 0;
    int xpld = 0;
    // enemies
#define ENEMn 8
    struct enem {
        int x, y, dx, dy;
        unsigned char r, g, b;
    } enems[ENEMn];

    for (int i = 0; i < ENEMn; i++) {
        enems[i].x = random_range (0, DISPLAY_WIDTH);
        enems[i].y = random_range (1, DISPLAY_HEIGHT);
        enems[i].dx = 0; // random_range(-1,1+1);
        enems[i].dy = random_range (-1, 1 + 1);
        enems[i].r = random_range (48, 255);
        enems[i].g = random_range (0, 255);
        enems[i].b = random_range (0, 255);
    }

    int counter = 120;

    while (counter--) {
        delay_ms (64);
        display_buffer_swap (1);

        // ship
        shipx += shipdx;

        if (shipx < 1) {
            shipx += 2;
            shipdx = -shipdx;
        }

        if (shipx >= DISPLAY_WIDTH) {
            shipx -= 2;
            shipdx = -shipdx;
        }

        if ( ( (counter + 1) & 1) == 1) {
            shipy += shipdy;
        }

        if (shipy < 0) {
            shipy += 2;
            shipdy = -shipdy;
        }

        if (shipy >= DISPLAY_HEIGHT) {
            shipy -= 2;
            shipdy = -shipdy;
        }

        display_pixel_set (shipx - 1         , shipy    , display_color_from_rgb ( 200, 255, 255 ) );
        display_pixel_set (shipx             , shipy    , display_color_from_rgb ( 200, 255, 255 ) );
        display_pixel_set (shipx + 1         , shipy    , display_color_from_rgb ( 200, 255, 255 ) );
        display_pixel_set (shipx + 2 * shipdx, shipy    , display_color_from_rgb ( 200, 255, 255 ) );
        display_pixel_set (shipx - shipdx    , shipy - 1, display_color_from_rgb ( 200, 255, 255 ) );
        display_pixel_set (shipx             , shipy - 1, display_color_from_rgb ( 255, 196,  60 ) );

        // shot
        shotx += shotdx * 2;

        if (shotx < 0 || shotx >= DISPLAY_WIDTH) { // new shot
            shotx = shipx + shipdx * shotlen;
            shotdx = shipdx;
            shoty = shipy;
        }

        for (int i = 1, xx = shotx; i <= shotlen; i++, xx += shotdx) {
            int j = i * 255 / shotlen;
            int x = shotx + xx - 4 * shotdx;
            display_pixel_set (x, shoty, display_color_from_rgb (j, j, j) );

            for (int i = 0; i < ENEMn; i++) {
                struct enem *e = &enems[i];

                if (e->x == x && e->y == shoty) {
                    xplx = e->x;
                    xply = e->y;
                    xpld = 1;
                    e->y = -100;
                    e->dy = 0; // away
                }
            }
        }

        if (xpld == 1) {
            shotx = -100;
        }

        // explosion
        if (xpld) {
            for (int xpl_x = -1; xpl_x <= 1; xpl_x++) {
                for (int xpl_y = -1; xpl_y <= 1; xpl_y++) {
                    //for (int i=0; i<2; i++)
                    display_pixel_set (xplx + xpl_x * xpld, xply + xpl_y * xpld, display_color_from_rgb ( 255, 255, 0 ) );
                }

                xpld++;

                if (xpld == 8) {
                    xpld = 0;
                }
            }
        }

        // enemies
        for (int i = 0; i < ENEMn; i++) {
            struct enem *e = &enems[i];

            if ( ( (i + counter + 1) & 7) == 7) {
                e->x += e->dx;

                if (e->x < 0) {
                    e->x += DISPLAY_WIDTH;
                } else if (e->x >= DISPLAY_WIDTH) {
                    e->x = 0;
                }

                e->y += e->dy;

                if (e->y < 0) {
                    e->y += DISPLAY_HEIGHT;
                } else if (e->y >= DISPLAY_HEIGHT) {
                    e->y = 0;
                }
            }

            display_pixel_set (e->x    , e->y - 1, display_color_from_rgb ( e->r, e->g, e->b ) );
            display_pixel_set (e->x - 1, e->y    , display_color_from_rgb ( e->r, e->g, e->b ) );
            display_pixel_set (e->x    , e->y    , display_color_from_rgb ( e->r, e->g, e->b ) );
            display_pixel_set (e->x + 1, e->y    , display_color_from_rgb ( e->r, e->g, e->b ) );
            //my_paint(e->x  ,e->y+1,e->r,e->g,e->b);
        }
    }
}

