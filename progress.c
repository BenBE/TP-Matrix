#include <uTPlib.h>

#include "main.h"

#define BLOCK_WIDTH 6

void progress(void) 
{
    int progress_style = random_range(0, 4);
    timebase_t t0 = time_frame_get();

    for(int i = 0; i <= 100; i++) {

        switch(progress_style) {
            case 0:
                display_clear_color( 0244 );
                for(coord_t x = 0; x < DISPLAY_WIDTH; x++) {
                    display_pixel_set(x, 0, 0111);
                    display_pixel_set(x, DISPLAY_HEIGHT - 1, 0377);
                }
                for(coord_t y = 0; y < DISPLAY_HEIGHT; y++) {
                    display_pixel_set(0, y, 0111);
                    display_pixel_set(DISPLAY_WIDTH - 1, y, 0377);
                }

                for(coord_t x = 2; (x < DISPLAY_WIDTH - 2) && (x - 2 - BLOCK_WIDTH + 1 < (DISPLAY_WIDTH - 4) * i / 100); x += BLOCK_WIDTH) {
                    for(coord_t y = 2; y < DISPLAY_HEIGHT - 2; y++) {
                        for(coord_t x1 = 0; x1 < BLOCK_WIDTH - 2; x1++) {
                            if(x + x1 >= DISPLAY_WIDTH - 2) {
                                break;
                            }
                            display_pixel_set(x + x1, y, 0200);
                        }
                    }
                }

                break;

            case 1:
                display_clear_color( 0377 );

                for(coord_t x = 2; (x < DISPLAY_WIDTH - 2) && (x - 2 - BLOCK_WIDTH + 1 < (DISPLAY_WIDTH - 4) * i / 100); x += BLOCK_WIDTH) {
                    for(coord_t y = 1; y < DISPLAY_HEIGHT - 1; y++) {
                        color_t color = ((1 == y) || (DISPLAY_HEIGHT - 1 == y)) ? 0173 : 0070;
                        for(coord_t x1 = 0; x1 < BLOCK_WIDTH - 1; x1++) {
                            if(x + x1 >= DISPLAY_WIDTH - 2) {
                                break;
                            }
                            display_pixel_set(x + x1, y, color);
                        }
                    }
                }

                break;

            case 2:
                display_clear_color( 0255 );

                timebase_t t = time_frame_get() - t0;
                t %= DISPLAY_WIDTH;

                for(coord_t x = 1; (x < DISPLAY_WIDTH - 1) && (x - 1 < (DISPLAY_WIDTH - 2) * i / 100); x++ ) {
                    for(coord_t y = 1; y < DISPLAY_HEIGHT - 1; y++) {
                        if(x == t) {
                            display_pixel_set(x, y, (y < 3) ? 0377 : 0174);
                        } else {
                            display_pixel_set(x, y, (y < 3) ? 0275 : 0070);
                        }
                    }
                }

                break;

            default:
            {
                display_clear_color( 0000 );

                coord_t w = ( DISPLAY_WIDTH + 1 ) / FONT_WIDTH - 2;
                font_char_print(0, 1, 0377, '[');
                font_char_print(FONT_WIDTH * (w + 1), 1, 0377, ']');
                for( coord_t x = 0; x * 100 / w < i; x++) {
                    font_char_print(FONT_WIDTH * (x + 1), 1, 0377, '=');
                }
                if(i < 100) {
                    font_char_print(FONT_WIDTH * (2 + i * w / 100), 1, 0377, '>');
                }
            }
        }

        delay_ms(random_range(20, 250));
    }

    delay_ms(200);
}