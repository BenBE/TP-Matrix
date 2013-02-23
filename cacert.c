#include "main.h"

#include <uTPlib.h>

static const uint8_t PROGMEM cacert_guy1[] = {
    0x04, 0x08, 0x90, 0x74, 0x10, 0x14, 0x08, 0x00, 0x00
};

static const uint8_t PROGMEM cacert_guy2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x3A, 0x48, 0x88
};

void cacert(void) {
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);

    font_string_printX(12, 1, display_color_from_rgb(17, 86, 140), "CAcert");

    display_sprite_put_P(1, 0, sizeof cacert_guy1,  8, display_color_from_rgb(0, 190, 0), cacert_guy1);
    display_sprite_put_P(1, 0, sizeof cacert_guy2,  8, display_color_from_rgb(199, 255, 0), cacert_guy2);

    display_buffer_swap(0);
    delay_s(5);
}
