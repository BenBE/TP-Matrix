#include <dcf77.h>
#include <dcf77_keys.h>

uint32_t dcf77_cipher_expand(uint32_t key) {
    uint32_t tmp = 0x00100000;
    register uint32_t result = key & 0x000FFFFF;

    for (volatile register uint8_t i = 0; i < sizeof(dcf77_key_expand); i++) {
        if ((result & (1u << dcf77_key_expand[i])) != 0) {
            result |= tmp;
        }

        tmp <<= 1;
    }

    return result;
}
