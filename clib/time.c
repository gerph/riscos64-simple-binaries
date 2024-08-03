#include <stddef.h>

#include "kernel.h"
#include "swis.h"

int clock(void)
{
    _kernel_swi_regs regs;
    _kernel_swi(OS_ReadMonotonicTime, NULL, &regs);
    return regs.r[0];
}
