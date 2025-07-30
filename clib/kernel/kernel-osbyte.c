#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "kernel-state.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_osbyte
 Description:   OS_Byte interface
 Parameters:    op = OS_Byte reason
                x = BBC X register
                y = BBC Y register
 Returns:       X | (Y<<8) | (C<<16) ; C is never used in 64bit
                _kernel_ERROR for failure
 ******************************************************************/
int _kernel_osbyte(int op, int x, int y)
{
    _kernel_oserror *err;
    _kernel_swi_regs regs;

    regs.r[0] = op;
    regs.r[1] = x;
    regs.r[2] = y;

    err = _kernel_swi(OS_Byte, &regs, &regs);
    if (err)
	{
        _kernel_copyerror(err);
		return _kernel_ERROR;
	}

    return regs.r[0] | (regs.r[1] << 8);
}
