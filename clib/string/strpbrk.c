#include <stddef.h>
#include <string.h>
#include <stdint.h>

/* The Array form is possibly less efficient as it writes to memory, but
 * it's a little unclear to me how well it compares to the version that has
 * explicit registers for each block of terminators. So I stick with the array
 * form as it looks simpler.
 */
#define USE_ARRAY

/* Use filter is a fast reject that we can use on each character to check if
 * it could be a terminator, before we check explicitly with each bitmap.
 */
//#define USE_FILTER

char *strpbrk(const char *s, const char *charset)
{
#ifdef USE_ARRAY
    uint64_t terms[4] = {1,0,0,0};
#else
    uint64_t terms0 = 1;
    uint64_t terms1 = 0;
    uint64_t terms2 = 0;
    uint64_t terms3 = 0;
#ifdef USE_FILTER
    uint64_t termsfilter;
#endif
#endif
    uint8_t c;

    /* Return pointer to the first character in charset, in s */
    if (*charset == '\0')
        return NULL; /* Nothing in the charset, so nothing found */
    if (charset[1] == '\0')
        return strchr(s, *charset); /* Only 1 character */
    if (charset[2] == '\0')
    {
        /* Only 2 characters, so we can do this with a completely separate implementation which should be faster */
        uint8_t c1 = charset[0];
        uint8_t c2 = charset[1];
        do {
            c = *s++;
            if (c == '\0')
                return NULL; /* Not found */
            if (c == c1 || c == c2)
                return s-1;
        } while (1);
    }

    /* Set up a table of terminators */
    for (; *charset; charset++)
    {
        c = (uint8_t)*charset;
#ifdef USE_ARRAY
        terms[c>>6] |= (1u<< (c & 63));
#else
        switch (c>>6)
        {
            case 0: terms0 |= (1u<< (c & 63)); break;
            case 1: terms1 |= (1u<< (c & 63)); break;
            case 2: terms2 |= (1u<< (c & 63)); break;
            default: terms3 |= (1u<< (c & 63)); break;
        }
#endif
    }
#ifdef USE_FILTER
    termsfilter = terms0 | terms1 | terms2 | terms3;
#endif

    while (1)
    {
        c=(uint8_t)*s++;
#ifdef USE_ARRAY
        if ((terms[c>>6] >> (c & 63)) & 1)
        {
            /* This is a terminator, so return the pointer */
            return s - 1;
        }
#else
#ifdef USE_FILTER
        if ((termsfilter>>(c & 63)) & 1)
            goto check;

        continue;
check:
#endif
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
        if ((terms>>(c & 63)) & 1)
        {
            if (c==0)
                return NULL;
            return s - 1;
        }
#endif
    }
    return NULL;
}
