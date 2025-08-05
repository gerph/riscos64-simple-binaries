/*******************************************************************
 * File:        io-console
 * Purpose:     Simple console input/output functions
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <string.h>
#include "swis_os.h"

#include "io-internal.h"

int getchar(void)
{
    return getc(stdin);
}

int putchar(int c)
{
    return putc(c, stdout);
}

int puts(const char *ptr)
{
    if (ptr == NULL)
        ptr = "<NULL>";

    if (!IO_IS_CONSOLE(stdout))
        return fputs(ptr, stdout);

    int total = strlen(ptr);
    int wrote = 0;

    while (total)
    {
        const char *next_nl = memchr(ptr, '\n', total);
        if (next_nl == NULL)
        {
            os_writen(ptr, total);
            wrote += total;
            break;
        }
        int to_nl = (next_nl - (const char *)ptr);
        if (to_nl)
            os_writen(ptr, to_nl);
        os_newline();
        wrote += to_nl + 1;
        total -= to_nl + 1;
        ptr = ((const char *)ptr) + to_nl + 1;
    }
    os_newline();
    wrote += 1;

    return wrote;
}
