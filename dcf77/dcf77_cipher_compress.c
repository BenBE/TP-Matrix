#include <dcf77.h>
#include <dcf77_keys.h>

uint32_t dcf77_cipher_compress(void *buf) {
    register uint8_t * const p = buf;
    uint32_t tmp = 0x00000001;					// and set bits from 16-1A (time)
    uint32_t result = 0;					// clear 12-15

    for (register uint8_t i = 0; i < sizeof(dcf77_key_compress); i++) {
        const register uint8_t bit = dcf77_cipherdata_read(&dcf77_key_compress[i]);
        if ((p[bit >> 3] & (1 << (bit & 7))) != 0) {
            result |= tmp;
        }

        tmp <<= 1;
    }

    return result;
}
