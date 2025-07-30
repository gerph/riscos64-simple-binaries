#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "kernel-state.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_osgbpb
 Description:   OS_GBPB interface to read bytes from the FS
 Parameters:    op = OS_GBPB operation
                handle = file handle to operate on
                inout = the parameters to pass through to the OS_GBPB interface
 Returns:       -2 for failure, or 0 for success (-1 was C set)
 ******************************************************************/
int _kernel_osgbpb(int op, unsigned handle, _kernel_osgbpb_block *inout)
{
    _kernel_oserror *err;
    _kernel_swi_regs regs;

    regs.r[0] = op;
    regs.r[1] = handle;
    regs.r[2] = inout->dataptr;
    regs.r[3] = inout->nbytes;
    regs.r[4] = inout->fileptr;
    regs.r[5] = inout->buf_len;
    regs.r[6] = inout->wild_fld;

    err = _kernel_swi(OS_GBPB, &regs, &regs);

    inout->dataptr = regs.r[2];
    inout->nbytes = regs.r[3];
    inout->fileptr = regs.r[4];
    /* Additional parameters used for the enumeration operations */
    inout->buf_len = regs.r[5];
    inout->wild_fld = regs.r[6];

    if (err)
	{
        _kernel_copyerror(err);
		return _kernel_ERROR;
	}

    return 0;
}
