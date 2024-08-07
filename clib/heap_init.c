/*******************************************************************
 * File:        heap_init
 * Purpose:     Heap setup
 * Author:      Gerph
 * Date:        25 Jul 2024
 ******************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "swis.h"

#include "heap_init.h"

char *__heap_base;
char *__heap_hwm;
char *__heap_end;

void __heap_init(void *append, void *heap_limit)
{
    __heap_base = (char *)append;
    __heap_end = (char *)heap_limit;
    __heap_hwm = __heap_base;
}

