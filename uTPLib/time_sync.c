#include "uTPlib.h"

//#include <avr/cpufunc.h>

void time_sync() {
    time_vsynced = 0;
    int_enable();
    while(!time_vsynced) {
        //_MemoryBarrier();
        __asm __volatile("" ::: "memory");
    }
}
