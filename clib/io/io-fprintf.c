#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "swis.h"
#include "io-vprintf.h"
#include "io-internal.h"


static int file_write0(outputter_t *out, const char *str)
{
    FILE *f = (FILE *)out->private;
    int len = strlen(str);
    int wrote;
    wrote = fwrite(str, 1, len, f);
    return wrote;
}

static int file_writen(outputter_t *out, const char *str, size_t len)
{
    FILE *f = (FILE *)out->private;
    int wrote;
    wrote = fwrite(str, 1, len, f);
    return wrote;
}

static int file_writec(outputter_t *out, char c)
{
    FILE *f = (FILE *)out->private;
    int wrote;
    wrote = fputc(c, f);
    return wrote == EOF ? 0 : 1;
}

static int file_newline(outputter_t *out)
{
    return file_writec(out, 10);
}


int vfprintf(FILE *f, const char *format, va_list args)
{
    int n;
    outputter_t out;
    out.write0 = file_write0;
    out.writen = file_writen;
    out.writec = file_writec;
    out.newline = file_newline;
    out.private = (void*)f;
    n = _vprintf(&out, format, args);
    return n;
}

int fprintf(FILE *f, const char *format, ...)
{
    int n;
    va_list args;

    CHECK_MAGIC(f, 0);

    if (!IO_IS_WRITABLE(f))
    {
        return 0;
    }

    va_start(args, format);
    if (IO_IS_SCREEN(f))
        n = vprintf(format, args);
    else
        n = vfprintf(f, format, args);

    va_end(args);
    return n;
}
