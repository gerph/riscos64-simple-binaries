#include <stddef.h>
#include <string.h>

int memcmp(const void *oa, const void *ob, size_t n)
{
    const char *a = (const char *)oa;
    const char *b = (const char *)ob;
    while (n-->0)
    {
        int ac = *a++;
        int bc = *b++;
        if (ac != bc)
        {
            return ac - bc;
        }
    }
    return 0;
}
