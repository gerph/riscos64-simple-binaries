/*******************************************************************
 * File:        heap-o1heap-shim
 * Purpose:     Interface between heap allocator and O(1)heap
 *              https://github.com/pavel-kirienko/o1heap
 * Author:      Gerph
 * Date:        17 Aug 2024
 ******************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap-internal.h"
#include "heap-init.h"

#include "heap-o1heap.h"

//#define DEBUG

#ifdef DEBUG
#define dprintf if (1) printf
#else
#define dprintf if (0) printf
#endif

static O1HeapInstance *heap = NULL;

/* O1heap-type heap functions */
void HEAP_TYPEFUNC(O1heap, init) (void *base, size_t size)
{
    dprintf("o1heapInit(%p, %i)\n", base, size);

    /* We need the heap aligned to a O1HEAP_ALIGNMENT alignment, so move it around */
    uintptr_t unalignment = ((uintptr_t)base) % (O1HEAP_ALIGNMENT);
    dprintf("Unalignment = %i\n", unalignment);
    char *aligned = ((char *)base) + (unalignment ? (O1HEAP_ALIGNMENT - unalignment) : 0);
    size -= (aligned - (char*)base);
    dprintf("  aligned = (%p, %i)\n", aligned, size);

    heap = o1heapInit(aligned, size);
    if (heap == NULL)
        __heap_fatal("Not enough memory for heap");
}

void * HEAP_TYPEFUNC(O1heap, alloc) (size_t size)
{
    void *mem = (void*)o1heapAllocate(heap, size);
#ifdef DEBUG
    if (!mem)
    {
        dprintf("Failed to allocate %i bytes\n", size);
        O1HeapDiagnostics diag = o1heapGetDiagnostics(heap);
        dprintf("  capacity  = %i\n", diag.capacity);
        dprintf("  allocated = %i\n", diag.allocated);
        dprintf("  peak      = %i\n", diag.peak_allocated);
        dprintf("  peak req  = %i\n", diag.peak_request_size);
        dprintf("  ooms      = %i\n", diag.oom_count);
    }
#endif
    return mem;
}

void HEAP_TYPEFUNC(O1heap, free) (void *block, size_t size)
{
    o1heapFree(heap, block);
}

void * HEAP_TYPEFUNC(O1heap, realloc) (void *block, size_t new_size, size_t old_size)
{
    void *new_block = HEAP_TYPEFUNC(O1heap, alloc) (new_size);
    if (new_block != NULL)
    {
        memcpy(new_block, block, old_size);
        HEAP_TYPEFUNC(O1heap, free) (block, old_size); /* This is safe, because it's only going to manipulate the HWM */
    }
    return new_block;
}
