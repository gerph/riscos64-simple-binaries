#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "swis.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_osrdch
 Description:   OS_ReadC
 Parameters:    none
 Returns:       character, or -1 if error, or -27 if escape
 ******************************************************************/
int _kernel_osrdch(void)
{
    return os_readc();
}
