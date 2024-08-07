#include <stdint.h>
#include "kernel.h"

#include "swi_numbers.h"

#define _FLAGS     0x10 /*use with _RETURN() or _OUT()*/
#define _IN(i)     (1U << (i))
#define _INR(i,j)  (~0 << (i) ^ ~0 << (j) + 1)
#define _OUT(i)    ((i) != _FLAGS? 1U << (31 - (i)): (1U << 21))
#define _OUTR(i,j) (~0U >> (i) ^ ~0U >> (j) + 1)
#define _C         (1U << 29)
#define _Z         (1U << 30)
#define _N         (1U << 31)

_kernel_oserror *_swix (int swi_no, unsigned int, ...);
