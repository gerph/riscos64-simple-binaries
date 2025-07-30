#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "kernel-state.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_oswrch
 Description:   OS_WriteC
 Parameters:    character
 Returns:       -2 if failure, 0 if success
 ******************************************************************/
int _kernel_oswrch(int c)
{
    _kernel_oserror *err;
    err = os_writec(c);
    if (err)
	{
        _kernel_copyerror(err);
		return _kernel_ERROR;
	}

    return 0;
}
