/*******************************************************************
 * File:        perror
 * Purpose:     Print the error (perror)
 * Author:      Gerph
 * Date:        25 Mar 2025
 ******************************************************************/

#include <errno.h>
#include <stdio.h>


void
perror(const char *s)
{
    char *errmsg = strerror(errno);
    fflush(stderr);
    if (s)
        fprintf(stderr, "%s: %s\n", s, errmsg);
    else
        fprintf(stderr, "%s\n", errmsg);
}
