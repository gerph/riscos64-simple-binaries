#include <stdio.h>
#include <time.h>
#include "swis.h"

/* Maximum seconds to wait */
#define LIMIT (5)

int main(void)
{
    int i;
    time_t start = time(NULL);
    for (i=0; i<300; i++)
    {
        time_t now = time(NULL);
        printf("time = %i\n", time(NULL));
        _swix(OS_Byte, _IN(0), 19);
        if (now - start > LIMIT)
            break;
    }
    return 0;
}
