#include <dcf77.h>
#include <dcf77_keys.h>

void dcf77_decrypt(dcf77_cipherblock_t *data)
{
    // The cipher block contains the raw data as transmitted on the line as follows:
    /*
     *  Input Block
     *  0000 0000 0011 1111 1111 2222 2222 2233 3333 3333 4444 4444 4455 5555 5555 6666 6666 6677 7777 7777 88
     *  0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 01
     *   ^^^ ^^^  ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^
     *   ||| |||  |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| ||
     *   vvv vvv  vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vv
     *   012 345  6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 89
     *   000 000  0000 1111 1111 1122 2222 2222 3333 3333 3344 4444 4444 5555 5555 5566 6666 6666 7777 7777 77
     *  Output Block
     */
    // Note however that for proper encoding of the data you'll need to call dcf77_encode to transform the
    // one-the-wire data into a proper dcf77_cipher_block_t.
    // Internally the first bit of the stream is expected to be in the LSb of the first byte of the cipher block,
    // while the MSb is the MSb of the last byte of the 10-byte cipher block.

    // The registers used for decryption are as follows:
    /*
     *  Input Block
     *  00000 00000 11111 11111 22222 22222 33333 33333 44444 44444 55555 55555 66666 66666 77777 77777
     *  01234 56789 01234 56789 01234 56789 01234 56789 01234 56789 01234 56789 01234 56789 01234 56789
     *  ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^ ^^^^^
     *  ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| ||||| |||||
     *  vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv vvvvv
     *  | Cipher Register L   | | Cipher Register R   | | Cipher Key                                  |
     *  01234 56789 01234 56789 01234 56789 01234 56789 01234 56789 01234 56789 01234 56789 01234 56789
     *  00000 00000 11111 11111 00000 00000 11111 11111 00000 00000 11111 11111 22222 22222 33333 33333
     *  Output Block
     */

    for( volatile unsigned int i = 16; i > 0; i--) {
        dcf77_cipher_shift_right(i, data);

        uint32_t regLDash = dcf77_cipher_expand(data->data.message.cipher_reg.regR);
        regLDash ^= dcf77_cipher_compress(&data->data.keyinfo);

        dcf77_cipher_sbox(data, regLDash);
        dcf77_cipher_pbox(data, regLDash);

        regLDash ^= data->data.message.cipher_reg.regL;
        data->data.message.cipher_reg.regL = data->data.message.cipher_reg.regR;
        data->data.message.cipher_reg.regR = regLDash;
    }

}
