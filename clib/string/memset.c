#include <string.h>
#include <stdlib.h>

void *memset(void *odst, int c, size_t size)
{
    char *dst = (char *)odst;
    while (size--)
        *dst++ = c;
    return odst;
}
