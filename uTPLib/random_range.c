#include <stdlib.h>

#include "uTPlib.h"

int random_range(int min, int max)
{
    return random() % (max - min) + min;
}
