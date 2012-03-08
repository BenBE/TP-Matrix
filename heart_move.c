#include <uTPlib.h>

#include "main.h"

const prog_uint8_t heart_data[9] = {
    0x0C, 0x12, 0x21, 0x42, 0x84, 0x42, 0x21, 0x12, 0x0C
};

void heart() {
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);

    for(coord_t x = 0; x < DISPLAY_WIDTH; x++) {
        for(coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
            display_pixel_set(x, y,
                display_color_from_rgb(
                    128 + 127 * y / (DISPLAY_HEIGHT - 1),
                    255 - 255 * (DISPLAY_HEIGHT - y - 1) / (DISPLAY_HEIGHT - 1),
                    128 - 128 * (DISPLAY_WIDTH - x - 1) / (DISPLAY_WIDTH - 1)
                    )
                );
        }
    }

    time_sync();

    for (uint16_t counter = 256; counter; --counter) {
        display_buffer_write_set(0);
        display_buffer_copy(1, 0);

        coord_t p = counter % DISPLAY_WIDTH;
        display_sprite_put_P(p, 0, 9, 8, display_color_from_rgb( 255, 0, 128 ), heart_data);

        if( DISPLAY_WIDTH - p < 9 ) {
            display_sprite_put_P(p - DISPLAY_WIDTH, 0, 9, 8, 
                display_color_from_rgb( 255, 0, 128 ), heart_data);
        }

        if(counter & 1) {
            for(coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
                color_t tmp = display[1][0][y];
                for(coord_t x = 0; x < DISPLAY_WIDTH - 1; x++) {
                    display[1][x][y] = display[1][x + 1][y];
                }
                display[1][DISPLAY_WIDTH - 1][y] = tmp;
            }
        }

        delay_ms(50);
    }

}
