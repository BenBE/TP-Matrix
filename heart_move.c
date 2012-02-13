#include <uTPlib.h>

#include "main.h"

void heart()
{
    int o = 0;
    int o1 = 0;

    int counter = 66;

    while (counter--) {
        delay_ms (50);
        display_buffer_swap (0);

        // make nice background
        o1++;

        if (o1 >= DISPLAY_WIDTH) {
            o1 = 0;
        }

        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            //int x1=(x+SCRdx-o1)%SCRdx;
            int x1 = (x + o1) % DISPLAY_WIDTH;

            for (int y = 0; y < DISPLAY_HEIGHT; y++) {
                display_pixel_set (x1, y, display_color_from_rgb( x * 255 / DISPLAY_WIDTH, y * 255 / DISPLAY_HEIGHT, 0 ) );
                //scrr[act_buf_write][x1][y]=x*255/SCRdx;
                //scrg[act_buf_write][x1][y]=y*255/SCRdy;
                //scrb[act_buf_write][x1][y]=0;
            }
        }

        // animate blue heart
        if (DISPLAY_WIDTH >= 9) {
            o--;

            if (o < 0) {
                o = DISPLAY_WIDTH - 9;
            }

            //o++; if (o+8>=SCRdx) o=0;
            int rgb = display_color_from_rgb(0, 0, 255);
            (*display_write)[2 + o][0] = rgb;
            (*display_write)[6 + o][0] = rgb;
            (*display_write)[1 + o][1] = rgb;
            (*display_write)[3 + o][1] = rgb;
            (*display_write)[5 + o][1] = rgb;
            (*display_write)[7 + o][1] = rgb;
            (*display_write)[0 + o][2] = rgb;
            (*display_write)[4 + o][2] = rgb;
            (*display_write)[8 + o][2] = rgb;
            (*display_write)[0 + o][3] = rgb;
            (*display_write)[8 + o][3] = rgb;
            (*display_write)[1 + o][4] = rgb;
            (*display_write)[7 + o][4] = rgb;
            (*display_write)[2 + o][5] = rgb;
            (*display_write)[6 + o][5] = rgb;
            (*display_write)[3 + o][6] = rgb;
            (*display_write)[5 + o][6] = rgb;
            (*display_write)[4 + o][7] = rgb;
            // Use of scr[act_buf_write][x][y] is discouraged...
        }
    }
}

