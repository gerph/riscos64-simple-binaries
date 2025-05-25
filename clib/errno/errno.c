/*******************************************************************
 * File:        errno
 * Purpose:     errno initialisation
 * Author:      Gerph
 * Date:        08 Aug 2024
 ******************************************************************/

#include <stdint.h>

int errno;

int *__errno_location(void)
{
    return &errno;
}
