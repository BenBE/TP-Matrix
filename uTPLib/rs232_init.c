#include <uTPlib.h>

void rs232_init() {
    rs232_data_mode(rs232_bits_8, rs232_parity_none, rs232_stop_1bit);
    rs232_data_rate(9600, rs232_txmode_ddr);
}
