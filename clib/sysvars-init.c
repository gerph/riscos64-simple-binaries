/*******************************************************************
 * File:        sysvars-init
 * Purpose:     System variables initialisation/finalisation
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include "swis.h"

char *__envstring = NULL;
int __envstringlen = 0;

void __getenv_final(void)
{
    if (__envstring)
    {
        free(__envstring);
        __envstring = NULL;
    }
}
