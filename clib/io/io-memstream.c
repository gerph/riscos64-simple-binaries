/*******************************************************************
 * File:        io-memstream
 * Purpose:     Open a memory stream for writing - this is a POSIX function
 * Author:      Gerph
 * Date:        5 Aug 2025
 ******************************************************************/

#include <stdio.h>

#include "io/io-internal.h"
#include "fs/fs-errors.h"

static _io_dispatch_t __mem_dispatch;

/* Fields within the FILE * structure which we will populate
    * `_IO_write_base` - Start of write buffer
    * `_IO_write_ptr` - Current write pointer
    * `_IO_write_end` - End of write buffer (end of the space)
    * `_IO_read_ptr` - The furthest we have written
    * `_IO_read_base` - Where we'll store base pointer
    * `_IO_read_end` - Where we'll store size used
 */


#define MEM_BASE(fh)    (fh)->_IO_write_base
#define MEM_PTR(fh)     (fh)->_IO_write_ptr
#define MEM_END(fh)     (fh)->_IO_write_end
#define MEM_ENDPTR(fh)  (fh)->_IO_read_ptr

#define MEM_POS(fh)     (MEM_PTR(fh) - MEM_BASE(fh))
#define MEM_EXTENT(fh)  (MEM_ENDPTR(fh) - MEM_BASE(fh))
#define MEM_FREE(fh)    (MEM_ENDPTR(fh) - MEM_PTR(fh) - 1) /* -1 because of the \0 we must store */
#define MEM_BUFSIZE(fh) (MEM_ENDPTR(fh) - MEM_BASE(fh))

#define INITIAL_SIZE    (256)
#define INCREASE_SIZE   (256)

#define UPDATE_POINTERS(fh) \
    do { \
        *(char**)((fh)->_IO_read_base) = _IO_write_base; \
        *(size_t*)((fh)->_IO_read_end) = MEM_EXTENT(fh); \
        *(MEM_PTR(fh)) = '\0'; \
    } while (0)


/*************************************************** Gerph *********
 Function:      __mem_ensure
 Description:   Ensure space in the the buffer for more data
 Parameters:    fh-> the file handle we're writing to
                need = how much space we need
 Returns:       true if reallocated, false if failed
 ******************************************************************/
bool __mem_ensure(FILE *fh, size_t need)
{
    size_t freespace = MEM_FREE(fh);
    char *newbuf;

    if (freespace < need)
        return true;

    /* We don't have enough room in the buffer, so we need to reallocate */
    size_t new_size;
    need += INCREASE_SIZE;
    new_size = MEM_BUFSIZE(fh) + need;

    newbuf = realloc(MEM_BASE(fh), new_size);
    if (newbuf == NULL)
        return false; /* Cannot resize, so leave everything as is */

    /* Resized, so we need to resynchronise pointers */
    {
        size_t pos = MEM_POS(fh);
        size_t extent = MEM_EXTENT(fh);

        MEM_BASE(fh) = newbuf;
        MEM_PTR(fh) = newbuf + pos;
        MEM_ENDPTR(fh) = newbuf + extent;
        MEM_END(fh) = newbuf + new_size;
    }

    /* We need to clear the extra space */
    memset(newbuf + extent, 0, new_size - extent);

    /* Ensure that the user's view of the data has been updated */
    UPDATE_POINTERS(fh);

    return true;
}



static int __mem_close(FILE *fh)
{
    UPDATE_POINTERS(fh);
    /* No memory to free; the user takes ownership */
    return 0;
}


static int __mem_flush(FILE *fh)
{
    UPDATE_POINTERS(fh);
    return 0;
}

static int __mem_check_eof(FILE *fh)
{
    return 0;
}


static int __mem_read_multiple(FILE *fh, void *ptr, size_t transfer)
{
    /* Cannot read from a memstream */
    return -EPERM;
}

static int __mem_read_byte(FILE *fh)
{
    /* Cannot read from a memstream */
    return -EPERM;
}

static int __mem_write_multiple(FILE *fh, const void *ptr, size_t transfer)
{
    /* FIXME: Write some data */
    __mem_ensure(fh, transfer);
    return 0;
}

static int __mem_write_byte(FILE *fh, int c)
{
    return __mem_write_multiple(fh, &c, 1);
}


static long int __mem_write_pos(FILE *fh, long int pos, int whence)
{
    /* FIXME: Update the current position in the memstream */

    return pos;
}


static long int __mem_read_pos(FILE *fh)
{
    /* FIXME: Read the current position in the memstream */
    return cur;
}



static int __mem_read_line(FILE *fh, char *str, size_t size)
{
    /* Cannot read from a memstream */
    return -EPERM;
}


/*************************************************** Gerph *********
 Function:      __mem_setup_dispatch
 Description:   Set up the dispatch table used by the I/O system
 Parameters:    fh-> the file handle
 Returns:       none
 ******************************************************************/
void __mem_setup_dispatch(FILE *fh)
{
    if (__mem_dispatch.close == NULL)
    {
        __mem_dispatch.read_multiple = __mem_read_multiple;
        __mem_dispatch.read_byte = __mem_read_byte;
        __mem_dispatch.read_line = __mem_read_line;
        __mem_dispatch.write_multiple = __mem_write_multiple;
        __mem_dispatch.write_byte = __mem_write_byte;
        __mem_dispatch.close = __mem_close;
        __mem_dispatch.flush = __mem_flush;
        __mem_dispatch.read_pos = __mem_read_pos;
        __mem_dispatch.write_pos = __mem_write_pos;
        __mem_dispatch.check_eof = __mem_check_eof;
    }

    fh->_IO_save_base = (void*)&__mem_dispatch;
}


FILE *open_memstream(char **bufp, size_t *sizep)
{
    FILE *fh = calloc(1, sizeof(*fh));
    char *buf;
    if (fh == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    buf = calloc( 1, INITIAL_SIZE );
    if (buf == NULL)
    {
        errno = ENOMEM;
        free(fh);
        return NULL;
    }
    MEM_BASE(fh) = buf;
    MEM_PTR(fh) = buf;
    MEM_ENDPTR(fh) = buf;
    MEM_END(fh) = buf + INITIAL_SIZE;

    /* Where we'll update the pointers */
    fh->_IO_read_base = (char *)bufp;
    fh->_IO_read_end = (char *)sizep;

    __mem_setup_dispatch(fh);

    /* Link to chain */
    fh->_chain = __file_list;
    __file_list = fh;

    return fh;
}
