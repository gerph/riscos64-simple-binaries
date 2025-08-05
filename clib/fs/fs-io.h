/*******************************************************************
 * File:        fs-io
 * Purpose:     Filesystem I/O dispatchers
 * Author:      Gerph
 * Date:        4 Aug 2025
 ******************************************************************/

#ifndef FS_IO_H
#define FS_IO_H

#include <stdio.h>

/*************************************************** Gerph *********
 Function:      __fs_setup_dispatch
 Description:   Set up the dispatch table used by the I/O system
 Parameters:    fh-> the file handle
 Returns:       none
 ******************************************************************/
void __fs_setup_dispatch(FILE *fh);

#endif
