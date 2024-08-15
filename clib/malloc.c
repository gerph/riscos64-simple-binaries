/*******************************************************************
 * File:        malloc
 * Purpose:     Memory allocation on the heap
 * Author:      Gerph
 * Date:        03 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "swis.h"
#include "swis-os.h"
#include "kernel-state.h"

#include "heap_init.h"

/* Define this to make failures of the heap fatal */
#define HEAP_FAIL_IS_FATAL

/* Type of heap we're providing */
//#define HEAP_SIMPLE_ACCUMULATOR
#define HEAP_OSHEAP



void heap_fatal(const char *msg)
{
    os_write0(msg);
    os_newline();
    exit(1);
}


typedef struct alloc_s {
    size_t size;
    char data[0];
} alloc_t;

#if defined(HEAP_SIMPLE_ACCUMULATOR)
static void *last_alloc = NULL;

#define HEAP_LEFT (__heap_end - __heap_hwm)
#endif

__THROW __attribute_malloc__
void *malloc (size_t size)
{
    void *allocated = NULL;

    if (_kernel_inmodule)
    {
        /* Allocate through OS_Module */
        _kernel_oserror *err = os_module(6, 0, size, (void**)&allocated);
        if (err)
            return NULL;
        return allocated;
    }

    if (__heap_base == NULL)
        heap_fatal("No heap memory");

#if defined(HEAP_SIMPLE_ACCUMULATOR)
    void *mem = (void*)__heap_hwm;
    /* Round to a multiple of 8 */
    size = (size + 7 + sizeof(alloc_t)) & ~7;
    __heap_hwm += size;
    if (HEAP_LEFT > 0)
    {
        alloc_t *p = (alloc_t*)mem;
        p->size = size;
        last_alloc = (void*)&p->data;
        allocated = (void*)&p->data;
    }

#elif defined(HEAP_OSHEAP)
    size = (size + 7 + sizeof(alloc_t)) & ~7;

    _kernel_oserror *err;
    if (__heap_base[0] == '\0')
    {
        /* This is the first call, so we initialise the heap */
        err = os_heap(0, __heap_base, 0, __heap_end - __heap_base, NULL);
        if (err)
            heap_fatal(err->errmess);
    }

    alloc_t *p = NULL;
    err = os_heap(2, __heap_base, 0, size, (void**)&p);
    if (err)
    {
#ifdef HEAP_FAIL_IS_FATAL
        heap_fatal(err->errmess);
#endif
    }
    else
    {
        p->size = size;
        allocated = (void*)&p->data;
    }
#endif

    if (allocated)
        return allocated;

fail:
#ifdef HEAP_FAIL_IS_FATAL
    char buffer[80];
#define MSG0 "OUT OF MEMORY - need &"
#define MSG1 " bytes"
    char *s;
    memcpy(buffer, MSG0, sizeof(MSG0) - 1);
    s = buffer + sizeof(MSG0) - 1;
#if defined(HEAP_SIMPLE_ACCUMULATOR)
    uint64_t need = -HEAP_LEFT;
#else
    uint64_t need = size;
#endif
    int started = 0;
    for(int i=60; i >= 0; i-=4)
    {
        unsigned int v = (need>>i) & 15;
        if (v || started || i == 0)
        {
            started = 1;
            *s++ = "0123456789ABCDEF"[v];
        }
    }
    memcpy(s, MSG1, sizeof(MSG1));
    heap_fatal(s);
#else
    return NULL;
#endif
}

void *calloc(size_t count, size_t size)
{
    int total = count * size;
    void *mem = malloc(total);
    memset(mem, 0, size);
    return mem;
}

void free(void *block)
{
    if (block == NULL)
        return;

    if (_kernel_inmodule)
    {
        /* Free through OS_Module */
        _kernel_oserror *err = os_module(7, block, 0, NULL);
        /* Cannot do anything with the error */
        return;
    }

    if (__heap_base == NULL)
        heap_fatal("No heap memory");

#if defined(HEAP_SIMPLE_ACCUMULATOR)
    if (block == last_alloc)
    {
        /* Just handle the last allocation being removed */
        last_alloc = NULL;

        alloc_t *p = ((alloc_t *)block) - 1;
        __heap_hwm -= p->size;
        return; /* We freed at the end of the heap */
    }
    /* Nothing to do */
#else
    alloc_t *p = ((alloc_t *)block) - 1;

    _kernel_oserror *err;
    err = os_heap(3, __heap_base, p, 0, NULL);
    if (err)
        heap_fatal(err->errmess);
#endif
}

void *realloc(void *block, size_t size)
{
    if (size == 0)
    {
        free(block);
        return NULL;
    }
    if (block == NULL)
        return malloc(size);

    if (_kernel_inmodule)
    {
        /* Resize through OS_Module */
        void *new_block;
        uint32_t *p = (uint32_t*)block;
        size_t old_size = p[-1] - 4;
        _kernel_oserror *err = os_module(13, block, size - old_size, &new_block);
        if (err)
            return NULL;
        return new_block;
    }

    if (__heap_base == NULL)
        heap_fatal("No heap memory");

#if defined(HEAP_SIMPLE_ACCUMULATOR)
    size_t new_size = (size + 7 + sizeof(alloc_t)) & ~7;

    alloc_t *p = ((alloc_t *)block) - 1;

    size_t old_size = p->size;
    if (old_size >= new_size)
        return block; /* Reduced the size, so this block is fine */

    free(block); /* This is safe, because it's only going to manipulate the HWM */

    void *new_block = malloc(size);
    if (new_block != block && new_block != NULL)
        memcpy(new_block, block, old_size - sizeof(alloc_t));
    return new_block;
#elif defined(HEAP_OSHEAP)
    size_t new_size = (size + 7 + sizeof(alloc_t)) & ~7;

    alloc_t *p = ((alloc_t *)block) - 1;
    size_t old_size = p->size;

    _kernel_oserror *err;
    err = os_heap(4, __heap_base, p, new_size, (void**)&p);
    if (err)
#ifdef HEAP_FAIL_IS_FATAL
        heap_fatal(err->errmess);
#else
        return NULL;
#endif

    if (p == ((alloc_t *)-1))
        return NULL;
    return (void*)&p->data;
#endif
}
