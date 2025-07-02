#include <stdlib.h>

long labs(long i)
{
    if (i<0)
        i = -i;
    return i;
}
