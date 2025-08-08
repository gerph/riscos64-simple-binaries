#ifndef TIME_CLOCK_H
#define TIME_CLOCK_H

#include <time.h>

/*************************************************** Gerph *********
 Function:      __clock_init
 Description:   Initialise the clock which returns the number of ticks process has run for
 Parameters:    none
 Returns:       none
 ******************************************************************/
void __clock_init(void);

/*************************************************** Gerph *********
 Function:      __clock_freeze
 Description:   Freeze/unfreeze the clock whilst we're pending user interaction
 Parameters:    freeze = true to freeze the clock, or false to unfreeze it
 Returns:       none
 ******************************************************************/
void __clock_freeze(bool freeze);

/*************************************************** Gerph *********
 Function:      clock
 Description:   Return number of ticks (CLOCKS_PER_SEC) the process
                has run for.
 Parameters:    none
 Returns:       Clocks we've run for (centiseconds)
 ******************************************************************/
clock_t clock(void);


#endif
