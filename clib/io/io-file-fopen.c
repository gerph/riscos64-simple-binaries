#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "fs/fs-errors.h"
#include <errno.h>

extern FILE *__file_list;


FILE *fopen(const char *filename, const char *mode)
{
    int reason = 0x00;
    for (char c = *mode++; c; c = *mode++)
    {
        if (c == 'r')
            reason |= 0x40;
        if (c == 'w')
        {
            if (reason == 0x40)
                reason = 0;
            reason |= 0x80;
        }
        if (c == '+')
            reason |= 0xC0;
    }

    reason |= (1<<2) | (1<<3); /* Error if not a file */

    FILE *fh = calloc(1, sizeof(*fh));
    if (fh == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }

    _kernel_oserror *err;
    int32_t _fileno;
    err = _swix(OS_Find, _INR(0, 1) | _OUT(0), reason, filename, &_fileno);
    if (err)
    {
        __fs_seterrno(err);

        free(fh);
        return NULL;
    }

    fh->_fileno = _fileno;

    /* Link to chain */
    fh->_chain = __file_list;
    __file_list = fh;

    fh->_flags = _IO_MAGIC; /* Mark as valid */

    if (reason & 0x80)
        fh->_flags |= _IO_WRITABLE;
    if (reason & 0x40)
        fh->_flags |= _IO_READABLE;

    return fh;
}


int fclose(FILE *fh)
{
    if (fh)
    {
        CHECK_MAGIC(fh, -1);
        if (fh->_fileno)
        {
            _kernel_osfind(0, (const char *)fh->_fileno); /* Close file */
            fh->_fileno = 0;
            if (fh->_flags & _IO_DELETEONCLOSE)
            {
                /* Delete the file */
                if (fh->_markers)
                {
                    _kernel_osfile(6, fh->_markers->filename, NULL);
                    free(fh->_markers);
                    fh->_markers = NULL;
                }
            }
        }
        if (fh == stdin)
        {
            /* Reset the FILE for stdin */
            fh->_flags = _IO_MAGIC | _IO_READABLE | _IO_CONSOLE;
            return 0;
        }
        else if (fh == stdout || fh == stderr)
        {
            /* Reset the FILE for stdout/stderr */
            fh->_flags = _IO_MAGIC | _IO_WRITABLE | _IO_CONSOLE;
            return 0;
        }
        else
        {
            fh->_flags = -1; /* Clear the magic code */
        }

        /* Unlink from chain */
        FILE **lastp = &__file_list;
        FILE *cur;
        for (cur=__file_list; cur; cur=cur->_chain)
        {
            if (cur == fh)
            {
                /* This is the entry to unlink */
                *lastp = cur->_chain;
                free(fh);
                break;
            }
            lastp = &cur->_chain;
        }
        return 0;
    }
    errno = EBADF;
    return -1;
}
