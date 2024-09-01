/*******************************************************************
 * File:        heap_init
 * Purpose:     Heap initialisation
 * Author:      Gerph
 * Date:        03 Aug 2024
 ******************************************************************/

#ifndef HEAPINIT_H
#define HEAPINIT_H

#include "_heap_implementation.h"

extern char *__heap_base;
extern char *__heap_end;
extern int __heap_inited;
extern __heap_implementation_t * __attribute__((weak)) __heap_implementation;

void __heap_init(void *append, void *heap_limit);

#endif
