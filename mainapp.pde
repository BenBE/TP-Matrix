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

    progress();
    PlayPong();
    string_anim (6);
    game_of_life();
    string_anim (42);
    pacman();
    string_anim (0);
    heart();
    string_anim (1);
    forest_fire();
    string_anim (2);
    nyancat();
    string_anim (3);
    leuchtturm();
    drop2();
    string_anim (4);
    matrix_code();
    string_anim (5);
    bonfire();
}
