#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "io-vprintf.h"


typedef struct formatparams_s {
    int alternate;
    int sign;
    int leading_char;
    int align_left;
    int field_width;
    int precision;
    int param_width;
} formatparams_t;

static int pad_output(outputter_t *out, formatparams_t *params, int size)
{
    /* They wanted this laid out into a field */
    char lead = params->leading_char ? params->leading_char : ' ';
    char shortbuf[8];
    int count = params->field_width - size;
    int n = 0;
    memset(shortbuf, lead, 8);
    while (count > 0)
    {
        n += out->writen(out, shortbuf, count > 8 ? 8 : count);
        count -= 8;
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
                params.sign = c;
                c = *format++;
            }
            else if (c=='#')
            {
                params.alternate = 1;
                c = *format++;
            }
            else if (c=='0')
            {
                params.leading_char = c;
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
                if (c>='1' && c<='9')
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
                    n += out->writec(out, c);
                }
                break;

            case 's':
                {
                    const char *s = va_arg(args, const char *);
                    int size;
                    if (s==NULL)
                        s = "<NULL>";
                    if (params.precision != 0)
                    {
                        for (size = 0; size < params.precision ; size++)
                        {
                            char sc = s[size];
                            if (sc == '\0')
                                break;
                        }
                    }
                    else
                    {
                        size = strlen(s);
                    }

                    if (params.align_left)
                        n += out->writen(out, s, size);

                    if (params.field_width)
                        n += pad_output(out, &params, size);

                    if (!params.align_left)
                        n += out->writen(out, s, size);
                }
                break;

            case 'p':
            case 'x':
            case 'X':
            case 'i':
            case 'd':
            case 'u':
                {
                    char buf[22];
                    char *p = buf;
                    bool hex = (c=='p' || c=='x' || c=='X');
                    uint64_t value;
                    if (c == 'u' || hex)
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
                        int64_t uvalue;
                        if (params.param_width == 'b')
                        {
                            uvalue = va_arg(args, int64_t) & 0xFF;
                            if (uvalue & 0x80)
                                uvalue = uvalue - 0x100;
                        }
                        else if (params.param_width == 'h')
                        {
                            uvalue = va_arg(args, int64_t) & 0xFFFF;
                            if (uvalue & 0x8000)
                                uvalue = uvalue - 0x10000;
                        }
                        else if (params.param_width == 'l' || !params.param_width)
                        {
                            uvalue = va_arg(args, int64_t) & 0xFFFFFFFF;
                            if (uvalue & 0x80000000)
                                uvalue = uvalue - 0x100000000;
                        }
                        else
                            uvalue = va_arg(args, int64_t);
                        if (uvalue < 0)
                        {
                            uvalue = 0 - uvalue;
                            *p++ = '-';
                        }
                        else
                        {
                            if (params.sign)
                                *p++ = params.sign;
                        }
                        value = uvalue;
                    }
                    if (hex)
                    {
                        int start = -1;
                        /* Hex printing */
                        if (c == 'p' && value == 0)
                        {
                            start = 16 - 4;
                            strcpy(&buf[start], "NULL");
                        }
                        else
                        {
                            int i;
                            if (c == 'p' || params.alternate) /* FIXME: Wrong in alignment? */
                                n += out->writen(out, c=='X' ? "0X" : "0x", 2);
                            for (i=16-1; i>-1; i--) /* FIXME: widen? */
                            {
                                int v = value & 15;
                                char x = "0123456789ABCDEF"[v];
                                if (c == 'x')
                                    x |= 32; /* Lower case */
                                buf[i] = x;
                                value = value >> 4;
                                if (start == -1 && value == 0)
                                {
                                    start = i;
                                    break;
                                }
                            }
                            if (start == -1)
                                start = 0;
                        }

                        if (params.align_left)
                            n += out->writen(out, &buf[start], 16 - start);

                        if (params.field_width)
                            n += pad_output(out, &params, 16 - start);

                        if (!params.align_left)
                            n += out->writen(out, &buf[start], 16-start);
                    }
                    else
                    {
                        /* Decimal printing */
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
                                10000000000000000000u,
                            };
                        int size = 19;

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
#ifdef ARCH_HAS_DIVISION
                                digit = value / m;
                                value = value % m;
#else
                                value -= m;
                                while (value >= m)
                                    digit += 1, value -= m;
#endif
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
                        if (p == buf)
                            *p++ = '0';

                        if (params.align_left)
                            n += out->writen(out, buf, p - buf);

                        if (params.field_width)
                            n += pad_output(out, &params, p - buf);

                        if (!params.align_left)
                            n += out->writen(out, buf, p - buf);
                    }
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
