#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "io/io-consoleio.h"
#include "fs/fs-errors.h"
#include "fs/fs-io.h"
#include "io/io-file-fopen.h"
#include <errno.h>

extern FILE *__file_list;


/*************************************************** Gerph *********
 Function:      _fopen
 Description:   Internal file open function
 Parameters:    filename-> the file to open
                mode = the file mode to use
                fh-> the file handle we're opening into (which has been cleared)
 Returns:       true on success, false on failure
 ******************************************************************/
bool _fopen(const char *filename, const char *mode, FILE *fh)
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

    _kernel_oserror *err;
    int32_t _fileno;
    err = _swix(OS_Find, _INR(0, 1) | _OUT(0), reason, filename, &_fileno);
    if (err)
    {
        __fs_seterrno(err);
        return false;
    }

    fh->_fileno = _fileno;

    fh->_flags = _IO_MAGIC; /* Mark as valid */

    if (reason & 0x80)
        fh->_flags |= _IO_WRITABLE;
    if (reason & 0x40)
        fh->_flags |= _IO_READABLE;

    __fs_setup_dispatch(fh);

    return true;
}

/*************************************************** Gerph *********
 Function:      _fclose
 Description:   Internal close for the file, which does not unlink.
                The file is closed / reset to its original state.
 Parameters:    fh-> the file handle to close
 Returns:       none
 ******************************************************************/
void _fclose(FILE *fh)
{
    if (fh->_fileno)
    {
        IO_DISPATCH(fh)->close(fh);
    }
    if (fh == stdin)
    {
        /* Reset the FILE for stdin */
        fh->_flags = _IO_MAGIC | _IO_READABLE | _IO_CONSOLE;
        fh->_fileno = IO_FD_CONSOLE;

        /* Reset console dispatcher */
        __con_setup_dispatch(fh);
    }
    else if (fh == stdout || fh == stderr)
    {
        /* Reset the FILE for stdout/stderr */
        fh->_flags = _IO_MAGIC | _IO_WRITABLE | _IO_CONSOLE;
        fh->_fileno = IO_FD_CONSOLE;

        /* Reset console dispatcher */
        __con_setup_dispatch(fh);
    }
    else
    {
        fh->_flags = -1; /* Clear the magic code */
    }
}

FILE *fopen(const char *filename, const char *mode)
{
    FILE *fh = calloc(1, sizeof(*fh));
    if (fh == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    if (!_fopen(filename, mode, fh))
    {
        free(fh);
        return NULL;
    }

    /* Link to chain */
    fh->_chain = __file_list;
    __file_list = fh;

    return fh;
}


int fclose(FILE *fh)
{
    if (fh)
    {
        CHECK_MAGIC(fh, -1);
        _fclose(fh);

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
