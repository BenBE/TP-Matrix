#ifndef H_DCF77_KEY
#define H_DCF77_KEY

#include <dcf77.h>

//Make this cross-platform:
//Our data will be stored in the flash of the controller on AVR platforms and inside RAM for everything else.
//This saves us ~128 Bytes of RAM for the expense of some performance to access the flash memory
#ifdef __AVR
#include <avr/pgmspace.h>
typedef const prog_uint8_t dcf77_cipherdata_t;
static inline uint8_t dcf77_cipherdata_read(const dcf77_cipherdata_t *ptr) {
    return ptr ? pgm_read_byte(ptr) : 0;
}
#else
typedef const uint8_t dcf77_cipherdata_t;
static inline uint8_t dcf77_cipherdata_read(const dcf77_cipherdata_t *ptr) {
    return ptr ? *ptr : 0;
}
#endif

extern dcf77_cipherdata_t dcf77_key_sbox1[64];
extern dcf77_cipherdata_t dcf77_key_sbox2[64];
extern dcf77_cipherdata_t dcf77_key_sbox3[64];

extern dcf77_cipherdata_t dcf77_key_pbox[20];

extern dcf77_cipherdata_t dcf77_key_expand[10];
extern dcf77_cipherdata_t dcf77_key_compress[30];

extern uint32_t dcf77_cipher_compress(void *buf);
extern uint32_t dcf77_cipher_expand(uint32_t key);
extern void dcf77_cipher_shift_left(uint8_t round, dcf77_cipherblock_t *buf);
extern void dcf77_cipher_shift_right(uint8_t round, dcf77_cipherblock_t *buf);

extern void dcf77_cipher_sbox(dcf77_cipherblock_t *data, uint32_t key);
extern void dcf77_cipher_pbox(dcf77_cipherblock_t *data, uint32_t key);

#endif
