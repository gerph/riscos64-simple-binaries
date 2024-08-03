#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "swis.h"
#include "io-vprintf.h"


static int stdout_write0(outputter_t *out, const char *str)
{
    os_write0(str);
    return strlen(str);
}

static int stdout_writen(outputter_t *out, const char *str, size_t len)
{
    os_writen(str, len);
    return len;
}

static int stdout_writec(outputter_t *out, char c)
{
    os_writec(c);
    return 1;
}

static int stdout_newline(outputter_t *out)
{
    os_newline();
    return 1;
}

int vprintf(const char *format, va_list args)
{
    int n;
    outputter_t out;
    out.write0 = stdout_write0;
    out.writen = stdout_writen;
    out.writec = stdout_writec;
    out.newline = stdout_newline;
    n = _vprintf(&out, format, args);
    return n;
}

int printf(const char *format, ...)
{
    int n;
    va_list args;
    va_start(args, format);

    n = vprintf(format, args);

    va_end(args);
    return n;
}
