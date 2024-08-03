#include <string.h>
#include <stdlib.h>

void *memcpy(void *odst, const void *osrc, size_t size)
{
    char *dst = (char *)odst;
    char *src = (char *)osrc;
    while (size--)
        *dst++ = *src++;
    return odst;
}


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


void *memset(void *odst, int c, size_t size)
{
    char *dst = (char *)odst;
    while (size--)
        *dst++ = c;
    return odst;
}
