#include <stddef.h>
#include <string.h>
#include <stdint.h>

/* The Array form is possibly less efficient as it writes to memory, but
 * it's a little unclear to me how well it compares to the version that has
 * explicit registers for each block of terminators. So I stick with the array
 * form as it looks simpler.
 */
#define USE_ARRAY

char *strpbrk(const char *s, const char *charset)
{
#ifdef USE_ARRAY
    uint64_t terms[4] = {0};
#else
    uint64_t terms0 = 0;
    uint64_t terms1 = 0;
    uint64_t terms2 = 0;
    uint64_t terms3 = 0;
#endif
    uint8_t c;

    /* Return pointer to the first character in charset, in s */
    if (*charset == '\0')
        return NULL; /* Nothing in the charset, so nothing found */
    if (charset[1] == '\0')
        return strchr(s, *charset); /* Only 1 character */

    /* Set up a table of terminators */
    for (; *charset; charset++)
    {
        c = (uint8_t)*charset;
#ifdef USE_ARRAY
        terms[c>>6] |= (1<< (c & 63));
#else
        switch (c>>6)
        {
            case 0: terms0 |= (1<< (c & 63)); break;
            case 1: terms1 |= (1<< (c & 63)); break;
            case 2: terms2 |= (1<< (c & 63)); break;
            default: terms3 |= (1<< (c & 63)); break;
        }
#endif
    }

    while ((c=(uint8_t)*s++) != '\0')
    {
#ifdef USE_ARRAY
        if ((terms[c>>6] >> (c & 63)))
        {
            /* This is a terminator, so return the pointer */
            return s - 1;
        }
#else
        uint64_t terms = 0;
        int chunk = (c>>6);
        if (chunk == 0)
            terms = terms0;
        else
        {
            if (chunk < 2)
                terms = terms1;
            else if (chunk == 2)
                terms = terms2;
            else if (chunk > 2)
                terms = terms3;
        }
        if (terms & (1<< (c & 63)))
            return s - 1;
#endif
    }
    return NULL;
}
