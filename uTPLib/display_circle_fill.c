#include <uTPlib.h>

// from wikipedia http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void display_circle_fill(coord_t x0, coord_t y0, int radius, color_t c)
{
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    display_pixel_set(x0, y0 + radius, c);
    display_pixel_set(x0, y0 - radius, c);
    display_pixel_set(x0 + radius, y0, c);
    display_pixel_set(x0 - radius, y0, c);

    while(x < y) {
        // ddF_x == 2 * x + 1;
        // ddF_y == -2 * y;
        // f == x*x + y*y - radius*radius + 2*x - y + 1;
        if(f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        int x_min = x0 - x;
        int x_max = x0 + x;
        int y_min = y0 - y;
        int y_max = y0 + y;

        if( x_min < 0 ) {
            x_min = 0;
        }
        if( x_max >= DISPLAY_WIDTH ) {
            x_max = DISPLAY_WIDTH - 1;
        }

        if( y_min < 0 ) {
            y_min = 0;
        }
        if( y_max >= DISPLAY_HEIGHT ) {
            y_max = DISPLAY_HEIGHT - 1;
        }

        for( int xl = x_min; xl <= x_max; xl++) {
            //display_pixel_set(x0 + x, y0 + y, c);
            //display_pixel_set(x0 - x, y0 + y, c);

            //display_pixel_set(x0 + x, y0 - y, c);
            //display_pixel_set(x0 - x, y0 - y, c);
            for( int yl = y_min; yl <= y_max; yl++) {
                display_pixel_set(xl, yl, c);
            }
        }

        x_min = x0 - y;
        x_max = x0 + y;
        y_min = y0 - x;
        y_max = y0 + x;

        if( x_min < 0 ) {
            x_min = 0;
        }
        if( x_max >= DISPLAY_WIDTH ) {
            x_max = DISPLAY_WIDTH - 1;
        }

        if( y_min < 0 ) {
            y_min = 0;
        }
        if( y_max >= DISPLAY_HEIGHT ) {
            y_max = DISPLAY_HEIGHT - 1;
        }

        for( int xl = x_min; xl <= x_max; xl++) {
            //display_pixel_set(x0 + x, y0 + y, c);
            //display_pixel_set(x0 - x, y0 + y, c);

            //display_pixel_set(x0 + x, y0 - y, c);
            //display_pixel_set(x0 - x, y0 - y, c);
            for( int yl = y_min; yl <= y_max; yl++) {
                display_pixel_set(xl, yl, c);
            }
        }

    }
}
