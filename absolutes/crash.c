#include <stdarg.h>
#include "swis.h"
#include "swis_os.h"

int myprint(const char *str)
{
    int n = 0;
    for (; *str; str++)
    {
        __os_writec(*str);
        n += 1;
    }

    return n;
}

int print_many(int n, ...)
{
    va_list args;
    va_start(args, n);
    for (n; n; n--)
    {
        const char *str = va_arg(args, const char*);
        myprint(str);
        __os_newline();
    }
    va_end(args);
}

int main(int argc, char *argv[])
{
    return print_many(2, "Hello world", (const char *)0x9876543);
}
