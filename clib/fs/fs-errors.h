/*******************************************************************
 * File:        fs-errors
 * Purpose:     Handle FS errors
 * Author:      Gerph
 * Date:        25 Mar 2025
 ******************************************************************/

#ifndef FS_ERRORS_H
#define FS_ERRORS_H

#include "kernel.h"

/*************************************************** Gerph *********
 Function:      __fs_seterrno
 Description:   Set the errno variable based on filesystem error numbers
 Parameters:    err-> the error block returned
 Returns:       none
 ******************************************************************/
void __fs_seterrno(_kernel_oserror *err);

#endif
