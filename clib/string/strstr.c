#include <stddef.h>
#include <string.h>

char *strstr(const char *a, const char *b)
{
    int blen = strlen(b);
    int alen = strlen(a);
    char bc = *b;
    int offset;
    for (offset=0; offset <= alen - blen; offset++)
    {
        if (a[offset] == bc)
        {
            /* This could be the string, try it */
            int diff = strncmp(&a[offset], b, blen);
            if (!diff)
                return (char *)&a[offset];
        }
    }
    return NULL;
}
