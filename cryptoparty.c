#include <uTPlib.h>

#include "main.h"

// 27
const uint8_t PROGMEM crypto [19] = {
    0x0F, 0x09, 0x09, 0x00, 0x0F, 0x05, 0x0B, 0x00, 0x07, 0x04, 0x0F, 0x00, 0x0F, 0x05, 0x07, 0x00, 0x01, 0x0F, 0x01
};
const uint8_t PROGMEM party [19] = {
    0x0F, 0x05, 0x07, 0x00, 0x0F, 0x05, 0x0F, 0x00, 0x0F, 0x05, 0x0B, 0x00, 0x01, 0x0F, 0x01, 0x00, 0x07, 0x04, 0x0F
};

const uint8_t PROGMEM cryptokey [13][7] = {
    //key right 0-3 h
    //key left  4-8 h
    //key vertical 9-15
    {0x0F, 0x09, 0x0F, 0x04, 0x0C, 0x04, 0x0C},
    {0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04},
    {0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02},
    {0x0F, 0x09, 0x0F, 0x02, 0x03, 0x02, 0x03},
    /* */
    {0x0C, 0x04, 0x0C, 0x04, 0x0F, 0x09, 0x0F},
    {0x04, 0x04, 0x04, 0x04, 0x06, 0x06, 0x06},
    {0x02, 0x02, 0x02, 0x02, 0x06, 0x06, 0x06},
    {0x03, 0x02, 0x03, 0x02, 0x0F, 0x09, 0x0F},
    /* */
    {0x00, 0x0F, 0x0F, 0x04, 0x0C, 0x0C, 0x00},
    {0x00, 0x00, 0x0F, 0x0C, 0x0C, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0C, 0x0C, 0x0F, 0x00, 0x00},
    {0x00, 0x0C, 0x0C, 0x04, 0x0F, 0x0F, 0x00},
};

const uint8_t PROGMEM keyindexV1 [8] = {
    0,1,2,3,3,2,1,0
};
const uint8_t PROGMEM keyindexV2 [8] = {
    4,5,6,7,7,6,5,4
};

const uint8_t PROGMEM keyindexH1 [14] = {
    0,8,9,10,11,12,4,4,12,11,10,9,8,0
};
const uint8_t PROGMEM keyindexH2 [14] = {
    4,12,11,10,9,8,0,0,8,9,10,11,12,4
};

#define BGCOLOR 0

void cryptoparty() {
    display_buffer_write_set(0);
    display_clear_color(BGCOLOR);
    display_buffer_active_set(0);
    display_buffer_write_set(1);
    display_clear_color(BGCOLOR);

    if(random_range(0,2)) {
        for( int i = 0; i < 5; i++) {
            for( uint8_t frame = 0; frame < sizeof(keyindexH1); frame++) {
                display_clear_color(BGCOLOR);
                display_sprite_put_P(10, 0, 19, 4, display_color_from_rgb(0xd9, 0x00, 0xff),crypto); //crypt
                display_sprite_put_P(18, 4, 19, 4, display_color_from_rgb(0xd9, 0x00, 0xff),party);  //party

                uint8_t idx1 = pgm_read_byte(keyindexH1+frame);
                uint8_t idx2 = pgm_read_byte(keyindexH2+frame);

                display_sprite_put_P(30, 0, 7, 4, display_color_from_rgb( 255, 0, 152 ), (uint8_t *)&cryptokey[0][0] + (sizeof cryptokey[0]) * idx1);
                display_sprite_put_P(10, 4, 7, 4, display_color_from_rgb( 255, 0, 152 ), (uint8_t *)&cryptokey[0][0] + (sizeof cryptokey[0]) * idx2);

                display_buffer_copy(1, 0);
                delay_ms(125);
            }
        }
    } else {
        for( int i = 0; i < 5; i++) {
            for( uint8_t frame = 0; frame < sizeof(keyindexV1); frame++) {
                display_clear_color(BGCOLOR);
                display_sprite_put_P(10, 0, 19, 4, display_color_from_rgb(0xd9, 0x00, 0xff),crypto); //crypt
                display_sprite_put_P(18, 4, 19, 4, display_color_from_rgb(0xd9, 0x00, 0xff),party);  //party

                uint8_t idx1 = pgm_read_byte(keyindexV1+frame);
                uint8_t idx2 = pgm_read_byte(keyindexV2+frame);

                display_sprite_put_P(30, 0, 7, 4, display_color_from_rgb( 255, 0, 152 ), (uint8_t *)&cryptokey[0][0] + (sizeof cryptokey[0]) * idx1);
                display_sprite_put_P(10, 4, 7, 4, display_color_from_rgb( 255, 0, 152 ), (uint8_t *)&cryptokey[0][0] + (sizeof cryptokey[0]) * idx2);

                display_buffer_copy(1, 0);
                delay_ms(125);
            }
        }
    }
}
