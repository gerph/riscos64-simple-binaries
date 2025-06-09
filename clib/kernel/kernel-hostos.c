#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "swis.h"

/*************************************************** Gerph *********
 Function:      _kernel_hostos
 Description:   Report the host OS (OS_Byte 0, 1)
 Parameters:    none
 Returns:       6 for RISC OS (https://beebwiki.mdfs.net/OSBYTE_%2600)
 ******************************************************************/
int _kernel_hostos(void)
{
    _kernel_swi_regs regs = {0};
    _kernel_oserror *err;
    err = _kernel_swi(OS_CLI, NULL, &regs);
    if (err)
        return -1;
    return regs.r[0];
}
