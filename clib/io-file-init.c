/*******************************************************************
 * File:        io-file-init
 * Purpose:     I/O file initialisation/finalisation
 * Author:      Gerph
 * Date:        11 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <stdio.h>

FILE *__file_list;
#pragma weak free

void __io_final(void)
{
    FILE *cur = __file_list;
    __file_list = NULL;
    if (free)
    {
        while (cur)
        {
            FILE *chain = cur->_chain;
            free(cur);
            cur = chain;
        }
    }
}
