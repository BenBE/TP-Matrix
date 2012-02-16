#include <uTPlib.h>
#include <WProgram.h>

#include "main.h"

void forest_fire()
{
    uint8_t forest[DISPLAY_WIDTH][DISPLAY_HEIGHT]; // 0:empty 1:tree 2:fire
    uint8_t cell;

    for (int x = 0; x < DISPLAY_WIDTH; x++) {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            cell = random_range (0, 2);
            forest[x][y] = cell;
            display_pixel_set (x, y, display_color_from_rgb ( cell > 1 ? 255 : 0, cell > 0 ? 127 : 0, 0 ) );
        }

        //        display_buffer_swap(2);
    }

    int counter = 500;

    while (counter--) {
        delay_ms (20);
        display_buffer_swap (1);

        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            for (int y = 0; y < DISPLAY_HEIGHT; y++) {
                cell = (forest[x][y] & 3);

                if (cell == 0) {
                    cell = (random_range (0, 10) == 1 ? 1 : 0); // grow tree p=10%
                } else if (cell == 1) {
                    int neighbours = 0;

                    for (int xx = -1; xx <= 1; xx++)
                        for (int yy = -1; yy <= 1; yy++)
                            if (! (xx == 0 && yy == 0) &&
                                x + xx >= 0 && x + xx < DISPLAY_WIDTH &&
                                y + yy >= 0 && y + yy < DISPLAY_HEIGHT)
                                if ( (forest[x + xx][y + yy] & 3) == 2) {
                                    neighbours++;
                                    goto stop_neighbours;
                                }

stop_neighbours:

                    if (neighbours || random_range (0, 100) == 1) {
                        cell = 2;  // burn f=1%
                    }
                } else {
                    cell = 0;  // stop burning
                }

                forest[x][y] = (forest[x][y] & 3) | (cell << 2); // save new value
                display_pixel_set (x, y, display_color_from_rgb ( cell > 1 ? 255 : 0, cell > 0 ? 127 : 0, 0 ) );
            }
        }

        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            for (int y = 0; y < DISPLAY_HEIGHT; y++) {
                forest[x][y] = forest[x][y] >> 2; // new value to old value
            }
        }
    }
}

