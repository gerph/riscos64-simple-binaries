#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "kernel-state.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_osword
 Description:   OS_Word interface
 Parameters:    op = OS_Word reason
                data-> the data for the OS_Word call.
 Returns:       return r1, or _kernel_ERROR for failure
 ******************************************************************/
int _kernel_osword(int op, int *data)
{
    _kernel_oserror *err;
    _kernel_swi_regs regs;

    regs.r[0] = op;
    regs.r[1] = data;

    err = _kernel_swi(OS_Word, &regs, &regs);
    if (err)
	{
        _kernel_copyerror(err);
        return _kernel_ERROR;
	}

    return regs.r[1];
}
