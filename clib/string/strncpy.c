#include <stddef.h>
#include <string.h>

char *strncpy(char *dst, const char *src, size_t n)
{
    char *odst = dst;
    while (n-->0)
    {
        int c = *src++;
        *dst++ = c;
        if (!c)
            break;
    }
    return odst;
}
