#include <stddef.h>
#include <string.h>

int strncmp(const char *a, const char *b, size_t n)
{
    while (n-->0)
    {
        int ac = *a++;
        int bc = *b++;
        if (ac != bc)
        {
            return ac - bc;
        }
        if (ac == 0)
            break;
    }
    return 0;
}
