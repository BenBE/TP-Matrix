#include "uTPlib.h"

#include "main.h"

void setup(void);
void loop(void);

void setup()
{
    display_init();
}

void loop()
{
    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);

    string_anim (42);
    pacman();
    string_anim (0);
    heart();
    string_anim (1);
    forest_fire();
    string_anim (2);
    defender();
    string_anim (3);
    leuchtturm();
    string_anim (4);

}
