/*******************************************************************
 * File:        io-fgets.c
 * Purpose:     Implementation of fgets, diverting to OS_ReadLine
 * Author:      Gerph
 * Date:        5 May 2025
 ******************************************************************/

#include <stdio.h>

#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"

/*************************************************** Gerph *********
 Function:      os_readline
 Description:   Call OS_ReadLine for input
 Parameters:    line-> line to read
                len = max length including terminator
 Returns:       1 for success, 0 for failure
 ******************************************************************/
static int os_readline(char *line, int len)
{
    _kernel_oserror *err;
    int read;
    uint32_t flags = 0;
#ifdef __riscos64
    err = _swix(OS_ReadLine32, _INR(0, 4)|_OUTR(0, 1), line, len, 32, 128, 0, &flags, &read);
    if (err)
        return 0;
    if (flags)
        goto escape;
    line[read] = '\0';
    return 1;
#else
    err = _swix(OS_ReadLine32, _INR(0, 4)|_OUT(1)|_OUT(_FLAGS), line, len, 32, 128, 0, &read, &flags);
#ifndef ErrorNumber_ModuleBadSWI
#define ErrorNumber_ModuleBadSWI          0x110
#endif
    if (err && err->errnum == ErrorNumber_ModuleBadSWI)
    {
        err = _swix(OS_ReadLine, _INR(0, 4)|_OUT(1)|_OUT(_FLAGS), line, len, 32, 128, 0, &read, &flags);
    }
    if (err)
        return 0;
    if (flags & _C)
        goto escape;
    line[read] = '\0';
    return 1;
#endif

escape:
    return 0;
}

char *fgets(char *str, int size, FILE *fh)
{
    char *p;
    if (!fh)
        return NULL;

    if (fh == stdin)
    {
        /* They want to read a line from stdin. Might as well use OS_ReadLine */
        if (!os_readline(str, size))
            return NULL;
        return str;
    }
    if (fh == stdout || fh == stderr)
    {
        return NULL;
    }

    CHECK_MAGIC(fh, NULL);

    for (p = str; p - str < size - 1; p++)
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
