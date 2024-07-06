#include "swis.h"

int myprint(char *str)
{
    int n = 0;
    for (; *str; str++)
    {
        os_writec(*str);
        n += 1;
    }

    return n;
}

int start(void)
{
    return myprint("Hello world");
}
