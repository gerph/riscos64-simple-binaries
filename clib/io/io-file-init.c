/*******************************************************************
 * File:        io-file-init
 * Purpose:     I/O file initialisation/finalisation
 * Author:      Gerph
 * Date:        11 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <kernel.h>

#include "io/io-internal.h"

FILE *__file_list;
#pragma weak free
#pragma weak fclose

void __io_init(void)
{
    stdin->_flags = _IO_MAGIC | _IO_READABLE | _IO_CONSOLE;
    stdout->_flags = _IO_MAGIC | _IO_WRITABLE | _IO_CONSOLE;
    stderr->_flags = _IO_MAGIC | _IO_WRITABLE | _IO_CONSOLE;
}


void __io_final(void)
{
    FILE *cur = __file_list;
    __file_list = NULL;
    if (free)
    {
        while (cur)
        {
            FILE *chain = cur->_chain;
            if (fclose)
            {
                fclose(cur);
            }
            else
            {
                free(cur);
            }
            cur = chain;
        }
        /* Finally close the stdout, stdin, stderr handles */
        if (fclose)
        {
            fclose(stdin);
            fclose(stdout);
            fclose(stderr);
        }
    }
}
