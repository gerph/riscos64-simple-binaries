#include <stddef.h>
#include <string.h>

char *strchr(const char *s, int want)
{
    want = want & 255;
    while (*s != want && *s != '\0')
    {
        s++;
    }
    if (*s == '\0')
        return NULL;
    return (char *)s;
}
