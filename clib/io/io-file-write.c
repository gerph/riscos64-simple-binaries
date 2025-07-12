#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "fs/fs-errors.h"
#include <errno.h>


size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }
    if (size == 0 || nitems == 0)
        return 0;

    CHECK_MAGIC(fh, -1);

    if (!IO_IS_WRITABLE(fh))
    {
        return 0;
    }

    if (IO_IS_SCREEN(fh))
    {
        size_t total = size * nitems;
        while (total)
        {
            const char *next_nl = memchr(ptr, '\n', total);
            if (next_nl == NULL)
            {
                os_writen(ptr, total);
                break;
            }
            int to_nl = (next_nl - (const char *)ptr);
            os_writen(ptr, to_nl);
            os_newline();
            total -= to_nl + 1;
            ptr = ((const char *)ptr) + to_nl + 1;
        }
        return size * nitems;
    }

    size_t transfer = size * nitems;
    size_t not_transferred = 0;
    err = _swix(OS_GBPB, _INR(0, 3)|_OUT(3), 2, fh->_fileno, ptr, transfer, &not_transferred);
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }
    else
    {
        /* No error, so unmark as any character pushed back */
        fh->_flags &= ~ _IO_CHARPUSHED;
    }

    return transfer - not_transferred;
}

int fflush(FILE *fh)
{
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (!IO_IS_WRITABLE(fh))
    {
        return 0;
    }

    if (IO_IS_CONSOLE(fh))
        return 0;

    /* FIXME: Could call the flush OS_Args call */
    return 0;
}


int fputc(int c, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (!IO_IS_WRITABLE(fh))
    {
        return 0;
    }

    if (IO_IS_SCREEN(fh))
    {
        if (c == '\n')
            os_newline();
        else
            os_writec(c);
        return c;
    }

    err = _swix(OS_BPut, _INR(0, 1), c, fh->_fileno);
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }
    else
    {
        /* No error, so unmark as any character pushed back */
        fh->_flags &= ~ _IO_CHARPUSHED;
    }

    return c;
}

int putc(int c, FILE *fh)
{
    return fputc(c, fh);
}

int fputs(const char *str, FILE *fh)
{
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }
    if (str == NULL)
        str = "<NULL>";

    int len = strlen(str);
    int wrote;

    wrote = fwrite(str, 1, len, fh);
    fputc('\n', fh);
    wrote += 1;
    return wrote;
}
