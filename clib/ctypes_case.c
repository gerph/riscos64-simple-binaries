#include <ctype.h>
#include <string.h>

int (toupper)(int c)
{
    if (c >= 'a' && c <= 'z')
        c -= 32;
    return c;
}

int (tolower)(int c)
{
    if (c >= 'A' && c <= 'Z')
        c += 32;
    return c;
}
