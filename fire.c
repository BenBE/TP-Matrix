#include <uTPlib.h>

#include "main.h"

const prog_uint8_t fire_lookup[12] = {
    0000, 0002, 0004, 0007,
    0017, 0037, 0047, 0057,
    0067, 0077, 0277, 0377
};

void bonfire() {
    char fire[DISPLAY_WIDTH];

    for(coord_t x = 0; x < DISPLAY_WIDTH; x++) {
        fire[x] = 0;
    }

    display_buffer_active_set(0);
    display_buffer_write_set(0);

    for(int t = 0; t < 1000; t++) {
        for(coord_t x = 0; x < DISPLAY_WIDTH; x++) {
            if(fire[x]) {
                fire[x]--;
            }
        }

        //Power to the fire!
        coord_t x = random_range(0,3);
        while(x < DISPLAY_WIDTH) {
            signed char p = random_range(1, DISPLAY_HEIGHT>>2);
            coord_t x1 = 0;
            while(p > 0) {
                if(DISPLAY_HEIGHT <= (fire[(x+x1)%DISPLAY_WIDTH] += p)) {
                    fire[(x+x1)%DISPLAY_WIDTH] = DISPLAY_HEIGHT;
                }

                if(x1) {
                    if(DISPLAY_HEIGHT <= (fire[(x+DISPLAY_WIDTH-x1)%DISPLAY_WIDTH] += p)) {
                        fire[(x+DISPLAY_WIDTH-x1)%DISPLAY_WIDTH] = DISPLAY_HEIGHT;
                    }
                }

                p -= 2;
                x1++;
            }

            x += random_range(0, 3);
        }

        for(coord_t x = 0; x < DISPLAY_WIDTH; x++) {
            for(coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
                coord_t ctmp = y + fire[x] - DISPLAY_HEIGHT;
                color_t c = (ctmp < 0) ? 0 : (ctmp >= sizeof(fire_lookup) / sizeof(*fire_lookup)) ? sizeof(fire_lookup) / sizeof(*fire_lookup) - 1 : ctmp;
                c = pgm_read_byte(&fire_lookup[c]);
                display_pixel_set(x, y, c);
            }
        }

        delay_ms(25);
    }
}
