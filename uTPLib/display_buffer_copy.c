#include "uTPlib.h"

void display_buffer_copy(buffer_t from, buffer_t to) 
{
    if(from == to)
    {
        return;
    }
    if( from >= DISPLAY_BUFFERS )
    {
        return;
    }
    if( to >= DISPLAY_BUFFERS )
    {
        return;
    }

    for(coord_t x = 0; x < DISPLAY_WIDTH; x++)
    {
        for(coord_t y = 0; y < DISPLAY_HEIGHT; y++)
        {
            display[to][x][y] = display[from][x][y];
        }
    }
}
