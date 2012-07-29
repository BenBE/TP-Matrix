#include <dcf77.h>
#include <dcf77_keys.h>

void dcf77_cipher_pbox(dcf77_cipherblock_t *data, uint32_t key) {
    uint32_t val4 = 0;
    register uint32_t tmp = 0x00000001;

    for(volatile uint8_t i = 0; i < sizeof(dcf77_key_pbox); i++) {
        if((val4 & (1 << dcf77_cipherdata_read(&dcf77_key_pbox[i]))) != 0) {
            key |= tmp;
        }

        tmp <<= 1;
    }
}
