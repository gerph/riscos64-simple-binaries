#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#include "kernel.h"
#include "swis.h"

#include "time-clock.h"

static int64_t base_time;
static int64_t frozen_time;

uint64_t __sysclock(void)
{
    _kernel_swi_regs regs;
    _kernel_swi(OS_ReadMonotonicTime, NULL, &regs);
    return regs.r[0];
}

/*************************************************** Gerph *********
 Function:      __clock_init
 Description:   Initialise the clock which returns the number of ticks process has run for
 Parameters:    none
 Returns:       none
 ******************************************************************/
void __clock_init(void)
{
    base_time = 0;
    base_time = __sysclock();
    frozen_time = 0;
}

/*************************************************** Gerph *********
 Function:      __clock_freeze
 Description:   Freeze/unfreeze the clock whilst we're pending user interaction
 Parameters:    freeze = true to freeze the clock, or false to unfreeze it
 Returns:       none
 ******************************************************************/
void __clock_freeze(bool freeze)
{
    if (freeze && frozen_time == 0)
    {
        /* Freeze and we weren't frozen */
        frozen_time = __sysclock();
    }
    else if (!freeze && frozen_time != 0)
    {
        /* Unfreeze and we were frozen */
        uint64_t diff = __sysclock() - frozen_time;
        base_time += diff;
        frozen_time = 0;
    }
}


/*************************************************** Gerph *********
 Function:      clock
 Description:   Return number of ticks (CLOCKS_PER_SEC) the process
                has run for.
 Parameters:    none
 Returns:       Clocks we've run for (centiseconds)
 ******************************************************************/
clock_t clock(void)
{
    if (frozen_time)
        return frozen_time - base_time;
    return __sysclock() - base_time;
}
