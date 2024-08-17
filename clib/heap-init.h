/*******************************************************************
 * File:        heap_init
 * Purpose:     Heap initialisation
 * Author:      Gerph
 * Date:        03 Aug 2024
 ******************************************************************/

#ifndef HEAPINIT_H
#define HEAPINIT_H

extern char *__heap_base;
extern char *__heap_end;
extern int __heap_inited;

void __heap_init(void *append, void *heap_limit);

#endif
