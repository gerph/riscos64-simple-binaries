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

    FILE *fh = malloc(sizeof(*fh));
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

    return fh;
}


int fclose(FILE *fh)
{
    if (fh)
    {
        CHECK_MAGIC(fh, -1);
        if (fh->_fileno)
            _swix(OS_Find, _INR(0, 1), 0, fh->_fileno);
        fh->_flags = -1; /* Clear the magic code */
        fh->_fileno = 0;

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
    return pos;
}


long int ftell(FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }
    if (fh == stdin || fh == stdout || fh == stderr)
        return -1;

    CHECK_MAGIC(fh, -1);

    size_t cur = 0;
    err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 0, fh->_fileno, &cur);
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }

    return cur;
}


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

    err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 5, fh->_fileno, &at_eof);
    if (err)
    {
        __fs_seterrno(err);
        return 1; /* Error, so return EOF */
    }
    return at_eof ? 1 : 0;
}


size_t fread(void *ptr, size_t size, size_t nitems, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
        return 0;
    if (fh == stdin)
    {
        if (size == 1 && nitems == 1)
        {
            char *p = (char*)ptr;
            *p = fgetc(fh);
            return 1;
        }

        return -1;
    }

    CHECK_MAGIC(fh, -1);

    size_t transfer = size * nitems;
    size_t not_transferred = 0;
    err = _swix(OS_GBPB, _INR(0, 3)|_OUT(3), 4, fh->_fileno, ptr, transfer, &not_transferred);
    if (err)
        return 0;

    return transfer - not_transferred;
}


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
    if (fh == stdout || fh == stderr)
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

    CHECK_MAGIC(fh, -1);

    size_t transfer = size * nitems;
    size_t not_transferred = 0;
    err = _swix(OS_GBPB, _INR(0, 3)|_OUT(3), 2, fh->_fileno, ptr, transfer, &not_transferred);
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }

    return transfer - not_transferred;
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
    if (fh == stdin)
        return os_readc();

    CHECK_MAGIC(fh, -1);

    err = _swix(OS_BGet, _IN(1)|_OUT(0), fh->_fileno, &c);
    /* FIXME: Doesn't check for EOF */
    if (err)
    {
        __fs_seterrno(err);
        return -1;
    }

    return c;
}

int fflush(FILE *fh)
{
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }
    if (fh == stdin || fh == stdout || fh == stderr)
        return 0;

    CHECK_MAGIC(fh, -1);

    /* FIXME: Could call the flush OS_Args call */
    return 0;
}


int getc(FILE *fh)
{
    return fgetc(fh);
}

int fputc(int c, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }
    if (fh == stdout || fh == stderr)
    {
        if (c == '\n')
            os_newline();
        else
            os_writec(c);
        return c;
    }

    CHECK_MAGIC(fh, -1);

    err = _swix(OS_BPut, _INR(0, 1), c, fh->_fileno);
    if (err)
    {
        __fs_seterrno(err);
        return -1;
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

    int len = strlen(str ? str : "<NULL>");

    return fwrite(str, 1, len, fh);
}

int fileno(FILE *fh)
{
    if (!fh)
    {
        errno = EBADF;
        return -1;
    }

    if (fh == stdin || fh == stdout || fh == stderr)
        return -2;

    // CHECK_MAGIC(fh, -1);

    return fh->_fileno;
}

int isatty(int fd)
{
    if (fd == -2)
        return 1;
    return 0;
}
