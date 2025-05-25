/*******************************************************************
 * File:        fs-errors
 * Purpose:     Handle FS errors
 * Author:      Gerph
 * Date:        25 Mar 2025
 ******************************************************************/

#include <errno.h>

#include "fs-errors.h"

/*************************************************** Gerph *********
 Function:      __fs_seterrno
 Description:   Set the errno variable based on filesystem error numbers
 Parameters:    err-> the error block returned
 Returns:       none
 ******************************************************************/
void __fs_seterrno(_kernel_oserror *err)
{
    int errnum = err->errnum;
    if ((errnum & ~0xFFFF) == 1)
    {
        /* Filesystem errors */
        int lownum = errnum & 0xFF;
        switch (lownum)
        {
            case 0xA7: /* Is a directory */
                errno = EISDIR;
                break;

            case 0xB4: /* Not empty */
                errno = ENOTEMPTY;
                break;

            case 0xBD: /* Bad access */
                errno = EACCES;
                break;

            case 0xC0: /* Too many open files */
                errno = EMFILE;
                break;

            case 0xCC: /* Bad filename */
                errno = ENOENT; /* Or ENXIO? */
                break;

            case 0xD6: /* File not found */
                errno = ENOENT;
                break;

            case 0xDE: /* Bad handle */
                errno = EBADF;
                break;

            default:
                errno = EIO; /* Miscellaneous error */
        }
    }
    else
    {
        errno = EIO; /* Miscellaneous error */
    }
}
