/*******************************************************************
 * File:        sysvars-kernel
 * Purpose:     System variables handling (kernel functions)
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <string.h>
#include "kernel.h"
#include "swis.h"

_kernel_oserror *_kernel_setenv(const char *var, const char *val)
{
    _kernel_oserror *err;
    err = _swix(OS_SetVarVal, _INR(0,4), var, val, strlen(val), 0, 4);
    return err;
}

_kernel_oserror *_kernel_getenv(const char *var, char *buf, unsigned size)
{
    _kernel_oserror *err;
    int wrote;
    err = _swix(OS_ReadVarVal, _INR(0,4)|_OUT(2), var, buf, size - 1, 0, 3, &wrote);
    if (! err)
        buf[wrote] = '\0';
    return err;
}
