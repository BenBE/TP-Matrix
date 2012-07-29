#include <uTPlib.h>
#include <string.h>

#include "main.h"

void string_doanim (char *s, timebase_t wait_after, color_t color)
{
    coord_t x = DISPLAY_WIDTH;
    coord_t y = 1;

    while (*s && (1 || (x > -FONT_WIDTH) ) ) {
        display_clear_black();
        font_string_printX (x, y, color, s);
        display_buffer_swap (0);

        delay_ms (75);

        x--;

        if (x < -FONT_WIDTH) {
            x += FONT_WIDTH + 1;
            s++;
        }
    }

    delay_ms (wait_after);
}

void string_anim (char id)
{
    display_clear_black();

    switch (id) {
        case 0:
//            string_doanim ("CHAOS in Kiel?", 250, display_color_from_rgb (160, 160, 255) );
            string_doanim ("DON'T PANIC!", 250, display_color_from_rgb (255, 0, 0) );
            break;
        case 1:
//            string_doanim ("Toppoint e.V.", 250, display_color_from_rgb (127, 0, 255) );
            string_doanim ("So long and thanks for all the fish!", 250, display_color_from_rgb (64, 0, 255) );
            break;
        case 2:
//            string_doanim ("Y U NO FRICKL?", 250, display_color_from_rgb (255, 255, 0) );
            string_doanim ("Time is an illusion. Lunch time doubly so.", 250, display_color_from_rgb (255, 255, 0) );
            break;
        case 3:
//            string_doanim ("Diese Laufschrift ist in Ihrem Land nicht verf\206gbar. Das tut uns (nicht) leid!", 250, display_color_from_rgb (255, 255, 255) );
            string_doanim ("Ford, you're turning into a penguin. Stop it.", 250, display_color_from_rgb (255, 255, 255) );
            break;
        case 4:
//            string_doanim ("Stoppt Zensursula, SOPA, PIPA, ACTA, ...!", 500, display_color_from_rgb (255, 0, 0) );
            string_doanim ("Mostly harmless.", 250, display_color_from_rgb (0, 64, 255) );
            break;
        case 5:
//            string_doanim ("F\206r Netzneutralit\204t und m\206ndigen Umgang mit dem Internet!", 500, display_color_from_rgb (0, 255, 0) );
            string_doanim ("Anyone who is capable of being elected president should on no account be allowed to do the job.", 250, display_color_from_rgb (255, 255, 0) );
            break;
        case 6:
//            string_doanim ("F\206r Netzneutralit\204t und m\206ndigen Umgang mit dem Internet!", 500, display_color_from_rgb (0, 255, 0) );
            string_doanim ("ZZ9 Plural Z Alpha", 250, display_color_from_rgb (0, 255, 0) );
            break;
        case 42:
            string_doanim ("The Answer to the Great Question of Life, the Universe, and Everything?        42!", 400, display_color_from_rgb (255, 255, 255) );
            break;
        default:
//            string_doanim ("Bastelst Du noch, oder FRICKLst Du schon?", 500, display_color_from_rgb (0, 255, 0) );
            string_doanim ("The guide is definitive. Reality is frequently inaccurate.", 500, display_color_from_rgb (0, 255, 0) );
    }
}
