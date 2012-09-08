#include <uTPlib.h>

#include "main.h"

static void make_circles(coord_t x0, coord_t y0, int radius, color_t c, int inc_color) {
    if( radius > 0 ) {
        if( c == 0300 )
            inc_color = 0;
        else if( c == 0000)
            inc_color = 1;
        if( inc_color )
            make_circles(x0,y0, radius - 1, c + 64, inc_color);
        else
            make_circles(x0,y0, radius - 1, c - 64, inc_color);
    }
    display_circle_put(x0, y0, radius, c);
}

void drop(void) {
    display_buffer_active_set(0);
    display_buffer_write_set(0);

    for(int i=0; i<3; ++i) {
        display_clear_black();

        coord_t circle_x = random_range(0, DISPLAY_WIDTH);
        coord_t circle_y = random_range(0, DISPLAY_HEIGHT);

        for(int j=1; j<24; ++j) {
            make_circles(circle_x, circle_y, j, 0000, 1);
            delay_ms(250);
        }
    }
}

