#include <string.h>
#include <stdlib.h>

void *memmove(void *odst, const void *osrc, size_t size)
{
    char *dst = (char *)odst;
    char *src = (char *)osrc;
    if (src > dst)
    {
        while (size--)
            *dst++ = *src++;
    }
    else
    {
        dst += size;
        src += size;

        while (size--)
            *--dst = *--src;

    }
    return odst;
}
