#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* Define this to have a special memcpy for 4-byte aligned to 4-byte aligned */
#define OPTIMISE_ALIGNED_COPIES

void *memcpy(void *odst, const void *osrc, size_t size)
{
    char *dst = (char *)odst;
    char *src = (char *)osrc;
#ifdef OPTIMISE_ALIGNED_COPIES
    if (size > 8)
    {
        /* This doesn't actually optimise all that well according to what I see
         * in godbolt.org, but I'm willing to believe it's still better than
         * the single byte copy.
         */
        if ((((intptr_t)odst) & 3) == 0 && (((intptr_t)osrc) & 3) == 0)
        {
            uint64_t *llsrc = (uint64_t *)osrc;
            uint64_t *lldst = (uint64_t *)odst;
            while (size >= 8*4)
            {
                *lldst++ = *llsrc++;
                *lldst++ = *llsrc++;
                *lldst++ = *llsrc++;
                *lldst++ = *llsrc++;
                size -= 8*4;
            }
            while (size >= 8)
            {
                *lldst++ = *llsrc++;
                size -= 8;
            }
            src = (char*)llsrc;
            dst = (char*)lldst;
        }
    }
#endif
    while (size >= 4)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst+=4;
        src+=4;
        size -= 4;
    }
    while (size--)
        *dst++ = *src++;
    return odst;
}
