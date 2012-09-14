#include "uTPlib.h"


#ifndef X86

#include <avr/interrupt.h>

void int_enable()
{
    sei();
}

#else 

void int_enable(){}

#endif
