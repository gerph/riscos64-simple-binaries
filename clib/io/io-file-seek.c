#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "fs/fs-errors.h"
#include <errno.h>


int fseek(FILE *fh, long int pos, int whence)
{
    _kernel_oserror *err;
    size_t size = 0;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (IO_IS_CONSOLE(fh))
    {
        /* FIXME: Should set errno? */
        return -1;
    }

    switch (whence)
    {
        case SEEK_SET:
            break;

        case SEEK_CUR:
            size_t cur = 0;
            err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 0, fh->_fileno, &cur);
            if (err)
            {
                __fs_seterrno(err);
                return -1;
            }
            pos += cur;
            break;

        case SEEK_END:
            size_t ext = 0;
            err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 2, fh->_fileno, &ext);
            if (err)
            {
                __fs_seterrno(err);
                return -1;
            }
            pos += ext;
            break;
    }
    err = _swix(OS_Args, _INR(0, 2), 1, fh->_fileno, pos);
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
    return 0;
}


long int ftell(FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (IO_IS_CONSOLE(fh))
    {
        /* FIXME: Should set errno? */
        return -1;
    }

    size_t cur = 0;
    err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 0, fh->_fileno, &cur);
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }

    return cur;
}
