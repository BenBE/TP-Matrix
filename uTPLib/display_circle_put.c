#include <uTPlib.h>

// from wikipedia http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void display_circle_put(coord_t x0, coord_t y0, int radius, color_t c)
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
        display_pixel_set(x0 + x, y0 + y, c);
        display_pixel_set(x0 - x, y0 + y, c);
        display_pixel_set(x0 + x, y0 - y, c);
        display_pixel_set(x0 - x, y0 - y, c);
        display_pixel_set(x0 + y, y0 + x, c);
        display_pixel_set(x0 - y, y0 + x, c);
        display_pixel_set(x0 + y, y0 - x, c);
        display_pixel_set(x0 - y, y0 - x, c);
    }
}
