/*******************************************************************
 * File:        kernel-state
 * Purpose:     Variables that declare the state of the kernel os
 * Author:      Gerph
 * Date:        14 Aug 2024
 ******************************************************************/

#ifndef KERNEL_STATE_H
#define KERNEL_STATE_H

#include <stdbool.h>
#include "kernel.h"

extern bool _kernel_inmodule;
extern _kernel_oserror *_last_error;

/* Our error copy */
#define _kernel_copyerror(err) _last_error = (err)

/*************************************************** Gerph *********
 Function:      _kernel_init
 Description:   Initialise the kernel state
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _kernel_init(void);

#endif
