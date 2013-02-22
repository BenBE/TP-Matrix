#include <uTPlib.h>

#include "main.h"

void forest_fire()
{
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);
    display_clear_black();
    display_buffer_swap(0);

    for(uint16_t steps = 256; steps; --steps) {
        for(coord_t x = 0; x < DISPLAY_WIDTH; x++) {
            for(coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
                const coord_t x0 = (x - 1 + DISPLAY_WIDTH) % DISPLAY_WIDTH;
                const coord_t y0 = (y - 1 + DISPLAY_HEIGHT) % DISPLAY_HEIGHT;
                const coord_t x1 = (x + 1) % DISPLAY_WIDTH;
                const coord_t y1 = (y + 1) % DISPLAY_HEIGHT;

                uint16_t burn = 
                    (display[1][x0][y0] & 007) +
                    (display[1][x0][y] & 007) +
                    (display[1][x0][y1] & 007) +
                    (display[1][x][y0] & 007) +
                    (display[1][x][y] & 007) +
                    (display[1][x][y1] & 007) +
                    (display[1][x1][y0] & 007) +
                    (display[1][x1][y] & 007) +
                    (display[1][x1][y1] & 007);
                if(!(display[1][x][y] & 007)) {
                    if(!random_range(0, 100)) {
                        burn++;
                    }
                } else {
                    burn++;
                }
                if(burn > 4) {
                    burn = 4;
                }

                uint8_t wood = (display[1][x][y] & 0070) >> 3;
                if(7 > wood && !burn) {
                    if(!random_range(0, 50)) {
                        wood += random_range(1, 6);
                    }
                    if(7 < wood) {
                        wood = 7;
                    }
                } else if(burn + burn > wood) {
                    burn = 0;
                    wood = 0;
                } else {
                    wood -= 2 * burn;
                    if(burn > wood) {
                        burn = wood;
                        if(burn) {
                            burn--;
                        }
                    }
                }

                display_pixel_set(x, y, burn + (wood << 3));
            }
        }

        display_buffer_copy(0, 1);
        delay_ms(20);
    }

}

