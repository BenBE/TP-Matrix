#include "uTPlib.h"

#ifndef X86

#include <avr/interrupt.h>

void int_disable()
{
    cli();
}
#else
  
void int_disable() {}

#endif
