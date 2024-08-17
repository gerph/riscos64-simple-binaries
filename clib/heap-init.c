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

#include "heap-init.h"

int __heap_inited;
char *__heap_base;
char *__heap_end;

void __heap_init(void *append, void *heap_limit)
{
    __heap_base = (char *)append;
    __heap_base[0] = '\0'; /* Marker that we haven't been initialised */
    __heap_end = (char *)heap_limit;
    __heap_inited = 0;
}

