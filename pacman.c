#include <uTPlib.h>

#include "main.h"

const uint8_t PROGMEM gespenst_sprite[9] = {
    0xFC, 0x7E, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7E, 0xFC
};

/*
const prog_uint8_t gespenst_pixel[8][9] = {
    {0, 0, 1, 1, 1, 1, 1, 0, 0},		2⁰=  1
    {0, 1, 1, 1, 1, 1, 1, 1, 0},		2¹=  2
    {1, 1, 1, 1, 1, 1, 1, 1, 1},		2²=  4
    {1, 1, 1, 1, 1, 1, 1, 1, 1},		2³=  8
    {1, 1, 1, 1, 1, 1, 1, 1, 1},		2⁴= 16
    {1, 1, 1, 1, 1, 1, 1, 1, 1},		2⁵= 32
    {1, 1, 1, 1, 1, 1, 1, 1, 1},		2⁶= 64
    {1, 0, 1, 0, 1, 0, 1, 0, 1}			2⁷=128
};

1111 1100 = 252 = 0xFC
*/

const uint8_t PROGMEM pacman_gefressen_sprite [6][6] = {
    {0x1E, 0x3F, 0x1E, 0x1E, 0x3F, 0x1E},
    {0x1E, 0x3E, 0x38, 0x38, 0x3E, 0x1E},
    {0x1C, 0x3C, 0x38, 0x38, 0x3C, 0x1C},
    {0x10, 0x38, 0x38, 0x38, 0x38, 0x10},
    {0x00, 0x30, 0x38, 0x38, 0x30, 0x00},
    {0x00, 0x00, 0x38, 0x38, 0x00, 0x00}
};

void pacman()
{
    display_buffer_active_set(0);
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_write_set (1); //bildschirm leeren
    display_clear_black();
    //    randomSeed (micros() );

    uint8_t richtung = 1;
    uint8_t gespenst = random_range (0, 4);

    uint8_t gespenst_frisst_pacman = 1 < random_range (1, 4);
    gespenst_frisst_pacman = 0;

    coord_t gespenst_pacman_offset = random_range (8, DISPLAY_WIDTH - 16);

    uint8_t module = DISPLAY_WIDTH / 4;

    uint8_t punkte[module];

    uint8_t punkte_pos[7] = {7, 5, 3, 2, 1, 3, 3};

    for (int i = 0; i < module; i++) { // punkte einfliegen
        punkte[i] = 1;

        for (int j = 0; j < 7; j++) {
            display_buffer_swap (2);

            if (j > 0) {
                display_pixel_set (2 + (i * 4), punkte_pos[j - 1], display_color_from_rgb ( 0, 0, 0 ) );
            }

            display_pixel_set (2 + (i * 4), punkte_pos[j], display_color_from_rgb ( 255, 255, 255 ) );
            delay_ms (30);
        }

        delay_ms (300);
    }

    delay_ms (1500);

    uint8_t ende = 0;
    uint8_t pacman_status = 0; // 0 = maul auf; 1 = halb zu, schließend; 2 = zu, 3 = halb zu, öffnend; >3 = pacman wird gefressen;

    uint8_t gespenst_status = true; // gespenster"fuß"status

    color_t gespenst_color;

    switch (gespenst) {
        case 0:
            gespenst_color = display_color_from_rgb ( 255,   0,   0 );
            break;
        case 1:
            gespenst_color = display_color_from_rgb ( 255,   0, 255 );
            break;
        case 2:
            gespenst_color = display_color_from_rgb (   0, 255, 255 );
            break;
        default:
            gespenst_color = display_color_from_rgb ( 255, 128,   0 );
            break;
    }

    uint8_t gespenst_pos;
    uint8_t pacman_pos;

    if (richtung) {
        pacman_pos = 0;
        gespenst_pos = 0;
    } else {
        pacman_pos = DISPLAY_WIDTH;
        gespenst_pos = DISPLAY_WIDTH;
    }

    int lauf = 0;

    while (!ende) {
        display_buffer_swap (1);

        //punkte malen
        for (int i = 0; i < module; i++) {
            uint8_t x_pos;

            if (richtung) {
                x_pos = 2 + i * 4;
            } else {
                x_pos = DISPLAY_WIDTH - (2 + i * 4);
            }

            if (punkte[i]) {
                display_pixel_set (x_pos, 3, display_color_from_rgb ( 255, 255, 255 ) );
            }
        }

        if (richtung) {

            //pacman malen
            if (pacman_status < 4) {
                display_pixel_set (pacman_pos - 4, 1, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 3, 1, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 2, 1, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 1, 1, display_color_from_rgb ( 255, 255, 0 ) );

                display_pixel_set (pacman_pos - 5, 2, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 4, 2, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 3, 2, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 2, 2, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 1, 2, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos    , 2, display_color_from_rgb ( 255, 255, 0 ) );

                display_pixel_set (pacman_pos - 5, 3, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 4, 3, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 3, 3, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 2, 3, display_color_from_rgb ( 255, 255, 0 ) );

                display_pixel_set (pacman_pos - 5, 4, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 4, 4, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 3, 4, display_color_from_rgb ( 255, 255, 0 ) );



                /*switch (pacman_status) {
                 case B00000000: if (lauf % 2 == 0) pacman_status = 1;
                 case B00000001: my_paint(pacman_pos - 1, 3, 255, 255, 0);
                                 my_paint(pacman_pos    , 3, 255, 255, 0);
                                 pacman_status <<= 1;
                                 break;
                 case B00000010: my_paint(pacman_pos - 2, 3, 255, 255, 0);
                                 my_paint(pacman_pos - 1, 3, 255, 255, 0);
                                 my_paint(pacman_pos    , 3, 255, 255, 0);

                                 my_paint(pacman_pos - 2, 4, 255, 255, 0);
                                 my_paint(pacman_pos - 1, 4, 255, 255, 0);
                                 my_paint(pacman_pos    , 4, 255, 255, 0);
                                 pacman_status |= 1;
                                 break;
                 case B00000011: my_paint(pacman_pos - 1, 3, 255, 255, 0);
                                 my_paint(pacman_pos    , 3, 255, 255, 0);
                                 pacman_status = 0;
                                 break;
                 default: break;
                }*/
                if (pacman_status == 0) {
                    pacman_status = 1;
                } else if (pacman_status == 1) {
                    display_pixel_set (pacman_pos - 1, 3, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos    , 3, display_color_from_rgb ( 255, 255, 0 ) );
                    pacman_status = 2;
                } else if (pacman_status == 2) {
                    display_pixel_set (pacman_pos - 2, 3, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos - 1, 3, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos    , 3, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos - 2, 4, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos - 1, 4, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos    , 4, display_color_from_rgb ( 255, 255, 0 ) );
                    pacman_status = 3;
                } else if (pacman_status == 3) {
                    display_pixel_set (pacman_pos - 1, 3, display_color_from_rgb ( 255, 255, 0 ) );
                    display_pixel_set (pacman_pos    , 3, display_color_from_rgb ( 255, 255, 0 ) );
                    pacman_status = 0;
                }


                display_pixel_set (pacman_pos - 5, 5, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 4, 5, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 3, 5, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 2, 5, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 1, 5, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos    , 5, display_color_from_rgb ( 255, 255, 0 ) );

                display_pixel_set (pacman_pos - 4, 6, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 3, 6, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 2, 6, display_color_from_rgb ( 255, 255, 0 ) );
                display_pixel_set (pacman_pos - 1, 6, display_color_from_rgb ( 255, 255, 0 ) );


                if ( (pacman_pos + 1) % 4 == 0) {
                    punkte[ ( (pacman_pos + 1) / 4) - 1] = 0;
                }

                //gespenst malen

                if (pacman_pos > gespenst_pacman_offset) {
                    display_sprite_put_P (gespenst_pos - 8, 0, 9, 8, gespenst_color, gespenst_sprite);

                    //augen malen
                    display_pixel_set (gespenst_pos - 2, 2, display_color_from_rgb ( 255, 255, 255 ) );
                    display_pixel_set (gespenst_pos - 3, 3, display_color_from_rgb ( 255, 255, 255 ) );
                    display_pixel_set (gespenst_pos - 3, 2, display_color_from_rgb ( 255, 255, 255 ) );
                    display_pixel_set (gespenst_pos - 2, 3, display_color_from_rgb (   0,   0,   0 ) );

                    display_pixel_set (gespenst_pos - 5, 2, display_color_from_rgb ( 255, 255, 255 ) );
                    display_pixel_set (gespenst_pos - 6, 3, display_color_from_rgb ( 255, 255, 255 ) );
                    display_pixel_set (gespenst_pos - 6, 2, display_color_from_rgb ( 255, 255, 255 ) );
                    display_pixel_set (gespenst_pos - 5, 3, display_color_from_rgb (   0,   0,   0 ) );

                    if (!gespenst_status) {
                        for (int f = 0; f < 9; f++) {
                            if (f % 2 == 0) {
                                display_pixel_set (gespenst_pos - f, 7, display_color_from_rgb ( 0, 0, 0 ) );
                            } else {
                                display_pixel_set (gespenst_pos - f, 7, gespenst_color );
                            }
                        }
                    }

                    gespenst_status = !gespenst_status;
                }

            }

            if ( (gespenst_pos != 0) && ( (pacman_pos - gespenst_pos) < 4) ) {
                if (pacman_status < 3) {
                    pacman_status = 3;
                }

                if (pacman_status == 3) {
                    delay_ms (222);
                }

                pacman_status++;

                display_sprite_put_P (pacman_pos - 5, 0, 6, 6, display_color_from_rgb ( 255, 255, 0 ), pacman_gefressen_sprite[pacman_status - 4]);

                delay_ms (50);
            }

            if (pacman_status < 4) {
                if (lauf % 2 == 0) {
                    pacman_pos++;
                }

                if ( (lauf % 2 == 0) && (pacman_pos > gespenst_pacman_offset) ) {
                    if (gespenst_frisst_pacman) {
                        gespenst_pos += 2;
                    } else {
                        gespenst_pos++;
                    }
                }
            }

            lauf++;

            if ( (gespenst_pos - 16) > DISPLAY_WIDTH) {
                ende = 1;
            }

            if (pacman_status > 20) {
                ende = 1;
            }

            if (lauf >= 200) {
                ende = 1;
            }

            delay_ms (100);
        } else {
            //To ensure to finish the animation
            ende = 1;
        }
    }
}
