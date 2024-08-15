#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "swis.h"

extern _kernel_oserror *_last_error;

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
