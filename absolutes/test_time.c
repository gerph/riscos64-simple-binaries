#include <stdio.h>
#include <time.h>
#include "swis.h"

int main(void)
{
    for (int i=0; i<300; i++)
    {
        printf("time = %i\n", time(NULL));
        _swix(OS_Byte, _IN(0), 19);
    }
    return 0;
}
