/*******************************************************************
 * File:        heap-osheap
 * Purpose:     Heap implementation using OS_Heap
 * Author:      Gerph
 * Date:        17 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include "../kernel.h"
#include "../swis-os.h"

#include "internal.h"
#include "init.h"


/* OS_Heap-type heap functions */
void HEAP_TYPEFUNC(OSHeap, init) (void *base, size_t size)
{
    _kernel_oserror *err;
    err = os_heap(0, base, 0, size, NULL);
    if (err)
        __heap_fatal(err->errmess);
}

void * HEAP_TYPEFUNC(OSHeap, alloc) (size_t size)
{
    _kernel_oserror *err;
    void *mem = NULL;
    err = os_heap(2, __heap_base, 0, size, &mem);
    if (err)
    {
#ifdef HEAP_FAIL_IS_FATAL
        __heap_fatal(err->errmess);
#endif
    }
    return mem;
}

void HEAP_TYPEFUNC(OSHeap, free) (void *block, size_t size)
{
    _kernel_oserror *err;
    err = os_heap(3, __heap_base, block, 0, NULL);
    if (err)
        __heap_fatal(err->errmess);
}

void * HEAP_TYPEFUNC(OSHeap, realloc) (void *block, size_t new_size, size_t old_size)
{
    _kernel_oserror *err;
    void *p = NULL;
    err = os_heap(4, __heap_base, block, new_size, &p);
    if (err)
    {
#ifdef HEAP_FAIL_IS_FATAL
        __heap_fatal(err->errmess);
#else
        return NULL;
#endif
    }

    if (p == ((void *)-1))
        return NULL;
    return p;
}

__heap_implementation_t __heap_osheap = {
    HEAP_TYPEFUNC(OSHeap, init),
    HEAP_TYPEFUNC(OSHeap, alloc),
    HEAP_TYPEFUNC(OSHeap, free),
    HEAP_TYPEFUNC(OSHeap, realloc),
};
