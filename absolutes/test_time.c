#include <stdio.h>
#include <time.h>
#include "swis.h"

/* Maximum seconds to wait */
#define LIMIT (5)

/* Define this to insert a getchar to pause the clock() */
//#define CHECK_CLOCK_FREEZES

int main(void)
{
    int i;
    time_t start = time(NULL);
    for (i=0; i<300; i++)
    {
        time_t now = time(NULL);
        printf("time = %i, clock = %i\n", time(NULL), clock());
#ifdef CHECK_CLOCK_FREEZES
        if (i == 20)
            getchar();
#endif
        _swix(OS_Byte, _IN(0), 19);
        if (now - start > LIMIT)
            break;
    }
    return 0;
}
