/*******************************************************************
 * File:        io-consoleio
 * Purpose:     Console I/O dispatchers
 * Author:      Gerph
 * Date:        4 Aug 2025
 ******************************************************************/

#include <string.h>
#include <stdlib.h>

#include "kernel.h"
#include "swis.h"
#include "swis_os.h"

#include "io/io-internal.h"

static _io_dispatch_t __con_dispatch;


static int __con_close(FILE *fh)
{
    /* Nothing to do */
    return 0;
}


static int __con_flush(FILE *fh)
{
    /* Nothing to do */
    return 0;
}

static int __con_check_eof(FILE *fh)
{
    if (IO_IS_SCREEN(fh))
        return 0;
    if (IO_IS_KEYBOARD(fh))
    {
        /* FIXME: Should check for input and if so look for ctrl-d or something ? */
        return 0;
    }

    return 0;
}


static int __con_read_multiple(FILE *fh, void *ptr, size_t transfer)
{
    /* FIXME: Currently you cannot read multiple input */
    return 0;
}

static int __con_read_byte(FILE *fh)
{
    /* Will never be called for output */
    /* FIXME: Should return failure if we had EOF? */
    return os_readc();
}

static int __con_write_multiple(FILE *fh, const void *ptr, size_t transfer)
{
    _kernel_oserror *err;
    int wrote = 0;
    while (transfer)
    {
        const char *next_nl = memchr(ptr, '\n', transfer);
        if (next_nl == NULL)
        {
            err = os_writen(ptr, transfer);
            if (err)
                break;
            wrote += transfer;
            break;
        }
        int to_nl = (next_nl - (const char *)ptr);
        if (to_nl)
        {
            err = os_writen(ptr, to_nl);
            if (err)
                break;
            wrote += to_nl;
        }
        err = os_newline();
        if (err)
            break;
        wrote += 1;
        transfer -= to_nl + 1;
        ptr = ((const char *)ptr) + to_nl + 1;
    }
    return wrote;
}

static int __con_write_byte(FILE *fh, int c)
{
    /* Will never be called for input */
    if (c == '\n')
        os_newline();
    else
        os_writec(c);
    return c;
}


static long int __con_write_pos(FILE *fh, long int pos, int whence)
{
    return -EIO;
}


static long int __con_read_pos(FILE *fh)
{
    return 0;
}


/*************************************************** Gerph *********
 Function:      __con_setup_dispatch
 Description:   Set up the dispatch table used by the I/O system
 Parameters:    fh-> the file handle
 Returns:       none
 ******************************************************************/
void __con_setup_dispatch(FILE *fh)
{
    if (__con_dispatch.close == NULL)
    {
        __con_dispatch.read_multiple = __con_read_multiple;
        __con_dispatch.read_byte = __con_read_byte;
        __con_dispatch.write_multiple = __con_write_multiple;
        __con_dispatch.write_byte = __con_write_byte;
        __con_dispatch.close = __con_close;
        __con_dispatch.flush = __con_flush;
        __con_dispatch.read_pos = __con_read_pos;
        __con_dispatch.write_pos = __con_write_pos;
        __con_dispatch.check_eof = __con_check_eof;
    }

    fh->_IO_save_base = (void*)&__con_dispatch;
}
