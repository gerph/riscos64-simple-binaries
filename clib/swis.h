#include <stdint.h>
#include "kernel.h"

#include "swi_numbers.h"

#define _IN(i)     (1U << (i))
#define _INR(i,j)  (~0 << (i) ^ ~0 << (j) + 1)
#define _OUT(i)    (1U << (31 - (i)))
#define _OUTR(i,j) (~0U >> (i) ^ ~0U >> (j) + 1)
#define _RETURN(i) ((i) << 16)
#define _C         (1U << 29)
#define _Z         (1U << 30)
#define _N         (1U << 31)

_kernel_oserror *_swix (int swi_no, uint32_t flags, ...);
uint64_t _swi(int swi_no, uint32_t flags, ...);
