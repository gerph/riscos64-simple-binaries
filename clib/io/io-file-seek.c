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
    int result;
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

    result = IO_DISPATCH(fh)->write_pos(fh, pos, whence);
    if (result < 0)
    {
        errno = -result;
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
    long int pos;
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

    pos = IO_DISPATCH(fh)->read_pos(fh);
    if (pos < 0)
    {
        errno = -pos;
        return -1;
    }

    return pos;
}
