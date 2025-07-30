/*******************************************************************
 * File:        kernel-escape
 * Purpose:     Handling of the escapes
 * Author:      Gerph
 * Date:        17 Aug 2024
 ******************************************************************/

#include "kernel.h"
#include "swis_os.h"

/*************************************************** Gerph *********
 Function:      _kernel_escape_seen
 Description:   Check whether the Escape key has been pressed
 Parameters:    none
 Returns:       1 if escape has been pressed, or 0 if not
 ******************************************************************/
int _kernel_escape_seen(void)
{
    /* FIXME: We don't have a handler for escapes, so we're going to use OS_ReadEscapeState */
    int state = os_readescapestate();
    //printf("[escape = %c]", state ? 'Y' : 'n');
    return state;
}
