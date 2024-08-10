/*******************************************************************
 * File:        sysvars
 * Purpose:     System variables handling
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <string.h>
#include "swis.h"

#define INITIAL_SIZE (256)
#define INCREMENT    (256)
#define MAXIMUM_SIZE (2048) /* Just to stop pathological cases */

#define ErrorNumber_BuffOverflow (0x1e4)

extern char *__envstring;
extern int __envstringlen;

char *getenv(const char *var)
{
    _kernel_oserror *err;
    if (__envstring == NULL)
    {
        __envstring = malloc(INITIAL_SIZE);
        if (__envstring == NULL)
            return NULL; /* Not enough space, so give up now */
        __envstringlen = INITIAL_SIZE;
    }

    while (1)
    {
        int wrote;
        err = _swix(OS_ReadVarVal, _INR(0,4)|_OUT(2), var, __envstring, __envstringlen, 0, 3, &wrote);
        if (err == NULL)
        {
            __envstring[wrote] = '\0';
            return __envstring;
        }
        if (err->errnum != ErrorNumber_BuffOverflow)
        {
            /* We couldn't find the variable, or something else bad; give up */
            return NULL;
        }

        int newsize = __envstringlen + INCREMENT;
        if (newsize > MAXIMUM_SIZE)
            return NULL; /* Not enough room - give up */

        char *newstring = realloc(__envstring, newsize);
        if (newstring == NULL)
            return NULL; /* Couldn't allocate space - give up */

        __envstring = newstring;
        __envstringlen = newsize;
    }
}
