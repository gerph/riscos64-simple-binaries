#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "fs/fs-errors.h"
#include <errno.h>


size_t fread(void *ptr, size_t size, size_t nitems, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
        return 0;

    CHECK_MAGIC(fh, -1);

    if (!IO_IS_READABLE(fh))
    {
        return 0;
    }

    if (IO_IS_KEYBOARD(fh))
    {
        if (size == 1 && nitems == 1)
        {
            char *p = (char*)ptr;
            *p = fgetc(fh);
            return 1;
        }

        return -1;
    }

    size_t transfer = size * nitems;
    size_t not_transferred = 0;
    size_t totransfer = transfer;

    if (transfer == 0)
        return 0; /* Nothing to do?! */

    if (fh->_flags & _IO_CHARPUSHED)
    {
        uint8_t *data = (uint8_t *)ptr;
        *data++ = fh->_shortbuf[0];
        /* Unmark as any character pushed back */
        fh->_flags &= ~ _IO_CHARPUSHED;
        totransfer -= 1;
        ptr = (void*)data;
    }

    if (totransfer != 0)
    {
        err = _swix(OS_GBPB, _INR(0, 3)|_OUT(3), 4, fh->_fileno, ptr, totransfer, &not_transferred);
        if (err)
        {
            /* FIXME: Set errno? */
            return 0;
        }
    }

    if (not_transferred == 0)
        return nitems;

    if (size == 1)
        return transfer - not_transferred;

    /* They requested a size that wasn't the whole, so we need to move back */
    {
        size_t transferred = (transfer - not_transferred);
        nitems = transferred / nitems;
        size_t excess = transferred % nitems;
        if (excess)
        {
            /* Move back the amount we didn't read */
            fseek(fh, -excess, SEEK_CUR);
        }

        return nitems;
    }
}

int fgetc(FILE *fh)
{
    int32_t c;
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (!IO_IS_READABLE(fh))
    {
        return 0;
    }

    if (IO_IS_KEYBOARD(fh))
        return os_readc();

    if (fh->_flags & _IO_CHARPUSHED)
    {
        c = fh->_shortbuf[0];
        /* Unmark as any character pushed back */
        fh->_flags &= ~ _IO_CHARPUSHED;
        return c;
    }

    err = _swix(OS_BGet, _IN(1)|_OUT(0), fh->_fileno, &c);
    /* FIXME: Doesn't check for EOF */
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }

    return c;
}


int getc(FILE *fh)
{
    return fgetc(fh);
}

int ungetc(int c, FILE *fh)
{
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    CHECK_MAGIC(fh, -1);

    if (!IO_IS_READABLE(fh))
    {
        return 0;
    }

    if (fh->_flags & _IO_CHARPUSHED)
        return EOF; /* Already pushed so cannot push more */
    if (c == EOF)
        return EOF; /* No push if they tried pushing EOF */
    fh->_flags |= _IO_CHARPUSHED;
    fh->_shortbuf[0] = c;
    return c;
}
