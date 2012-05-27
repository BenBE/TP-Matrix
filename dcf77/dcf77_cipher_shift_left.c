#include <dcf77.h>
#include <dcf77_keys.h>

void dcf77_cipher_shift_left(uint8_t round, dcf77_cipherblock_t *buf) {
    if(!buf) return;

    register uint8_t count;
    register uint8_t tmp;

    if ((round == 16) || (round == 8) || (round == 7) || (round == 3)) {
        count = 2;
    } else {
        count = 1;
    }

    while (count--) {
        tmp = 0;

        if ((buf->data.keyinfo.raw[4] & 0x80) != 0) {
            tmp = 1;
        }

        buf->data.keyinfo.raw[4] <<= 1;

        if ((buf->data.keyinfo.raw[3] & 0x80) != 0) {
            buf->data.keyinfo.raw[4] |= 1;
        }

        buf->data.keyinfo.raw[3] <<= 1;

        if ((buf->data.keyinfo.raw[2] & 0x80) != 0) {
            buf->data.keyinfo.raw[3] |= 1;
        }

        buf->data.keyinfo.raw[2] <<= 1;

        if ((buf->data.keyinfo.raw[1] & 0x80) != 0) {
            buf->data.keyinfo.raw[2] |= 1;
        }

        buf->data.keyinfo.raw[1] <<= 1;

        if ((buf->data.keyinfo.raw[0] & 0x80) != 0) {
            buf->data.keyinfo.raw[1] |= 1;
        }

        buf->data.keyinfo.raw[0] <<= 1;

        if ((buf->data.keyinfo.raw[2] & 0x10) != 0) {
            buf->data.keyinfo.raw[0] |= 1;
        }

        buf->data.keyinfo.raw[2] &= 0xEF;

        if (tmp != 0) {
            buf->data.keyinfo.raw[2] |= 0x10;
        }
    }
}
