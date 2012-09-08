#include <uTPlib.h>

#include "main.h"


//typedef enum { MODIFY_MODE_SET, MODIFY_MODE_ADD } modify_mode_t;
//static void inline modify_pixel(coord_t x, coord_t y, 
//                                color_t color, modify_mode_t modify_mode) 
//{
//  if( modify_mode == MODIFY_MODE_SET )
//    display_pixel_set(x, y, color);
//  else
//    display_pixel_get(x, y
//
//}
static const color_t color_lookup[] = {
        0000,	0100,	0200,	0300,
        0310,	0320,	0331,	0342,
        0354,	0365,	0376,	0377
        };

static const int8_t max_value = sizeof(color_lookup) / sizeof(color_lookup[0]) - 1;
static const int8_t min_value = 0;

static inline color_t value_to_color(int8_t value) {
    value -= min_value;
    value = value >> 1;
    if(value > max_value) {
        value = max_value;
    }
    return color_lookup[value];
}

static void add_buffers(void) {
    color_t* display0_ptr = &display[0][0][0];
    color_t* display1_ptr = &display[1][0][0];
    color_t* display2_ptr = &display[2][0][0];
    int x = DISPLAY_WIDTH * DISPLAY_HEIGHT - 1;
    for(; x >= 0; --x) {
        *display0_ptr = value_to_color( *display1_ptr + *display2_ptr);
        ++display0_ptr;
        ++display1_ptr;
        ++display2_ptr;
    }
}

//static void make_circles(coord_t x0, coord_t y0, int radius, color_t c, int inc_color) {
//    if( radius > 0 ) {
//        if( c == 0300 )
//            inc_color = 0;
//        else if( c == 0000)
//            inc_color = 1;
//        if( inc_color )
//            make_circles(x0,y0, radius - 1, c + 64, inc_color);
//        else
//            make_circles(x0,y0, radius - 1, c - 64, inc_color);
//    }
//    raster_circle(x0, y0, radius, c);
//}

static void make_circles( coord_t x0, coord_t y0, int radius, int8_t value,
                          int inc_value, int buffer)
{
    static const int8_t add_value = 1;

    while( radius >= 0 ) {
        if( value >= (max_value - add_value) )
            inc_value = 0;
        else if( value < (min_value + add_value) )
            inc_value = 1;

        if( inc_value )
//            make_circles(x0, y0, radius - 1, value + add_value, inc_value, buffer);
            value += add_value;
        else
//            make_circles(x0, y0, radius - 1, value - add_value, inc_value, buffer);
            value -= add_value;

        if(radius < DISPLAY_WIDTH) {
            //raster_circle(x0, y0, radius, value, buffer);
            display_buffer_write_set(buffer);
            display_circle_put(x0, y0, radius, value);
        }

        radius--;
    }

}

void drop2(void) {
    display_buffer_active_set(0);
    display_buffer_write_set(0);
    display_clear_black();
    //! display[0] active buffer
    //! display[1] write buffer for wave 1
    //! display[2] write buffer for wave 2

    coord_t circle1_x;
    coord_t circle1_y;
    coord_t circle2_x;
    coord_t circle2_y;

    for(int i = 0; i<16; ++i) {
        circle1_x = random_range(0, DISPLAY_WIDTH);
        circle1_y = random_range(0, DISPLAY_HEIGHT);
        circle2_x = random_range(0, DISPLAY_WIDTH);
        circle2_y = random_range(0, DISPLAY_HEIGHT);

        display_buffer_write_set(0);
        display_clear_black();
        display_buffer_write_set(1);
        display_clear_black();
        display_buffer_write_set(2);
        display_clear_black();

        for(int j = 1; j<64; ++j) {
//            display_buffer_write_set(0);
//            display_clear_black();
            make_circles(circle1_x, circle1_y, j, 0, 1, 1);
            make_circles(circle2_x, circle2_y, j, 0, 1, 2);

            add_buffers();
            delay_ms( 100 );
        }
        display_clear_black();
    }
}
