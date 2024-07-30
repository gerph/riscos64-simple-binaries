#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "swis.h"

void memcpy(char *dst, const char *src, int size)
{
    while (size--)
        *dst++ = *src++;
}


void memmove(char *dst, const char *src, int size)
{
    if (src > dst)
    {
        while (size--)
            *dst++ = *src++;
    }
    else
    {
        dst += size;
        src += size;

        while (size--)
            *--dst = *--src;

    }
}


void memset(char *dst, int c, int size)
{
    while (size--)
        *dst++ = c;
}


char *strcpy(char *dst, const char *src)
{
    char *odst = dst;
    while (1)
    {
        int c = *src++;
        *dst++ = c;
        if (!c)
            break;
    }
    return odst;
}


int strcmp(const char *a, const char *b)
{
    while (1)
    {
        int ac = *a++;
        int bc = *b++;
        if (ac != bc)
        {
            return ac - bc;
        }
        if (ac == 0)
            return 0;
    }
}


int strncmp(const char *a, const char *b, size_t n)
{
    while (n-->0)
    {
        int ac = *a++;
        int bc = *b++;
        if (ac != bc)
        {
            return ac - bc;
        }
        if (ac == 0)
            break;
    }
    return 0;
}


int memcmp(const char *a, const char *b, size_t n)
{
    while (n-->0)
    {
        int ac = *a++;
        int bc = *b++;
        if (ac != bc)
        {
            return ac - bc;
        }
    }
    return 0;
}


char *strncpy(char *dst, const char *src, size_t n)
{
    char *odst = dst;
    while (n-->0)
    {
        int c = *src++;
        *dst++ = c;
        if (!c)
            break;
    }
    return odst;
}


size_t strlen(const char *s)
{
    const char *os = s;
    while (*s++ != '\0')
        ;
    return s - os - 1;
}


const char *strchr(const char *s, char want)
{
    while (*s != want)
    {
        if (*s == '\0')
            return NULL;
        s++;
    }
    return s;
}


const char *memchr(const char *s, char want, size_t n)
{
    for (; n>0 && *s != want; s++, n--)
        ;
    if (n <= 0)
        return NULL;
    return s;
}

const char *strstr(const char *a, const char *b)
{
    int blen = strlen(b);
    int alen = strlen(a);
    char bc = *b;
    int offset;
    for (offset=0; offset <= alen - blen; offset++)
    {
        if (a[offset] == bc)
        {
            /* This could be the string, try it */
            int diff = strncmp(&a[offset], b, blen);
            if (!diff)
                return &a[offset];
        }
    }
    return NULL;
}


int clock(void)
{
    _kernel_swi_regs regs;
    _kernel_swi(OS_ReadMonotonicTime, NULL, &regs);
    return regs.r[0];
}


int getchar(void)
{
    return os_readc();
}


void __assert_fail(const char *message)
{
    static _kernel_oserror err = {0, "Assertion failed"};
    os_write0("Assertion failed: ");
    os_write0(message);
    os_newline();
    os_generateerror(&err);
}


typedef struct outputter_s {
    int (*write0)(struct outputter_s *out, const char *str);
    int (*writec)(struct outputter_s *out, char c);
    int (*writen)(struct outputter_s *out, const char *str, size_t len);
    int (*newline)(struct outputter_s *out);
    void *private;
} outputter_t;

typedef struct formatparams_s {
    int leading_char;
    int align_left;
    int field_width;
    int precision;
    int param_width;
} formatparams_t;

static int stdout_write0(outputter_t *out, const char *str)
{
    os_write0(str);
    return strlen(str);
}

static int stdout_writen(outputter_t *out, const char *str, size_t len)
{
    os_writen(str, len);
    return len;
}

static int stdout_writec(outputter_t *out, char c)
{
    os_writec(c);
    return 1;
}

static int stdout_newline(outputter_t *out)
{
    os_newline();
    return 1;
}

static int file_write0(outputter_t *out, const char *str)
{
    FILE *f = (FILE *)out->private;
    int len = strlen(str);
    int wrote;
    wrote = fwrite(str, 1, len, f);
    return wrote;
}

static int file_writen(outputter_t *out, const char *str, size_t len)
{
    FILE *f = (FILE *)out->private;
    int wrote;
    wrote = fwrite(str, 1, len, f);
    return wrote;
}

static int file_writec(outputter_t *out, char c)
{
    FILE *f = (FILE *)out->private;
    int wrote;
    wrote = fputc(c, f);
    return wrote == EOF ? 0 : 1;
}

static int file_newline(outputter_t *out)
{
    return file_writec(out, 10);
}


int _vprintf(outputter_t *out, const char *format, va_list args)
{
    const char *next_nl = strchr(format, '\n');
    int n = 0;

    while (*format)
    {
        formatparams_t params = {0};
        char c;
        const char *next_percent = strchr(format, '%');
        if (next_percent == NULL && next_nl == NULL)
        {
            /* No more characters left, so we output the remaining string */
            n += out->write0(out, format);
            break;
        }
        while (format < next_percent || next_nl)
        {
            int len = next_percent - format;
            if ((next_percent && next_nl && next_nl < next_percent) ||
                (next_nl && !next_percent))
            {
                len = next_nl - format;
                n += out->writen(out, format, len);
                n += out->newline(out);
                format = next_nl + 1;
                next_nl = strchr(format, '\n');
            }
            else
            {
                n += out->writen(out, format, len);
                format += len;
                break;
            }
        }
        /* Skip the percent */
        if (next_percent)
            format ++;
        else
            break;

        c = *format++;

        /* Parse the field parameters */
        if (c=='-')
        {
            params.align_left = 1;
            c = *format++;
        }
        if (c==' ' || c=='0')
        {
            params.leading_char = c;
            c = *format++;
        }
        if (c>='1' && c<='9')
        {
            /* Field width */
            params.field_width = c - '0';
            c = *format++;
            while (c>='1' && c<='9')
            {
                params.field_width = (params.field_width * 10) + c - '0';
                c = *format++;
            }
        }
        if (c=='.')
        {
            c = *format++;
            if (c == '*')
            {
                params.precision = va_arg(args, uint32_t);
                c = *format++;
            }
            else
            {
                if (c>='1' && c<='9')
                {
                    /* precision */
                    params.precision = c - '0';
                    c = *format++;
                    while (c>='1' && c<='9')
                    {
                        params.precision = (params.precision * 10) + c - '0';
                        c = *format++;
                    }
                }
            }

        }
        if (c=='l')
        {
            params.param_width = c;
            c = *format++;
        }

        switch (c)
        {
            case '%':
                n += out->writec(out, '%');
                break;

            case '\0':
                n += out->writec(out, '%');
                format--;
                continue;

            case 's':
                {
                    const char *s = va_arg(args, const char *);
                    if (params.precision != 0)
                    {
                        /* Maximum of precision characters */
                        while (params.precision-- > 0)
                        {
                            char c = *s++;
                            if (c)
                                out->writec(out, c);
                            else
                                break;
                        }
                    }
                    else
                    {
                        n += strlen(s);
                        out->write0(out, s);
                    }
                }
                break;

            case 'p':
                n += out->write0(out, "0x");

            case 'x':
                {
                    char hex[16]; /* FIXME: Should be width for arch */
                    int start = -1;
                    uint32_t value = va_arg(args, uint32_t);
                    int i;
                    for (i=sizeof(hex)-1; i>-1; i--) /* FIXME: widen */
                    {
                        int v = value & 15;
                        hex[i] = "0123456789ABCDEF"[v];
                        value = value >> 4;
                        if (start == -1 && value == 0)
                        {
                            start = i;
                            break;
                        }
                    }
                    if (start == -1)
                        start = 0;
                    n += out->writen(out, &hex[start], sizeof(hex)-start);
                }
                break;

            case 'i':
            case 'd':
            case 'u':
                {
                    char intstr[21];
                    static uint64_t ints[] = {
                            1,
                            10,
                            100,
                            1000,
                            10000,
                            100000,
                            1000000,
                            10000000,
                            100000000,
                            1000000000,
                            10000000000,
                            100000000000,
                            1000000000000,
                            10000000000000,
                            100000000000000,
                            1000000000000000,
                            10000000000000000,
                            100000000000000000,
                            1000000000000000000,
                            10000000000000000000,
                        };
                    char *p = intstr;
                    int size = 18;
                    uint64_t value;
                    if (c == 'u')
                    {
                        value = va_arg(args, uint64_t);
                    }
                    else
                    {
                        int32_t uvalue = va_arg(args, int64_t);
                        if (uvalue < 0)
                        {
                            uvalue = 0 - uvalue;
                            *p++ = '-';
                        }
                        value = uvalue;
                    }
                    if (value < 10000000000)
                        size = 11;
                    int first = 1;
                    while (size >= 0)
                    {
                        int64_t m = ints[size];
                        if (value >= m)
                        {
                            first = 0;
                            int digit = 1;
                            value -= m;
                            while (value >= m)
                                digit += 1, value -= m;
                            *p++ = '0' + digit;
                        }
                        else
                        {
                            if (!first)
                                *p++ = '0';
                        }
                        size -= 1;
                    }
                    /* Special case 0 */
                    if (p == intstr)
                        *p++ = '0';

                    n += out->writen(out, intstr, p - intstr);
                }
                break;

            default:
                n += out->writec(out, '%');
                n += out->writec(out, c);
                break;
        }
    }

    return n;
}

int vprintf(const char *format, va_list args)
{
    int n;
    outputter_t out;
    out.write0 = stdout_write0;
    out.writen = stdout_writen;
    out.writec = stdout_writec;
    out.newline = stdout_newline;
    n = _vprintf(&out, format, args);
    return n;
}

int printf(const char *format, ...)
{
    int n;
    va_list args;
    va_start(args, format);

    n = vprintf(format, args);

    va_end(args);
    return n;
}

int vfprintf(FILE *f, const char *format, va_list args)
{
    int n;
    outputter_t out;
    out.write0 = file_write0;
    out.writen = file_writen;
    out.writec = file_writec;
    out.newline = file_newline;
    out.private = (void*)f;
    n = _vprintf(&out, format, args);
    return n;
}

int fprintf(FILE *f, const char *format, ...)
{
    int n;
    va_list args;
    va_start(args, format);

    if (f==stdout || f==stderr)
        n = vprintf(format, args);
    else
        n = vfprintf(f, format, args);

    va_end(args);
    return n;
}

typedef struct outputterstr_t {
    outputter_t out;
    char *start;
    char *p;
    int size;
} outputterstr_t;

static int str_writen(outputter_t *out, const char *str, size_t len)
{
    outputterstr_t *outs = (outputterstr_t *)out;
    //printf("str_writen : writing %p to %p\n", str, outs->p);
    if (outs->p + len + 1 - outs->start > outs->size)
    {
        /* This would exceed the buffer size */
        if (outs->p > outs->start + outs->size)
        {
            /* It's wholey outside the buffer */
            outs->p += len;
        }
        else
        {
            /* Partially fills the buffer */
            int space = outs->p + len + 1 - outs->start;
            memcpy(outs->p, str, space);
            outs->p[space] = '\0';
            outs->p += len;
        }
    }
    else
    {
        memcpy(outs->p, str, len);
        outs->p += len;
        *outs->p = '\0';
    }
    return len;
}

static int str_write0(outputter_t *out, const char *str)
{
    outputterstr_t *outs = (outputterstr_t *)out;
    int len = strlen(str);
    int wrote;
    wrote = str_writen(out, str, len);
    return wrote;
}

static int str_writec(outputter_t *out, char c)
{
    outputterstr_t *outs = (outputterstr_t *)out;
    if (outs->p + 1 + 1 - outs->start > outs->size)
    {
        /* This would exceed the buffer size */
        outs->p++;
    }
    else
    {
        *outs->p++ = c;
        *outs->p = '\0';
    }
    return 1;
}

static int str_newline(outputter_t *out)
{
    return str_writec(out, 10);
}

int vsprintf(char *str, const char *format, va_list args)
{
    int n;
    outputterstr_t out;
    out.out.write0 = str_write0;
    out.out.writen = str_writen;
    out.out.writec = str_writec;
    out.out.newline = str_newline;
    out.start = str;
    out.p = str;
    out.size = (str == NULL) ? 0 : 0x7FFFFFFF;
    //printf("sprintf(%x, '%s', ...)\n", out.start, format);
    n = _vprintf((outputter_t*)&out, format, args);
    return n;
}

int sprintf(char *str, const char *format, ...)
{
    int n;
    va_list args;
    va_start(args, format);

    n = vsprintf(str, format, args);

    va_end(args);
    return n;
}

FILE *stdin = (FILE*)1;
FILE *stdout = (FILE*)2;
FILE *stderr = (FILE*)3;


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

void qsort(void *base, size_t nelements, size_t width,
           int (*compar)(const void *, const void *))
{
    /* FIXME: Not implemented */
    return;
}

static unsigned short __ctype_b[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
    0x0002, 0x2003, 0x2002, 0x2002, 0x2002, 0x2002, 0x0002, 0x0002,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
    0x6001, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004,
    0xc004, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004,
    0xd808, 0xd808, 0xd808, 0xd808, 0xd808, 0xd808, 0xd808, 0xd808,
    0xd808, 0xd808, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004,
    0xc004, 0xd508, 0xd508, 0xd508, 0xd508, 0xd508, 0xd508, 0xc508,
    0xc508, 0xc508, 0xc508, 0xc508, 0xc508, 0xc508, 0xc508, 0xc508,
    0xc508, 0xc508, 0xc508, 0xc508, 0xc508, 0xc508, 0xc508, 0xc508,
    0xc508, 0xc508, 0xc508, 0xc004, 0xc004, 0xc004, 0xc004, 0xc004,
    0xc004, 0xd608, 0xd608, 0xd608, 0xd608, 0xd608, 0xd608, 0xc608,
    0xc608, 0xc608, 0xc608, 0xc608, 0xc608, 0xc608, 0xc608, 0xc608,
    0xc608, 0xc608, 0xc608, 0xc608, 0xc608, 0xc608, 0xc608, 0xc608,
    0xc608, 0xc608, 0xc608, 0xc004, 0xc004, 0xc004, 0xc004, 0x0002,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
static unsigned short *__ctype_b_ptr;

unsigned short **__ctype_b_loc(void)
{
    __ctype_b_ptr = &__ctype_b[128];
    return &__ctype_b_ptr;
}


typedef void (*atexit_func_t)(void);

#define ATEXIT_MAX (32)

static atexit_func_t atexit_funcs[ATEXIT_MAX];

int atexit(atexit_func_t func)
{
    int i;
    for (i=0; i<ATEXIT_MAX; i++)
    {
        if (atexit_funcs[i] == NULL)
        {
            atexit_funcs[i] = func;
            return 0;
        }
    }

    /* All slots filled */
    return -1;
}

void exit(int rc)
{
    atexit_func_t *funcsp = atexit_funcs;
    int i;

    /* Call the registered functions in reverse order */
    for (i=ATEXIT_MAX - 1; i>=0; i--)
    {
        if (atexit_funcs[i] != NULL)
        {
            atexit_func_t func = atexit_funcs[i];
            atexit_funcs[i] = NULL;
            func();
        }
    }

    _exit(rc);
}
