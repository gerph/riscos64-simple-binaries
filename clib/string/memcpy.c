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
