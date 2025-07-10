#include <stddef.h>
#include <string.h>

size_t strcspn(const char *s, const char *charset)
{
    /* Return number of characters at the start of s that are not in charset */
    if (*charset == '\0')
    {
        /* No characters present, so this is the whole string */
        return strlen(s);
    }

    /* We optimise for the charset supplied being a short number of characters */
    if (charset[1] == '\0')
    {
        /* This is a single character */
        char sc = charset[0];
        char c;
        const char *start = s;
        while ((c=*s++) != '\0')
        {
            if (c == sc)
                return s - start - 1;
        }
        return s - start - 1;
    }
    else if (charset[2] == '\0')
    {
        /* There are two characters */
        char sc1 = charset[0];
        char sc2 = charset[1];
        char c;
        const char *start = s;
        while ((c=*s++) != '\0')
        {
            if (c == sc1 || c==sc2)
                return s - start - 1;
        }
        return s - start - 1;
    }

    /* Fall back to dumb search */
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
