/* From: https://github.com/freebsd/freebsd-src/blob/74ecdf86d8d2a94a4bfcf094a2e21b4747e4907f/sys/libkern/strcasecmp.c#L41 */
#include <ctype.h>
#include <stdlib.h>

int
strcasecmp(const char *s1, const char *s2)
{
    const u_char *us1 = (const u_char *)s1, *us2 = (const u_char *)s2;

    while (tolower(*us1) == tolower(*us2)) {
        if (*us1++ == '\0')
            return (0);
        us2++;
    }
    return (tolower(*us1) - tolower(*us2));
}

int
strncasecmp(const char *s1, const char *s2, size_t n)
{

    if (n != 0) {
        const u_char *us1 = (const u_char *)s1;
        const u_char *us2 = (const u_char *)s2;

        do {
            if (tolower(*us1) != tolower(*us2))
                return (tolower(*us1) - tolower(*us2));
            if (*us1++ == '\0')
                break;
            us2++;
        } while (--n != 0);
    }
    return (0);
}
