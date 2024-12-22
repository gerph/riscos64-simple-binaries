#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "io-vprintf.h"
#include "conversion/cvt.h"

/* Define this if printing a '0' just gives zero, with no prefix 0x or 0, etc */
#define ZERO_IS_JUST_ZERO

#ifndef NO_FP
#include "gdtoa.h"
#endif

typedef struct formatparams_s {
    int alternate;
    int sign;
    int digit_pad;
    int align_left;
    int field_width;
    int precision;
    int param_width;
} formatparams_t;

static int count_pad_digits(formatparams_t *params, int size, char *prefix)
{
    int n = 0;
    if (prefix)
        n = strlen(prefix);
    if (params->digit_pad)
    {
        int pad = (params->precision > 0 ? params->precision : (params->align_left ? size : (params->field_width - n))) - size;
        if (pad > 0)
            n += pad;
    }
    return n;
}

static int pad_digits(outputter_t *out, formatparams_t *params, int size, char *prefix)
{
    int n = 0;
    if (prefix)
        n = out->write0(out, prefix);

    if (params->digit_pad)
    {
        int pad = (params->precision > 0 ? params->precision : (params->align_left ? size : (params->field_width - n))) - size;
        if (pad > 0)
        {
            char shortbuf[8];
            memset(shortbuf, params->digit_pad, sizeof(shortbuf));
            while (pad > 0)
            {
                n += out->writen(out, shortbuf, pad > sizeof(shortbuf) ? sizeof(shortbuf) : pad);
                pad -= sizeof(shortbuf);
            }
        }
    }
    return n;
}

static int pad_output(outputter_t *out, formatparams_t *params, int size)
{
    /* They wanted this laid out into a field */
    int pad = params->field_width - size;
    int n = 0;
    while (pad > 0)
    {
        n += out->writen(out, "        ", pad > 8 ? 8 : pad);
        pad -= 8;
    }
    return n;
}

static int write_with_newlines(outputter_t *out, const char *s, int size)
{
    int n = 0;
    while (size > 0 && *s)
    {
        const char *nextnl = memchr(s, '\n', size);
        if (nextnl != NULL)
        {
            int write = nextnl - s;
            n += out->writen(out, s, write);
            size -= write + 1;
            s += write + 1;
            n += out->newline(out);
        }
        else
        {
            n += out->writen(out, s, size);
            break;
        }
    }
    return n;
}

int _vprintf(outputter_t *out, const char *format, va_list args)
{
    const char *next_nl = strchr(format, '\n');
    int n = 0;

    while (*format)
    {
        formatparams_t params = {0};
        params.precision = -1;
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
        while (1)
        {
            if (c=='-')
            {
                params.align_left = 1;
                c = *format++;
            }
            else if (c=='+' || c==' ')
            {
                if (params.sign != '+')
                    params.sign = c;    /* '+' takes precedence */
                c = *format++;
            }
            else if (c=='#')
            {
                params.alternate = 1;
                c = *format++;
            }
            else if (c=='0')
            {
                params.digit_pad = c;
                c = *format++;
            }
            else
            {
                break;
            }
        }
        if (c>='1' && c<='9')
        {
            /* Field width */
            params.field_width = c - '0';
            c = *format++;
            while (c>='0' && c<='9')
            {
                params.field_width = (params.field_width * 10) + c - '0';
                c = *format++;
            }
        }
        else if (c == '*')
        {
            /* Field width from the arguments */
            params.field_width = va_arg(args, uint32_t);
            if (params.field_width < 0)
            {
                params.align_left = 1;
                params.field_width = -params.field_width;
            }
            c = *format++;
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
                if (c>='0' && c<='9')
                {
                    /* precision */
                    params.precision = c - '0';
                    c = *format++;
                    while (c>='0' && c<='9')
                    {
                        params.precision = (params.precision * 10) + c - '0';
                        c = *format++;
                    }
                }
            }

        }
        if (c=='h')
        {
            params.param_width = c; /* Half word */
            c = *format++;
            if (c=='h')
            {
                /* byte */
                params.param_width = 'b';
                c = *format++;
            }
        }
        else if (c=='l')
        {
            params.param_width = c;
            c = *format++;
            if (c=='l')
            {
                /* Long-long */
                params.param_width = 'L';
                c = *format++;
            }
        }
        else if (c=='z' || c=='j' || c=='t')
        {
            params.param_width = 'L'; /* size_t/intmax_t/ptrdiff_t is 64bit */
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

            case 'c':
                {
                    unsigned char c = va_arg(args, uint64_t) & 0xFF;

                    if (params.align_left)
                        n += out->writec(out, c);

                    if (params.field_width)
                        n += pad_output(out, &params, 1);

                    if (!params.align_left)
                        n += out->writec(out, c);
                }
                break;

            case 's':
                {
                    const char *s = va_arg(args, const char *);
                    int size;
                    bool has_newline = false;
                    if (s==NULL)
                        s = "<NULL>";
                    if (params.precision > 0)
                    {
                        for (size = 0; size < params.precision ; size++)
                        {
                            char sc = s[size];
                            if (sc == '\n')
                                has_newline = true;
                            if (sc == '\0')
                                break;
                        }
                    }
                    else
                    {
                        has_newline = strchr(s, '\n');
                        size = strlen(s);
                    }

                    if (params.align_left)
                    {
                        if (has_newline)
                            n += write_with_newlines(out, s, size);
                        else
                            n += out->writen(out, s, size);
                    }

                    if (params.field_width)
                        n += pad_output(out, &params, size);

                    if (!params.align_left)
                    {
                        if (has_newline)
                            n += write_with_newlines(out, s, size);
                        else
                            n += out->writen(out, s, size);
                    }
                }
                break;

            case 'p':
            case 'x':
            case 'X':
            case 'i':
            case 'd':
            case 'u':
            case 'o':
                {
                    char buf[32];
                    char *p = buf;
                    int sign = 0;
                    bool hex = (c=='p' || c=='x' || c=='X');
                    uint64_t value;
                    char signbuf[2] = " ";
                    char *prefix = NULL;
                    if (params.precision > 0 && !params.digit_pad)
                        params.digit_pad = '0';
                    if (c == 'u' || hex || c == 'o')
                    {
                        if (params.param_width == 'b')
                            value = va_arg(args, uint64_t) & 0xFF;
                        else if (params.param_width == 'h')
                            value = va_arg(args, uint64_t) & 0xFFFF;
                        else if (params.param_width == 'l')
                            value = va_arg(args, uint64_t) & 0xFFFFFFFF;
                        else
                            value = va_arg(args, uint64_t);
                    }
                    else
                    {
                        int64_t svalue;
                        if (params.param_width == 'b')
                        {
                            svalue = va_arg(args, int64_t) & 0xFF;
                            if (svalue & 0x80)
                                svalue = svalue - 0x100;
                        }
                        else if (params.param_width == 'h')
                        {
                            svalue = va_arg(args, int64_t) & 0xFFFF;
                            if (svalue & 0x8000)
                                svalue = svalue - 0x10000;
                        }
                        else if (params.param_width == 'l' || !params.param_width)
                        {
                            svalue = va_arg(args, int64_t) & 0xFFFFFFFF;
                            if (svalue & 0x80000000)
                                svalue = svalue - 0x100000000;
                        }
                        else
                            svalue = va_arg(args, int64_t);
                        if (svalue < 0)
                        {
                            value = 0 - svalue;
                            prefix = "-";
                        }
                        else
                        {
                            if (params.sign)
                            {
                                signbuf[0] = params.sign;
                                prefix = signbuf;
                            }
                            value = svalue;
                        }
                    }
                    if (hex || c == 'o')
                    {
                        int width = hex ? 16 : 22;
                        int start = -1;
                        /* Hex printing */
                        if (c == 'p' && value == 0)
                        {
                            start = width - 4;
                            memcpy(&buf[start], "NULL", 4);
                        }
#ifdef ZERO_IS_JUST_ZERO
                        else if (value == 0)
                        {
                            start = width - 1;
                            buf[start] = '0';
                        }
#endif
                        else
                        {
                            int mask = hex ? 15 : 7;
                            int shift = hex ? 4 : 3;
                            int i;
                            if (c == 'p' || (hex && params.alternate)) /* FIXME: Wrong in alignment? */
                                prefix = (c=='X') ? "0X" : "0x";
                            else if (c == 'o' && params.alternate)
                                prefix = "0";
                            for (i=width-1; i>-1; i--) /* FIXME: widen? */
                            {
                                int v = value & mask;
                                char x = "0123456789ABCDEF"[v];
                                if (c == 'x')
                                    x |= 32; /* Lower case */
                                buf[i] = x;
                                value = value >> shift;
                                if (start == -1 && value == 0)
                                {
                                    start = i;
                                    break;
                                }
                            }
                            if (start == -1)
                                start = 0;
                        }

                        int size = (width - start);
                        if (params.align_left)
                        {
                            n += pad_digits(out, &params, size, prefix);
                            n += out->writen(out, &buf[start], size);
                        }

                        if (params.field_width)
                            n += pad_output(out, &params, size + count_pad_digits(&params, size, prefix));

                        if (!params.align_left)
                        {
                            n += pad_digits(out, &params, size, prefix);
                            n += out->writen(out, &buf[start], size);
                        }
                    }
                    else
                    {
                        int size = __cvt_uint64_decimal(value, p);
                        if (params.align_left)
                        {
                            n += pad_digits(out, &params, size, prefix);
                            n += out->writen(out, buf, size);
                        }

                        if (params.field_width)
                            n += pad_output(out, &params, size + count_pad_digits(&params, size, prefix));

                        if (!params.align_left)
                        {
                            n += pad_digits(out, &params, size, prefix);
                            n += out->writen(out, buf, size);
                        }
                    }
                }
                break;

#ifndef NO_FP
            case 'f':
                double value = va_arg(args, double);
                int ndigits = params.precision == -1 ? 6 : params.precision;
                //char temp[ndigits + 7];
                char temp[64] = "X";
                if (ndigits > sizeof(temp) - 7)
                    ndigits = sizeof(temp) - 7;
                char *end = g_dfmt(temp, &value, ndigits, sizeof(temp));
                int size = end - temp;
                if (params.align_left)
                {
                    n += out->writen(out, temp, size);
                }

                if (params.field_width)
                    n += pad_output(out, &params, size);

                if (!params.align_left)
                {
                    n += out->writen(out, temp, size);
                }

                break;
#endif

            default:
                n += out->writec(out, '%');
                n += out->writec(out, c);
                break;
        }
    }

    return n;
}
