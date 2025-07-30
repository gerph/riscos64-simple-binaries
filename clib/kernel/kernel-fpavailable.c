#include "kernel.h"

/*************************************************** Gerph *********
 Function:      _kernel_fpavailable
 Description:   Determine whether floating point is available
 Parameters:    none
 Returns:       0 if no FP is available
                1 if standard FP is available
 ******************************************************************/
int _kernel_fpavailable(void)
{
#ifdef __riscos64
    return 1;
#else
    /* FIXME: I'm going to say yes here if we're built for other systems,
              but we could probably do with checking really. */
    return 1;
#endif
}
