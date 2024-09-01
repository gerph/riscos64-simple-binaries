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

#include "../swis.h"

#include "internal.h"
#include "init.h"

int __heap_inited;
char *__heap_base;
char *__heap_end;

__heap_implementation_t * __attribute__((weak)) __heap_implementation;

void __heap_init(void *append, void *heap_limit)
{
    __heap_base = (char *)append;
    __heap_base[0] = '\0'; /* Marker that we haven't been initialised */
    __heap_end = (char *)heap_limit;
    __heap_inited = 0;
    if (!__heap_implementation)
        __heap_implementation = &__heap_o1;
}

