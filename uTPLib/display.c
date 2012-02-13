#include "uTPlib.h"

screen_t display[DISPLAY_BUFFERS];

screen_t* display_active = &display[0];
screen_t* display_write = &display[1];
