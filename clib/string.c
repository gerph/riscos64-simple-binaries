#include <stddef.h>
#include <string.h>


int strcmp(const char *a, const char *b)
{
    while (1)
    {
        int ac = *a++;
        int bc = *b++;
        if (ac != bc)
        {
            return ac - bc;
        }
        if (ac == 0)
            return 0;
    }
}


char *strcat(char *a, const char *b)
{
    char *oa = a;
    /* Find the end of the string */
    while (*a++)
        ;
    while (1)
    {
        char c = *b++;
        *a++ = c;
        if (c=='\0')
            break;
    }
    return oa;
}


char *strncat(char *a, const char *b, size_t n)
{
    char *oa = a;
    /* Find the end of the string */
    while (*a++)
        ;
    while (--n >= 0)
    {
        char c = *b++;
        *a++ = c;
        if (c=='\0')
            break;
    }
    return oa;
}


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


char *strncpy(char *dst, const char *src, size_t n)
{
    char *odst = dst;
    while (n-->0)
    {
        int c = *src++;
        *dst++ = c;
        if (!c)
            break;
    }
    return odst;
}


char *strchr(const char *s, int want)
{
    while (*s != want)
    {
        if (*s == '\0')
            return NULL;
        s++;
    }
    return (char *)s;
}


char *strrchr(const char *s, int want)
{
    char *lastchar = NULL;
    while (*s)
    {
        if (*s == want)
            lastchar = (char*)s;
        s++;
    }
    return lastchar;
}


void *memchr(const void *s, int want, size_t n)
{
    char *t = (char *)s;
    for (; n>0 && *t != want; t++, n--)
        ;
    if (n <= 0)
        return NULL;
    return (void *)t;
}

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
