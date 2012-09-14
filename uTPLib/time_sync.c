#include "uTPlib.h"

//#include <avr/cpufunc.h>

void time_sync() {
    time_vsynced = 0;
    int_enable();
    #ifndef X86
    while(!time_vsynced) {
        //_MemoryBarrier();
        __asm __volatile("" ::: "memory");
    }
    #else 
    pthread_cond_wait(&c_time_sync,&m_time_sync);
    #endif
}
