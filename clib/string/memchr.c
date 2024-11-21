#include <stddef.h>
#include <string.h>

void *memchr(const void *s, int want, size_t n)
{
    char *t = (char *)s;
    for (; n>0 && *t != want; t++, n--)
        ;
    if (n <= 0)
        return NULL;
    return (void *)t;
}
