#include "uTPlib.h"

#include <avr/interrupt.h>

void int_disable()
{
    cli();
}
