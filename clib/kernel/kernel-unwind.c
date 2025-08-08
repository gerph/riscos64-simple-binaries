/*******************************************************************
 * File:        kernel-unwind
 * Purpose:     Unwind stack and related functions
 * Author:      Gerph
 * Date:        14 Sep 2024
 ******************************************************************/

#include <stdlib.h>
#include "kernel.h"
#include "swis_os.h"

#define MAX_SEARCH (250)

/* The highest addressable location */
#define MEMORY_LIMIT (0xFFFFFFFFu)

/*************************************************** Gerph *********
 Function:      _kernel_procname
 Description:   For a given PC, return the procedure name
 Parameters:    pc = the address to search
 Returns:       Pointer to the function name, or NULL if none known
 ******************************************************************/
const char *_kernel_procname(uint64_t pc)
{
    uint32_t *z = (uint32_t *)pc;
    const char *name = NULL;
    int i;

    if (pc > MEMORY_LIMIT)
        return NULL;

    /* I search up to 100 words before the pc looking for the marker that    */
    /* shows me where the function name is.                                  */
    for (i=0; i<MAX_SEARCH && z>(uint32_t*)0x8000; i++)
    {   int w = *--z;
        if ((w & 0xffff0003) == 0xff000000)
        {   name = (char *)z - (w & 0xffff);
            break;
        }
    }
    if (i == MAX_SEARCH || z<=(uint32_t*)0x8000)
        return NULL;
    return name;
}

/* In the assembler file */
int _kernel_unwind_current(_kernel_unwindblock *inout);

/*************************************************** Gerph *********
  Function:      _kernel_unwind
  Description:   Unwind the stack; of return the current state
  Parameters:    inout-> the unwind block to step up from
                 language-> where to store the language name pointer
  Returns:       >0 if got a stack entry
                 0 if we reached the end of the backtrace
                 <0 if something went wrong
  ******************************************************************/
int _kernel_unwind(_kernel_unwindblock *inout, char **language)
{
    uint64_t *fp = (uint64_t *)inout->fp;
    if (fp == NULL)
    {
        _kernel_unwind_current(inout);
        return 1; /* Got a stack frame */
    }

    if (((uint64_t)fp) & 3 || ((uint64_t)fp) < 0x8000 || ((uint64_t)fp) > MEMORY_LIMIT)
        return -1; /* Invalid; give up */

    /* Roll back to prior entry */
    uint64_t *caller_fp = (uint64_t *)fp[0];
    uint64_t *caller_pc = (uint64_t *)fp[1];

    if (((uint64_t)caller_fp) & 3 ||
        (((uint64_t)caller_fp) < 0x8000 && caller_fp != NULL) ||
        ((uint64_t)caller_fp) > MEMORY_LIMIT)
        return -1; /* Invalid FP; give up */
    if (((uint64_t)caller_pc) & 3 ||
        ((uint64_t)caller_pc) < 0x8000 ||
        ((uint64_t)caller_pc) > MEMORY_LIMIT)
        return -1; /* Invalid PC; give up */

    inout->fp = (uint64_t)(caller_fp);
    inout->sp = (uint64_t)(fp + 2);
    inout->pc = (uint64_t)(caller_pc);
    inout->lr = caller_fp ? (uint64_t)caller_fp[1] : (uint64_t)0;

    if (language)
        *language = "Unknown";

    return (inout->fp == 0) ? 0 : 1;
}

int _kernel_unwind(_kernel_unwindblock *inout, char **language);
