#include <stddef.h>
#include <string.h>

size_t strcspn(const char *s, const char *charset)
{
    /* Return number of characters at the start of s that are not in charset */
    size_t count = 0;
    char c;
    while ((c=*s++) != '\0')
    {
        const char *search = charset;
        char sc;
        while ((sc=*search++) != '\0')
            if (sc == c)
                return count;
        count++;
    }
    return count;
}
