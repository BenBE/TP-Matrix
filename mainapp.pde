#include "uTPlib.h"

#include "main.h"

void setup(void);
void loop(void);

void setup()
{
    display_init();
}

void loop()
{
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);

    string_anim (42);
    pacman();
    string_anim (0);
    heart();
    string_anim (1);
    forest_fire();
    string_anim (2);
    defender();
    string_anim (3);

    display_buffer_write_set(0);
    display_buffer_active_set(0);
//    uint16_t tmp = time_frame;
    display_clear_color( 0 );
    delay_ms(2000);
    display_pixel_set(1, 1, display_color_from_rgb(255,0,0));
    delay_ms(2000);
    display_pixel_set(2, 1, display_color_from_rgb(0,255,0));
    delay_ms(2000);
    display_pixel_set(3, 1, display_color_from_rgb(0,0,255));
    delay_ms(2000);
    display_pixel_set(4, 1, 255);
//    display_pixel_set(8,0,(tmp>>16) & 255);

    delay_ms(2000);
//    time_sync();
}
