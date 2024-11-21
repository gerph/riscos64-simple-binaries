#include <stddef.h>
#include <time.h>

#include "kernel.h"
#include "swis.h"

#include "time-clock.h"

static int base_time;

void __clock_init(void)
{
    base_time = 0;
    base_time = clock();
}

clock_t clock(void)
{
    _kernel_swi_regs regs;
    _kernel_swi(OS_ReadMonotonicTime, NULL, &regs);
    return regs.r[0] - base_time;
}
