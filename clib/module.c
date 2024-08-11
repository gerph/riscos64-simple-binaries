/*******************************************************************
 * File:        module
 * Purpose:     Module initialisation/finalisation functions
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include "kernel.h"
#include "main-exit.h"


_kernel_oserror *_clib_initialisemodule(void *pwp)
{
    /* Perform zero-init ? */
    return NULL;
}

_kernel_oserror *_clib_finalisemodule(void *pwp)
{
    /* Perform zero-init ? */
    extern void clib_finalise(void);
    _clib_finalise();
    return NULL;
}
