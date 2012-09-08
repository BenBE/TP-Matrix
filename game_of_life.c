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

#define CRC32POLY 0xEDB88320 /* CRC-32 Polynom, umgekehrte Bitfolge */
static uint32_t get_state_checksum(void) {
    uint32_t crc32 = ~0;

    const color_t *pxl = &display[1][0][0];
    for(int offset = 0; offset < DISPLAY_WIDTH * DISPLAY_HEIGHT; offset++) {
        if ((crc32 & 1) != (!!pxl[offset])) {
            crc32 = (crc32 >> 1) ^ CRC32POLY;
        } else {
            crc32 >>= 1;
        }
    }

    return ~crc32;
}

void game_of_life()
{
    display_buffer_write_set (0);
    display_clear_black();
    display_buffer_write_set (2);
    display_clear_black();
    display_buffer_active_set (0);

    init_random();
    display_buffer_write_set (1);

    for (int i = 0; i < 1024; i++) {
        do_game_of_life();

//        if (!memcmp (display[0], display[1], DISPLAY_WIDTH * DISPLAY_HEIGHT) ) {
//            init_random();
//        }

        //Check for loops
        uint32_t curstate = get_state_checksum();
        uint32_t * const recent = (uint32_t *)(&display[2][0][0]);
        int maxRecent = (DISPLAY_WIDTH * DISPLAY_HEIGHT) / sizeof(uint32_t);
        for(int offset = 0; offset < maxRecent - 1; offset++) {
            if( (recent[offset] == curstate) && (recent[0] == recent[offset+1]) ) {

                //Gradually fade out ...
                uint32_t sum;
                do {
                    sum = 0;
                    color_t * const cd = &display[1][0][0];
                    for(int offset = 0; offset < DISPLAY_WIDTH * DISPLAY_HEIGHT; offset++) {
                        cd[offset] = !cd[offset] ? 0 :
                            ((((cd[offset] - 1) & 006) << 5) + ((cd[offset] - 1) & 007) * 011);
                        sum += !!cd[offset];
                    }

                    display_buffer_copy (1, 0);
                    delay_ms(50);
                } while (sum);

                init_random();
                break;
            }
        }
        for(int offset = maxRecent - 1; offset > 0; offset--) {
            recent[offset] = recent[offset - 1];
        }
        recent[0] = curstate;

        display_buffer_copy (1, 0);
        delay_ms (50);
    }

}
