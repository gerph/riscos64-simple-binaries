/*******************************************************************
 * File:        kernel-state
 * Purpose:     Variables that declare the state of the kernel os
 * Author:      Gerph
 * Date:        14 Aug 2024
 ******************************************************************/

#include <stddef.h>
#include <stdbool.h>

#include "kernel-state.h"

bool _kernel_inmodule = false;
_kernel_oserror *_last_error = NULL;


/*************************************************** Gerph *********
 Function:      _kernel_init
 Description:   Initialise the kernel state
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _kernel_init(void)
{
    /* Note: Note do not initialise _kernel_inmodule as this must
     *       be initialised by the initialisation that is in use.
     */
    _last_error = NULL;
}
