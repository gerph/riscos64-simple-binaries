/*******************************************************************
 * File:        malloc
 * Purpose:     Really really dumb malloc code
 * Author:      Gerph
 * Date:        25 Jul 2024
 ******************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Some memory */
#ifndef HEAP_SIZE
#define HEAP_SIZE (1024*128)
#endif

static char memory[HEAP_SIZE];
static char *freep = memory;
static int left = sizeof(memory);

__THROW __attribute_malloc__
void *malloc (size_t size)
{
    void *mem = (void*)freep;
    /* Round to a multiple of 8 */
    size = (size + 7 + sizeof(size_t)) & ~7;
    freep += size;
    left -= size;
    if (left < 0)
    {
        printf("OUT OF MEMORY - need %i bytes\n", size);
        exit(1);
    }
    size_t *p = (size_t*)mem;
    *p++ = size;
    return (void*)p;
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
    /* Nothing to do */
}

void *realloc(void *block, size_t size)
{
    size_t new_size = (size + sizeof(size_t)) & ~7;

    if (size == 0)
    {
        free(block);
        return NULL;
    }
    if (block == NULL)
        return malloc(size);

    size_t old_size = ((size_t*)block)[-1];
    if (old_size >= new_size)
        return block; /* Reduced the size, so this block is fine */

    void *new_block = malloc(size);
    memcpy(new_block, block, old_size - sizeof(size_t));
    return new_block;
}
