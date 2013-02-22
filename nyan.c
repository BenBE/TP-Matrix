#include <uTPlib.h>
#include <avr/pgmspace.h>

#include "main.h"

static const uint8_t PROGMEM nyan_body[] = {
    0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C
};
static const uint8_t PROGMEM nyan_grey[] = {
    0x3C, 0x7E, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0x7E, 0x3C
};
static const uint8_t PROGMEM nyan_black[] = {
    0x3C, 0x42, 0x89, 0xA2, 0xA2, 0xA2, 0x89, 0x42, 0x3C
};

void nyancat() {
    coord_t pos = -8;

    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);

    while(pos < DISPLAY_WIDTH - 10) {
        display_clear_color(0100);

        for(coord_t i = 0; i < pos; i++) {
            coord_t y = ((i + pos) >> 1) & 1;
            display_pixel_set(i, y+0, 0007);
            display_pixel_set(i, y+1, 0037);
            display_pixel_set(i, y+2, 0077);
            display_pixel_set(i, y+3, 0070);
            display_pixel_set(i, y+4, 0360);
            display_pixel_set(i, y+5, 0300);
            display_pixel_set(i, y+6, 0306);
        }

        display_sprite_put_P(pos-5, 0, sizeof nyan_body,  8, 0223, nyan_body);
        display_sprite_put_P(pos+0, 0, sizeof nyan_grey,  8, 0133, nyan_grey);
        display_sprite_put_P(pos+0, 0, sizeof nyan_black, 8, 0000, nyan_black);

        coord_t y = !(pos & 3);
        display_pixel_set(pos-4+0+y, 7, 0111);
        display_pixel_set(pos-4+1-y, 8, 0111);
        display_pixel_set(pos+0+1-y, 7, 0111);
        display_pixel_set(pos+0+0+y, 8, 0111);

        display_buffer_swap(1);

        pos++;
        delay_ms(100);
    }

    for(coord_t j = pos; j < pos+2*DISPLAY_WIDTH; j++) {
        display_clear_color(0100);

        for(coord_t i = 0; i < pos; i++) {
            coord_t y = ((i + j) >> 1) & 1;
            display_pixel_set(i, y+0, 0007);
            display_pixel_set(i, y+1, 0037);
            display_pixel_set(i, y+2, 0077);
            display_pixel_set(i, y+3, 0070);
            display_pixel_set(i, y+4, 0360);
            display_pixel_set(i, y+5, 0300);
            display_pixel_set(i, y+6, 0306);
        }

        display_sprite_put_P(pos-5, 0, sizeof nyan_body,  8, 0223, nyan_body);
        display_sprite_put_P(pos+0, 0, sizeof nyan_grey,  8, 0133, nyan_grey);
        display_sprite_put_P(pos+0, 0, sizeof nyan_black, 8, 0000, nyan_black);

        coord_t y = !(j & 3);
        display_pixel_set(pos-4+0+y, 7, 0111);
        display_pixel_set(pos-4+1-y, 8, 0111);
        display_pixel_set(pos+0+1-y, 7, 0111);
        display_pixel_set(pos+0+0+y, 8, 0111);

        display_buffer_swap(1);

        delay_ms(100);
    }

    for(coord_t j = 0; j < pos+8; j++, pos+=j&1) {
        display_clear_color(0100);

        for(coord_t i = j<6 ? 0 : j-6; i < pos; i++) {
            coord_t y = ((i + pos) >> 1) & 1;
            display_pixel_set(i, y+0, 0007);
            display_pixel_set(i, y+1, 0037);
            display_pixel_set(i, y+2, 0077);
            display_pixel_set(i, y+3, 0070);
            display_pixel_set(i, y+4, 0360);
            display_pixel_set(i, y+5, 0300);
            display_pixel_set(i, y+6, 0306);
        }

        display_sprite_put_P(pos-5, 0, sizeof nyan_body,  8, 0223, nyan_body);
        display_sprite_put_P(pos+0, 0, sizeof nyan_grey,  8, 0133, nyan_grey);
        display_sprite_put_P(pos+0, 0, sizeof nyan_black, 8, 0000, nyan_black);

        coord_t y = !(j & 3);
        display_pixel_set(pos-4+0+y, 7, 0111);
        display_pixel_set(pos-4+1-y, 8, 0111);
        display_pixel_set(pos+0+1-y, 7, 0111);
        display_pixel_set(pos+0+0+y, 8, 0111);

        display_buffer_swap(1);

        delay_ms(100);
    }




}
