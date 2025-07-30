#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "kernel-state.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_osargs
 Description:   OS_Args interface
 Parameters:    op = OS_Args reason
                handle = file handle
                arg = additional argument
 Returns:       if op|handle == 0: returns r0
                else: returns r2
 ******************************************************************/
int _kernel_osargs(int op, unsigned handle, int arg)
{
    _kernel_oserror *err;
    _kernel_swi_regs regs;

    regs.r[0] = op;
    regs.r[1] = handle;
    regs.r[2] = arg;

    err = _kernel_swi(OS_Args, &regs, &regs);
    if (err)
    {
        _kernel_copyerror(err);
        return _kernel_ERROR;
    }

    if (op == 0 && handle == 0)
        return regs.r[0];
    return regs.r[2];
}
