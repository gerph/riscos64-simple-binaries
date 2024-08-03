/*******************************************************************
 * File:        heap_init
 * Purpose:     Heap initialisation
 * Author:      Gerph
 * Date:        03 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "swis.h"

#include "heap_init.h"

/* Define this to make failures of the heap fatal */
#define HEAP_FAIL_IS_FATAL



#define HEAP_LEFT (__heap_end - __heap_hwm)


typedef struct alloc_s {
    size_t size;
    char data[0];
} alloc_t;

static void *last_alloc = NULL;

__THROW __attribute_malloc__
void *malloc (size_t size)
{
    void *mem = (void*)__heap_hwm;
    /* Round to a multiple of 8 */
    size = (size + 7 + sizeof(alloc_t)) & ~7;
    __heap_hwm += size;
    if (HEAP_LEFT < 0)
    {
#ifdef HEAP_FAIL_IS_FATAL
        os_write0("OUT OF MEMORY - need &");
        uint64_t need = -HEAP_LEFT;
        int started = 1;
        for(int i=60; i >= 0; i-=4)
        {
            unsigned int v = (need>>i) & 15;
            if (v || started || i == 0)
            {
                started = 1;
                os_writec("0123456789ABCDEF"[v]);
            }
        }
        os_write0(" bytes");
        os_newline();
        exit(1);
#else
        return NULL;
#endif
    }
    alloc_t *p = (alloc_t*)mem;
    p->size = size;
    last_alloc = (void*)&p->data;
    return (void*)&p->data;
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
    if (block == last_alloc)
    {
        /* Just handle the last allocation being removed */
        last_alloc = NULL;

        alloc_t *p = ((alloc_t *)block) - 1;
        __heap_hwm -= p->size;
        return; /* We freed at the end of the heap */
    }
    /* Nothing to do */
}

void *realloc(void *block, size_t size)
{
    size_t new_size = (size + 7 + sizeof(alloc_t)) & ~7;

    if (size == 0)
    {
        free(block);
        return NULL;
    }
    if (block == NULL)
        return malloc(size);

    alloc_t *p = ((alloc_t *)block) - 1;

    size_t old_size = p->size;
    if (old_size >= new_size)
        return block; /* Reduced the size, so this block is fine */

    free(block); /* This is safe, because it's only going to manipulate the HWM */

    void *new_block = malloc(size);
    if (new_block != block)
        memcpy(new_block, block, old_size - sizeof(alloc_t));
    return new_block;
}
