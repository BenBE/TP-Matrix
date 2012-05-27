#include <dcf77.h>
#include <dcf77_keys.h>

void dcf77_decode(dcf77_cipherblock_t *buf, dcf77_amdata_t *min1, dcf77_amdata_t *min2, dcf77_amdata_t *min3)
{
    // This method encodes the necessary information to decode the weather information into a cipher block.
    // For this to work the 3x 14 bit information plus some information of the second dcf77_amdata_t block
    // are copied.
    //
    // As some of the bits transmitted in the original stream are not required for the encoded information
    // they are removed in the process as follows:
    /*
     *  Input Block
     *  |Block 1        ||Block 2        | |Block 3        ||Reformatted Time Information from Block 2       |
     *  vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vv|                                                |
     *  0000 0000 0011 1111 1111 2222 2222 2233 3333 3333 4444 4444 4455 5555 5555 6666 6666 6677 7777 7777 88
     *  0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 01
     *   ^^^ ^^^  ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^^^ ^^
     *   ||| |||  |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| |||| ||
     *   vvv vvv  vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv vv
     *   012 345  6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 8901 2345 6789 0123 4567 89
     *   000 000  0000 1111 1111 1122 2222 2222 3333 3333 3344 4444 4444 5555 5555 5566 6666 6666 7777 7777 77
     *  Output Block
     */
    // Internally the first bit of the stream is expected to be in the LSb of the first byte of the cipher block,
    // while the MSb is the MSb of the last byte of the 10-byte cipher block.

    if(!buf) return;
    if(!min1) return;
    if(!min2) return;
    if(!min3) return;

    min1->data.status_information = (buf->data.message.cipher.block1 + (buf->data.message.cipher.block1 & 0x3F)) << 1;
    min2->data.status_information = buf->data.message.cipher.block2;
    min3->data.status_information = buf->data.message.cipher.block3;

    min2->data.time_min_0X = buf->data.keyinfo.data.minute & 0x0F;
    min2->data.time_min_X0 = (buf->data.keyinfo.data.minute & 0x70) >> 4;
    min2->data.time_hour_0X = buf->data.keyinfo.data.hour & 0x0F;
    min2->data.time_hour_X0 = (buf->data.keyinfo.data.hour & 0x30) >> 4;
    min2->data.date_day_0X = buf->data.keyinfo.data.day & 0x0F;
    min2->data.date_day_X0 = (buf->data.keyinfo.data.day & 0x30) >> 4;
    min2->data.date_dow = buf->data.keyinfo.data.dow;
    min2->data.date_month_0X = buf->data.keyinfo.data.month & 0x0F;
    min2->data.date_month_X0 = (buf->data.keyinfo.data.month & 0x10) >> 4;
    min2->data.date_year_0X = buf->data.keyinfo.data.year & 0x0F;
    min2->data.date_year_X0 = (buf->data.keyinfo.data.year & 0xF0) >> 4;

    //Should be one minute before minute 2
    min1->data.time_min_0X = min2->data.time_min_0X;
    min1->data.time_min_X0 = min2->data.time_min_X0;
    min1->data.time_hour_0X = min2->data.time_hour_0X;
    min1->data.time_hour_X0 = min2->data.time_hour_X0;
    min1->data.date_day_0X = min2->data.date_day_0X;
    min1->data.date_day_X0 = min2->data.date_day_X0;
    min1->data.date_dow = min2->data.date_dow;
    min1->data.date_month_0X = min2->data.date_month_0X;
    min1->data.date_month_X0 = min2->data.date_month_X0;
    min1->data.date_year_0X = min2->data.date_year_0X;
    min1->data.date_year_X0 = min2->data.date_year_X0;

    //Should be one minute after minute 2
    min3->data.time_min_0X = min2->data.time_min_0X;
    min3->data.time_min_X0 = min2->data.time_min_X0;
    min3->data.time_hour_0X = min2->data.time_hour_0X;
    min3->data.time_hour_X0 = min2->data.time_hour_X0;
    min3->data.date_day_0X = min2->data.date_day_0X;
    min3->data.date_day_X0 = min2->data.date_day_X0;
    min3->data.date_dow = min2->data.date_dow;
    min3->data.date_month_0X = min2->data.date_month_0X;
    min3->data.date_month_X0 = min2->data.date_month_X0;
    min3->data.date_year_0X = min2->data.date_year_0X;
    min3->data.date_year_X0 = min2->data.date_year_X0;

}
