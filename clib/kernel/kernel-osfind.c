#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "kernel-state.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_osfind
 Description:   OS_Find interface
 Parameters:    op = OS_Find reason
                name = filename
 Returns:       Open: 0 if open failed (no error), or file handle, -2 failure
                Close: 0 for success -2 for failure
 ******************************************************************/
int _kernel_osfind(int op, const char *name)
{
    _kernel_oserror *err;
    _kernel_swi_regs regs;

    regs.r[0] = op;
    regs.r[1] = name;

    err = _kernel_swi(OS_Find, &regs, &regs);
    if (err)
	{
        _kernel_copyerror(err);
		return _kernel_ERROR;
	}

    return regs.r[0];
}
