/*******************************************************************
 * File:        sysvars-kernel
 * Purpose:     System variables handling (kernel functions)
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <string.h>
#include "kernel.h"
#include "swis.h"

/*************************************************** Gerph *********
 Function:      _kernel_setenv
 Description:   Set an environment variable
 Parameters:    var-> the variable name to set
                val-> the value to set to, or NULL to delete
 Returns:       pointer to error if failed, or NULL if successful
 ******************************************************************/
_kernel_oserror *_kernel_setenv(const char *var, const char *val)
{
    _kernel_oserror *err;
    int len;
    if (val == NULL)
        len = -1;
    else
        len = strlen(val);
    err = _swix(OS_SetVarVal, _INR(0,4), var, val, len, 0, 4);
    return err;
}

/*************************************************** Gerph *********
 Function:      _kernel_getenv
 Description:   Read the environment variable into a supplied buffer,
                as a 0-terminated string
 Parameters:    var-> the variable name to read
                buf-> the buffer to use to read the string into
                size = the size of the buffer
 Returns:       pointer to error if failed, or NULL if successful
 ******************************************************************/
_kernel_oserror *_kernel_getenv(const char *var, char *buf, unsigned size)
{
    _kernel_oserror *err;
    int wrote;
    err = _swix(OS_ReadVarVal, _INR(0,4)|_OUT(2), var, buf, size - 1, 0, 3, &wrote);
    if (! err)
        buf[wrote] = '\0';
    return err;
}
