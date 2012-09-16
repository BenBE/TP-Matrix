#include "main.h"

#include <uTPlib.h>

void PlayPong(void) {
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);

    display_buffer_write_set(1);
    display_clear_black();

    for(coord_t y = 1; y < DISPLAY_HEIGHT; y+=2) {
        display_pixel_set(DISPLAY_WIDTH / 2, y, display_color_from_rgb(128, 128, 128));
        display_pixel_set(DISPLAY_WIDTH - DISPLAY_WIDTH / 2 - 1, y, display_color_from_rgb(128, 128, 128));
    }

    display_pixel_set(DISPLAY_WIDTH / 2, 0, 0377);
    display_pixel_set(DISPLAY_WIDTH - DISPLAY_WIDTH / 2 - 1, 0, 0377);

    int pts_player1 = 0, pts_player2 = 0;
    int pts_max = (DISPLAY_WIDTH - 1) / 2;

    int ball_dx = random_range(0, 2) ? 1 : -1;

    while( (pts_player1 < pts_max) && (pts_player2 < pts_max) ) {
        display_buffer_copy(1, 2);
        display_buffer_write_set(2);
        for(coord_t x = 0; x < pts_player1; x++) {
            display_pixel_set(DISPLAY_WIDTH - DISPLAY_WIDTH / 2 - x - 2, 0, ~x&1 ? 0007 : 0002);
        }
        for(coord_t x = 0; x < pts_player2; x++) {
            display_pixel_set(DISPLAY_WIDTH / 2 + x + 1, 0, ~x&1 ? 0070 : 0020);
        }

        int ball_x = DISPLAY_WIDTH / 2;
        if (ball_dx < 1) ball_x = DISPLAY_WIDTH - DISPLAY_WIDTH / 2 - 1;
        int ball_y = DISPLAY_HEIGHT / 2;
        int ball_dy = 1;

        int pad_player1 = DISPLAY_HEIGHT / 2;
        int pad_player2 = DISPLAY_HEIGHT / 2;

        int step = 0;

        while( (ball_x >= 0) && (ball_x < DISPLAY_WIDTH) ) {
            display_buffer_copy(2, 0);
            display_buffer_write_set(0);

            //Unser Ball
            display_pixel_set(ball_x, ball_y, 0377);

            //Die Schläger
            for(int i = -1; i <= 1; i++) {
                display_pixel_set(0, pad_player1 + i, 007);
                display_pixel_set(DISPLAY_WIDTH - 1, pad_player2 + i, 070);
            }

            //Reflektion am Schläger
            if(0 == ball_x) {
                if(abs (pad_player1 - ball_y) < 2) {
                    ball_dx = 1;
                    ball_dy = random_range(-2, 2);
                    if(0 <= ball_dy) ball_dy++;
                }
            } else if(DISPLAY_WIDTH - 1 == ball_x) {
                if(abs (pad_player2 - ball_y) < 2) {
                    ball_dx = -1;
                    ball_dy = random_range(-2, 2);
                    if(0 <= ball_dy) ball_dy++;
                }
            }

            //Ballbewegung simulieren
            ball_x += ball_dx;
            ball_y += ball_dy;
            step++;

            if(ball_y < 1) {
                ball_y = (1 - ball_y)/*delta am Spiegel*/ + 1/*Offset des Spiegels*/;
                ball_dy = abs(ball_dy);
            } else if(ball_y > DISPLAY_HEIGHT - 1) {
                ball_y = (DISPLAY_HEIGHT - 1)/*Offset des Spiegels*/ - (ball_y - DISPLAY_HEIGHT + 1)/*delta am Spiegel*/;
                ball_dy = -abs(ball_dy);
            }

            if( random_range(0, 3) ) {
                if( (ball_y < pad_player1) && (pad_player1 > 2) ) {
                    pad_player1--;
                }
                if( (ball_y < pad_player2) && (pad_player2 > 2) ) {
                    pad_player2--;
                }

                if( (ball_y > pad_player1) && (pad_player1 < DISPLAY_HEIGHT - 2) ) {
                    pad_player1++;
                }
                if( (ball_y > pad_player2) && (pad_player2 < DISPLAY_HEIGHT - 2) ) {
                    pad_player2++;
                }
            }

            delay_ms(25);
        }

        if(ball_x < 0) {
            pts_player2+=2;
        } else {
            pts_player1+=2;
        }

        delay_ms(500);
    }

}