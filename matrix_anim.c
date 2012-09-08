#include "main.h"

#include <uTPlib.h>

#define ABC 12
//    boolean fonts[ABC][4][4] = {
static prog_uint16_t fontmap[ABC] = {
        0x0000, //{ 0x00, 0x00, 0x00, 0x00 },
        /*{
            {0, 0, 0, 0}, //leer
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },*/

        0x01F1, //{ 0x01, 0x0F, 0x01, 0x00 },
        /*{
            {1, 1, 1, 0}, //T
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
        },*/

        0x6996, //{ 0x06, 0x09, 0x09, 0x06 },
        /*{
            {0, 1, 1, 0}, //O
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {0, 1, 1, 0},
        },*/

        0x025F, //{ 0x0F, 0x05, 0x02, 0x00 },
        /*{
            {1, 1, 0, 0}, //P
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
        },*/

        0x09F9, //{ 0x09, 0x0F, 0x09, 0x00 },
        /*{
            {1, 1, 1, 0}, //I
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 1, 0},
        },*/

        0xF42F, //{ 0x0F, 0x02, 0x04, 0x0F },
        /*{
            {1, 0, 0, 1}, //N
            {1, 1, 0, 1},
            {1, 0, 1, 1},
            {1, 0, 0, 1},
        },*/

        0x0D2F, //{ 0x0F, 0x02, 0x0D, 0x00 },
        /*{
            {1, 0, 1, 0}, //K
            {1, 1, 0, 0},
            {1, 0, 1, 0},
            {1, 0, 1, 0},
        },*/

        0x09DF, //{ 0x0F, 0x0D, 0x09, 0x00 },
        /*{
            {1, 1, 1, 0}, //E
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 1, 1, 0},
        },*/

        0x088F, //{ 0x0F, 0x08, 0x08, 0x00 },
        /*{
            {1, 0, 0, 0}, //L
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 1, 0},
        },*/

        0x055F, //{ 0x0F, 0x05, 0x05, 0x00 },
        /*{
            {1, 1, 1, 0}, //F
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
        },*/

        0x0A5F, //{ 0x0F, 0x05, 0x0A, 0x00 },
        /*{
            {1, 1, 0, 0}, //R
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {1, 0, 1, 0},
        },*/

        0x0996, //{ 0x06, 0x09, 0x09, 0x00 },
        /*{
            {0, 1, 1, 0}, //C
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {0, 1, 1, 0},
        }*/
    };

void matrix_code ()
{
    short pause = 100;

    byte toppoint[9] = {1, 2, 3, 3, 2, 4, 5, 1, 0};
    byte frickl[7] = {9, 10, 4, 11, 6, 8, 0};
    byte kiel[5] = {6, 4, 7, 8, 0};
    byte *woerter[3] = {toppoint, frickl, kiel};
    short lauf = 0;
    //    randomSeed (micros() );
    byte rgb[10][3] = {{0, 255, 0}, {0, 159, 0}, {0, 127, 0}, {0, 95, 0}, {0, 63, 0}, {0, 63, 0}, {0, 63, 0}, {0, 63, 0}, {0, 63, 0}, {0, 63, 0}};
    struct zeichenkette {
        signed short x;
        byte *font;
        byte fontzahl;
        signed short zyklus;
    };
    short anzahl = DISPLAY_WIDTH / 8;
    struct zeichenkette zeichen[anzahl];
    short tmp = 0;

    for (short i = 0; i < anzahl; i++) { //init zeichen
        zeichen[i].zyklus = random_range (0, 6) - 5;
        zeichen[i].x = i * 8 + random_range (0, 3);
        tmp = random_range (0, sizeof (woerter) / sizeof (byte*) );
        zeichen[i].font = woerter[tmp];
        tmp = 0;

        while (zeichen[i].font[tmp] != 0) {
            tmp++;
        }

        zeichen[i].fontzahl = tmp;
    }

    while (lauf < 100) { // anzahl schritte
        display_buffer_swap (1);

        for (short i = 0; i < anzahl; i++) {
            if ( (zeichen[i].zyklus >= 0) && (zeichen[i].zyklus < zeichen[i].fontzahl * 5 + DISPLAY_HEIGHT) ) {
                for (short j = 0; j < zeichen[i].fontzahl; j++) { //einzelne buchstaben durchlaufen
                    uint8_t charid = zeichen[i].font[zeichen[i].fontzahl - j - 1];
                    uint16_t charbmp = pgm_read_word ( &fontmap[charid] );
                    for (byte ix = 0; ix < 4; ix++) {
                        for (byte iy = 0; iy < 4; iy++) {
                            if ( (charbmp & 1) != 0 ) {
                                display_pixel_set (ix + zeichen[i].x, iy + j * 5 + zeichen[i].zyklus - zeichen[i].fontzahl * 5, display_color_from_rgb ( rgb[zeichen[i].fontzahl - j - 1][0], rgb[zeichen[i].fontzahl - j - 1][1], rgb[zeichen[i].fontzahl - j - 1][2] ) );
                            }
                            charbmp >>= 1;
                        }
                    }
                }

                zeichen[i].zyklus++;
            } else if (zeichen[i].zyklus < 0) { //warte, bis die zeit reif ist
                zeichen[i].zyklus++;
            } else { //neu initialisieren
                zeichen[i].zyklus = random_range (0, 10) - 9;
                zeichen[i].x = i * 8 + random_range (0, 3);
                tmp = random_range (0, sizeof (woerter) / sizeof (byte*) );
                zeichen[i].font = woerter[tmp];
                tmp = 0;

                while (zeichen[i].font[tmp] != 0) {
                    tmp++;
                }

                zeichen[i].fontzahl = tmp;
            }
        }

        delay_ms (pause);
        lauf++;
    }
}

