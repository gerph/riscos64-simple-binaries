#include <stdio.h>
#include <stdlib.h>
#include "swis.h"
#include "swis-os.h"


#define _IO_MAGIC (0x381F0000)
#define _IO_MAGIC_MASK (0xFFFF0000)
#define CHECK_MAGIC(fh, fail_code) \
                        do { \
                            if ( ((fh)->_flags & _IO_MAGIC_MASK) != _IO_MAGIC ) \
                                return (fail_code); \
                        } while (0)

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
        return NULL;

    _kernel_oserror *err;
    int32_t _fileno;
    err = _swix(OS_Find, _INR(0, 1) | _OUT(0), reason, filename, &_fileno);
    if (err)
    {
        free(fh);
        return NULL;
    }

    fh->_fileno = _fileno;

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
        if (fh->_fileno)
            _swix(OS_Find, _INR(0, 1), 0, fh->_fileno);
        fh->_fileno = 0;
        fh->_flags = -1; /* Clear the magic code */

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
    return -1;
}


int fseek(FILE *fh, long int pos, int whence)
{
    _kernel_oserror *err;
    size_t size = 0;
    if (!fh)
        return -1;

    CHECK_MAGIC(fh, -1);
    switch (whence)
    {
        case SEEK_SET:
            break;

        case SEEK_CUR:
            size_t cur = 0;
            err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 0, fh->_fileno, &cur);
            if (err)
                return -1;
            pos += cur;
            break;

        case SEEK_END:
            size_t ext = 0;
            err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 2, fh->_fileno, &ext);
            if (err)
                return -1;
            pos += ext;
            break;
    }
    _swix(OS_Args, _INR(0, 2), 1, fh->_fileno, pos);
}


long int ftell(FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
        return -1;

    CHECK_MAGIC(fh, -1);

    size_t cur = 0;
    err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 0, fh->_fileno, &cur);
    if (err)
        return -1;

    return cur;
}


int feof(FILE *fh)
{
    int32_t at_eof;
    _kernel_oserror *err;
    if (!fh)
        return -1;

    CHECK_MAGIC(fh, -1);

    err = _swix(OS_Args, _INR(0, 1)|_OUT(2), 5, fh->_fileno, &at_eof);
    if (err)
        return 1; /* Error, so return EOF */
    return at_eof ? 1 : 0;
}


size_t fread(void *ptr, size_t size, size_t nitems, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
        return -1;
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
        return -1;

    return transfer - not_transferred;
}


size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *fh)
{
    _kernel_oserror *err;
    if (!fh)
        return -1;
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
        return -1;

    return transfer - not_transferred;
}

int fgetc(FILE *fh)
{
    int32_t c;
    _kernel_oserror *err;
    if (!fh)
        return -1;
    if (fh == stdin)
        return os_readc();

    CHECK_MAGIC(fh, -1);

    err = _swix(OS_BGet, _IN(0)|_OUT(0), fh->_fileno, &c);
    /* FIXME: Doesn't check for EOF */
    if (err)
        return -1;

    return c;
}

int fflush(FILE *fh)
{
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
        return -1;
    if (fh == stdout || fh == stderr)
    {
        os_writec(c);
        return c;
    }

    CHECK_MAGIC(fh, -1);

    err = _swix(OS_BPut, _INR(0, 1), fh->_fileno, c);
    if (err)
        return -1;

    return c;
}

int putc(int c, FILE *fh)
{
    return fputc(c, fh);
}

char *fgets(char *str, int size, FILE *fh)
{
    char *p;
    if (!fh)
        return NULL;

    CHECK_MAGIC(fh, NULL);

    for (p = str; p - str > 1; p++)
    {
        int c = fgetc(fh);
        if (c == -1)
            return NULL;
        if (c != '\n')
            *p = c;
        else
            break;
    }
    *p = '\0';
    return p;
}
