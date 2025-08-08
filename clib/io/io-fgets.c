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

char *fgets(char *str, int size, FILE *fh)
{
    int result;

    CHECK_MAGIC(fh, NULL);

    if (!IO_IS_READABLE(fh))
    {
        errno = EPERM;
        return NULL;
    }

    result = IO_DISPATCH(fh)->read_line(fh, str, size);
    if (result < 0)
    {
        errno = -result;
        return NULL;
    }

    return str;
}
