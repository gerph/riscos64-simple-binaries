/*******************************************************************
 * File:        io-consoleio
 * Purpose:     Console I/O dispatchers
 * Author:      Gerph
 * Date:        4 Aug 2025
 ******************************************************************/

#ifndef IO_CONSOLEIO_H
#define IO_CONSOLEIO_H

#include <stdio.h>

/*************************************************** Gerph *********
 Function:      __con_setup_dispatch
 Description:   Set up the dispatch table used by the I/O system
 Parameters:    fh-> the file handle
 Returns:       none
 ******************************************************************/
void __con_setup_dispatch(FILE *fh);

#endif
