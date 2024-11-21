/*******************************************************************
 * File:        kernel-backtrace
 * Purpose:     Perform a backtrace, reporting that state of the system
 * Author:      Gerph
 * Date:        14 Sep 2024
 ******************************************************************/

#include "kernel.h"
#include "swis_os.h"
#include "cvt.h"

/*************************************************** Gerph *********
 Function:      _kernel_backtrace
 Description:   Report the backtrace to VDU
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _kernel_backtrace(void)
{
    _kernel_unwindblock uwp = {0};
    char *lang;
    int state;

    os_write0("Backtrace:");
    os_newline();

    state = _kernel_unwind(&uwp, &lang);
    while (state >= 0)
    {
        char buffer[20];

        /* Write the address */
        __cvt_uint64_hex(uwp.pc, buffer, 16, 1);
        os_write0(buffer);
        os_write0(" : ");

        const char *procname = _kernel_procname(uwp.pc);
        if (!procname)
            procname = "<unknown>";
        os_write0(procname);
        os_newline();

        if (state == 0)
            break; /* That was the last entry */
        state = _kernel_unwind(&uwp, &lang);
    }
    if (state < 0)
    {
        os_write0("Stack frames corrupt");
        os_newline();
    }
}
