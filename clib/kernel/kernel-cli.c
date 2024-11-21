#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "swis.h"

extern _kernel_oserror *_last_error;

/*************************************************** Gerph *********
 Function:      _kernel_oscli
 Description:   Run a CLI command and report whether it errored - this
                may replace the current application.
 Parameters:    cmd-> the command to run
 Returns:       1 if ok, 0 if failed
 NOTE:          This is implemented according to the actual implementation.
                The PRM implies that the return indicates that there is an error.
 ******************************************************************/
int _kernel_oscli(const char *cmd)
{
    _kernel_swi_regs regs = {0};
    _kernel_oserror *err;
    regs.r[0] = (int32_t)cmd;
    err = _kernel_swi(OS_CLI, &regs, NULL);
    if (err)
        _last_error = err;
    return err == NULL;
}
