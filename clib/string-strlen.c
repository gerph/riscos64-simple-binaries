#include <stddef.h>
#include <string.h>

size_t strlen(const char *s)
{
    const char *os = s;
    while (*s++ != '\0')
        ;
    return s - os - 1;
}
