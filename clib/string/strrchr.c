#include <stddef.h>
#include <string.h>

char *strrchr(const char *s, int want)
{
    want = want & 255;
    char *lastchar = NULL;
    while (*s)
    {
        if (*s == want)
            lastchar = (char*)s;
        s++;
    }
    if (*s == want)
        lastchar = (char*)s;
    return lastchar;
}
