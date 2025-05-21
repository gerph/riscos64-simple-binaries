#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include "kernel.h"
#include "swis.h"



/*************************************************** Gerph *********
 Function:      _kernel_system
 Description:   Call the CLI command as a subprocess/replacement
 Parameters:    cmd-> the command to run
                chain = 0 to run as a sub-program
                        1 to replace the current program
 Returns:       1 if failed, 0 if successful?
 ******************************************************************/
int _kernel_system(const char *cmd, int chain)
{
    /* FIXME: Neither of these implementations are correct */
    if (chain)
    {
        /* Remove all our handlers */
        /* Call the command */
        int ok;
        ok = _kernel_oscli(cmd);
        /* Call OS_Exit if the command returns */
        exit(!ok);
    }
    else
    {
        /* Install new handlers for a sub-application */
        /* Call the new command */
        int ok;
        ok = _kernel_oscli(cmd);
        /* Return the return code of the command? */
        return !ok;
    }
    return 1;
}
