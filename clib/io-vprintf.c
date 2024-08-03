#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "io-vprintf.h"


typedef struct formatparams_s {
    int leading_char;
    int align_left;
    int field_width;
    int precision;
    int param_width;
} formatparams_t;


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
