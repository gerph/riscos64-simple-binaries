#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* Uncomment to use a simple byte copy */
//#define SIMPLE

void *memset(void *odst, int c, size_t size)
{
    char *dst = (char *)odst;
#ifdef SIMPLE
    while (size--)
        *dst++ = c;
#else
    uintptr_t alignsize = ((uintptr_t)odst) & 15;
    if (alignsize)
    {
        alignsize = 15 - alignsize;
        if (alignsize <= size)
        {
            size -= alignsize;
            while (alignsize--)
                *dst++ = c;
        }
    }
    if (size < 16)
    {
        while (size--)
            *dst++ = c;
    }
    else
    {
        uint64_t *dst64 = (uint64_t *)dst;
        uint64_t c64 = c | (c<<8);
        c64 = c64 | (c64<<16);
        c64 = c64 | (c64<<32);
        while (size >= 32)
        {
            *dst64++ = c64;
            *dst64++ = c64;
            *dst64++ = c64;
            *dst64++ = c64;
            size -= 32;
        }
        while (size >= 8)
        {
            *dst64++ = c64;
            size -= 8;
        }
        dst = (char *)dst64;
        while (size--)
            *dst++ = c;
    }
#endif
    return odst;
}
