#include "uTPlib.h"

#include <WProgram.h>

uint8_t display_lut_data[2][8] = {
    {	0x00,	0x80,	0x88,	0x91,	0xA4,	0xAA,	0xEE,	0xFF	},
    {	0x00,	0x80,	0x88,	0x24,	0xA4,	0xAA,	0xEE,	0xFF	}
    };

int display_lut_step = 4;
uint8_t *display_lut_cur = display_lut_data[0];

static inline void pixel_to_matrix(register unsigned char pixel) {
  register unsigned char r,g,b;
  r = pixel & 0x07;
  g = (pixel >>= 3) & 0x07;
  b = (pixel >> 2) & 0x06;
  r = display_lut_cur[r] & 0x08;
  g = display_lut_cur[g] & 0x08;
  b = display_lut_cur[b] & 0x08;

  pixel = PORTB & ~0x28;
  PORTB = pixel += b;
  PORTB = pixel + 0x20;
  PORTB = pixel -= b;

  PORTB = pixel += g;
  PORTB = pixel + 0x20;
  PORTB = pixel -= g;

  PORTB = pixel += r;
  PORTB = pixel + 0x20;
  PORTB = pixel - r;
}

void display_interrupt()
{ 
    //              0:&=          1:|=
    // SCK =13; PB5 0xDF 11011111 0x20 00100000
    // Data=11; PB3 0xF7 11110111 0x08 00001000
    // LE  =10; PB2 0xFB 11111011 0x04 00000100
    // OE  = 9; PB1 0xFD 11111101 0x02 00000010

    PORTB &=~ 0x2E;

    color_t *scr_y = &(*display_active)[0][DISPLAY_HEIGHT-1];
//    color_t *scr_y = &display[0][0][DISPLAY_HEIGHT-1];
    for(char x = 0; x < DISPLAY_WIDTH; x++, scr_y += 2 * DISPLAY_HEIGHT)
    {
        for(char y = 0; y < DISPLAY_HEIGHT; y++)
        {
            pixel_to_matrix( *scr_y-- ); // rgb bits: bbgggrrr
        }
    }

    PORTB |= 0x04;  // repeat same to wait a bit (one cmd = 2clocks)

    for(int i = 0; i < 8; i++)
    {
        display_lut_cur[i] = rot_left(display_lut_cur[i], 1);
    }
    display_lut_step++;
    display_lut_step &= 0x0F;
    display_lut_cur = display_lut_data[(display_lut_step >> 3) & 1];

    PORTB &=~ 0x04;

    time_vsynced = 1;
    time_frame++;
}

