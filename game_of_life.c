#include <uTPlib.h>

#include "main.h"

static void init_random (void);
static void do_game_of_life (void);

static void init_random()
{
    for (coord_t x = 0; x < DISPLAY_WIDTH; x++) {
        for (coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
            display_pixel_set (x, y, random_range (0, 2) ? 255 : 0);
        }
    }
}

static void do_game_of_life()
{
    for (coord_t x = 0; x < DISPLAY_WIDTH; x++) {
        for (coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
            uint8_t count = 0;

            coord_t dx0 = (x - 1 + DISPLAY_WIDTH) % DISPLAY_WIDTH;
            coord_t dy0 = (y - 1 + DISPLAY_HEIGHT) % DISPLAY_HEIGHT;

            coord_t dx1 = (x + 1) % DISPLAY_WIDTH;
            coord_t dy1 = (y + 1) % DISPLAY_HEIGHT;

            uint8_t life_old = display[0][x][y], life = 255 == life_old;

            if (255 == display[0][dx0][dy0]) {
                count++;
            }

            if (255 == display[0][dx0][y]) {
                count++;
            }

            if (255 == display[0][dx0][dy1]) {
                count++;
            }

            if (255 == display[0][x][dy0]) {
                count++;
            }

            if (255 == display[0][x][dy1]) {
                count++;
            }

            if (255 == display[0][dx1][dy0]) {
                count++;
            }

            if (255 == display[0][dx1][y]) {
                count++;
            }

            if (255 == display[0][dx1][dy1]) {
                count++;
            }

            life = (3 == count) || (life && (2 == count) );
            life_old &= 7;
            life_old = (life_old - 2) * (life_old > 1);
            life_old = ((life_old >> 1) << 6) + life_old * 0011;
            display_pixel_set (x, y, life ? 255 : life_old);
        }
    }
}

void game_of_life()
{
    display_buffer_write_set (0);
    display_clear_black();
    display_buffer_active_set (0);

    init_random();
    display_buffer_write_set (1);

    for (int i = 0; i < 256; i++) {
        do_game_of_life();

        if (!memcmp (display[0], display[1], DISPLAY_WIDTH * DISPLAY_HEIGHT) ) {
            init_random();
        }

        display_buffer_copy (1, 0);
        delay_ms (200);
    }

}
