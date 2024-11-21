/*******************************************************************
 * File:        kernel-escape
 * Purpose:     Handling of the escapes
 * Author:      Gerph
 * Date:        17 Aug 2024
 ******************************************************************/

#include "kernel.h"
#include "swis_os.h"

int _kernel_escape_seen(void)
{
    /* FIXME: We don't have a handler for escapes, so we're going to use OS_ReadEscapeState */
    return os_readescapestate();
}
