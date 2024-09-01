/*******************************************************************
 * File:        heap-accumulator
 * Purpose:     Very simple accumulator heap that grows up from the base
 * Author:      Gerph
 * Date:        17 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <string.h>

#include "internal.h"
#include "init.h"

static void *last_alloc = NULL;
static char *__heap_hwm = NULL;

#define HEAP_LEFT (__heap_end - __heap_hwm)

/* Accumulator-type heap functions */
void HEAP_TYPEFUNC(Accumulator, init) (void *base, size_t size)
{
    __heap_hwm = base;
    last_alloc = NULL;
}

void * HEAP_TYPEFUNC(Accumulator, alloc) (size_t size)
{
    void *mem = (void*)__heap_hwm;
    __heap_hwm += size;
    if (HEAP_LEFT > 0)
    {
        last_alloc = mem;
        return mem;
    }
    return NULL;
}

void HEAP_TYPEFUNC(Accumulator, free) (void *block, size_t size)
{
    if (block == last_alloc)
    {
        /* Just handle the last allocation being removed */
        last_alloc = NULL;
        __heap_hwm -= size;
        return; /* We freed at the end of the heap */
    }
    /* Nothing to do */
}

void * HEAP_TYPEFUNC(Accumulator, realloc) (void *block, size_t new_size, size_t old_size)
{
    if (old_size >= new_size)
    {
        if (last_alloc == block)
        {
            /* High watermark has gone down by a bit */
            __heap_hwm = __heap_hwm - old_size + new_size;
        }
        return block; /* Reduced the size, so this block is fine */
    }

    HEAP_TYPEFUNC(Accumulator, free) (block, old_size); /* This is safe, because it's only going to manipulate the HWM */

    void *new_block = HEAP_TYPEFUNC(Accumulator, alloc) (new_size);
    if (new_block != block && new_block != NULL)
        memcpy(new_block, block, old_size);
    return new_block;
}

__heap_implementation_t __heap_accumulator = {
    HEAP_TYPEFUNC(Accumulator, init),
    HEAP_TYPEFUNC(Accumulator, alloc),
    HEAP_TYPEFUNC(Accumulator, free),
    HEAP_TYPEFUNC(Accumulator, realloc),
};
