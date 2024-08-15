/*******************************************************************
 * File:        io-console
 * Purpose:     Simple console input/output functions
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include "swis-os.h"

int getchar(void)
{
    return os_readc();
}

int putchar(char c)
{
    os_writec(c);
    return c;
}
