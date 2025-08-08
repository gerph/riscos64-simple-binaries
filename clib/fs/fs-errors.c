/*******************************************************************
 * File:        fs-errors
 * Purpose:     Handle FS errors
 * Author:      Gerph
 * Date:        25 Mar 2025
 ******************************************************************/

#include <errno.h>

#include "fs-errors.h"

/*************************************************** Gerph *********
 Function:      __fs_converterr
 Description:   Convert the RISC OS error to an errno value, based on
                the filesystem errors.
 Parameters:    err-> the error block returned
 Returns:       errno value to return
 ******************************************************************/
int __fs_converterr(_kernel_oserror *err)
{
    int errnum = err->errnum;
    int errblock = (errnum & ~0xFFFF);
    if (errblock == 0x10000 || errnum < 0x100)
    {
        /* Filesystem errors */
        int lownum = errnum & 0xFF;
        switch (lownum)
        {
            case 0xA7: /* Is a directory */
                return EISDIR;

            case 0xB4: /* Not empty */
                return ENOTEMPTY;

            case 0xBD: /* Bad access */
                return EACCES;

            case 0xC0: /* Too many open files */
                return EMFILE;

            case 0xCC: /* Bad filename */
                return ENOENT; /* Or ENXIO? */

            case 0xD6: /* File not found */
                return ENOENT;

            case 0xDE: /* Bad handle */
                return EBADF;

            default:
                return EIO; /* Miscellaneous error */
        }
    }

    return EIO; /* Miscellaneous error */
}


/*************************************************** Gerph *********
 Function:      __fs_seterrno
 Description:   Set the errno variable based on filesystem error numbers
 Parameters:    err-> the error block returned
 Returns:       none
 ******************************************************************/
void __fs_seterrno(_kernel_oserror *err)
{
    errno = __fs_converterr(err);
}
