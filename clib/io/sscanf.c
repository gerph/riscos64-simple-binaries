/* Very very simple sscanf */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int sscanf(const char *str, const char *format, ...)
{
    int n;
    va_list args;
    va_start(args, format);

    n = vsscanf(str, format, args);

    va_end(args);
    return n;
}



int vsscanf(const char *str, const char *format, va_list args)
{
    int converted = 0;
    char c;
    //printf("vsscanf '%s' with '%s'\n", str, format);
    while (*format)
    {
        char c = *format++;
        switch (c)
        {
            case ' ':
                /* Space matches zero or more whitespace characters */
                while (*str && isspace(*str))
                    str++;
                break;

            case '%':
                /* A format conversion */
                /* FIXME: Flag characters */
                /* FIXME: Field width */

                c = *format++;
                if (c == '\0')
                    goto done;

                switch (c)
                {
                    case 's':
                        /* String conversion - read up to end of string, or whitespace */
                        char *dest = va_arg(args, char *);
                        //char *odest = dest;

                        /* Skip any leading spaces */
                        while (*str && isspace(*str))
                            str++;

                        while (*str && !isspace(*str))
                            *dest++ = *str++;
                        *dest = '\0';
                        //printf("Converted '%s', left '%s', format '%s'\n", odest, str, format);
                        converted++;
                        if (*str == '\0')
                        {
                            /* We stopped at terminator */
                            goto done;
                        }
                        break;
                }
                break;

            default:
                /* Anything else must match exactly */
                if (*str != c)
                    goto done;
                break;
        }
    }

done:
    return converted;
}
