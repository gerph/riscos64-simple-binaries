#include <stdio.h>
#include <stdlib.h>
#include "swis.h"
#include "swis-os.h"


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
    return fh;
}


int fclose(FILE *fh)
{
    if (fh)
    {
        if (fh->_fileno)
            _swix(OS_Find, _INR(0, 1), 0, fh->_fileno);
        fh->_fileno = 0;
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

    err = _swix(OS_BGet, _IN(0)|_OUT(0), fh->_fileno, &c);
    /* FIXME: Doesn't check for EOF */
    if (err)
        return -1;

    return c;
}

int fflush(FILE *fh)
{
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

    err = _swix(OS_BPut, _INR(0, 1), fh->_fileno, c);
    if (err)
        return -1;

    return c;
}

char *fgets(char *str, int size, FILE *fh)
{
    char *p;
    if (!fh)
        return NULL;

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
