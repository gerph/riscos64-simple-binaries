#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "fs/fs-errors.h"
#include <errno.h>


int feof(FILE *fh)
{
    int32_t at_eof;
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (IO_IS_SCREEN(fh))
        return 0;
    if (IO_IS_KEYBOARD(fh))
    {
        /* FIXME: Should detect EOF? */
        return 0;
    }

    err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 5, fh->_fileno, &at_eof);
    if (err)
    {
        __fs_seterrno(err);
        return 1; /* Error, so return EOF */
    }
    return at_eof ? 1 : 0;
}

int ferror(FILE *fh)
{
    /* FIXME: We don't support error flagging at the moment */
    return 0;
}


int fileno(FILE *fh)
{
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (IO_IS_CONSOLE(fh))
    {
        errno = EBADF;
        return IO_FD_CONSOLE;
    }

    return fh->_fileno;
}


void setbuf(FILE *fh, char *buf)
{
    /* FIXME: We don't support buffering at the moment */
    return;
}

int setvbuf(FILE *fh, char *buf, int type, size_t size)
{
    /* FIXME: We don't support buffering at the moment */
    return 0;
}

void clearerr(FILE *fh)
{
    /* FIXME: We don't support error flagging at the moment */
    return;
}

int isatty(int fd)
{
    if (fd == IO_FD_CONSOLE)
        return 1;
    return 0;
}
