/*******************************************************************
 * File:        io-internal.h
 * Purpose:     Internal information for our IO implementation
 * Author:      Gerph
 * Date:        5 Mar 2025
 ******************************************************************/

#ifndef IO_INTERNAL_H
#define IO_INTERNAL_H

#include <errno.h>
#include <limits.h>
#include <stdio.h>

/* For fields, see:
     /usr/xcc/aarch64-unknown-linux-gnu/aarch64-unknown-linux-gnu/sysroot/usr/include/bits/types/struct_FILE.h
   We use:
    * `_flags` - to mark our streams as valid and their capabilities.
    * `_shortbuf[0]` - for the character which was ungetc'd.
    * `_fileno` - for the RISC OS file handle that is used.
    * `_chain` - links together all the FILE blocks to allow them to be freed.
    * `_markers` - may contain the filename used by the file when 'delete on close' set.
 */

/* Flags we use: */
#define _IO_CHARPUSHED      (1u<<0)  /* Character has been pushed back on to stream with ungetc */
#define _IO_DELETEONCLOSE   (1u<<1)  /* Stream must be deleted when closed (for tmpfile) */
#define _IO_READABLE        (1u<<2)  /* Can be read */
#define _IO_WRITABLE        (1u<<3)  /* Can be written */
#define _IO_CONSOLE         (1u<<4)  /* Is a console */

#define _IO_MAGIC (0x381F0000u)
#define _IO_MAGIC_MASK (0xFFFF0000u)
#define CHECK_MAGIC(fh, fail_code) \
                        do { \
                            if ( ((fh)->_flags & _IO_MAGIC_MASK) != _IO_MAGIC ) \
                            { \
                                errno = EBADF; \
                                return (fail_code); \
                            } \
                        } while (0)

/* _IO_marker is used to give us information about the file - it doesn't have to be here, but it's easy to add */
struct _IO_marker {
    char filename[PATH_MAX]; /* temporary filename name */
};

#define IO_IS_READABLE(fh)   ((fh)->_flags & _IO_READABLE)
#define IO_IS_WRITABLE(fh)   ((fh)->_flags & _IO_WRITABLE)

#define IO_IS_CONSOLE(fh)    ((fh)->_flags & _IO_CONSOLE)
#define IO_IS_KEYBOARD(fh)   (((fh)->_flags & (_IO_CONSOLE | _IO_READABLE)) == (_IO_CONSOLE | _IO_READABLE))
#define IO_IS_SCREEN(fh)     (((fh)->_flags & (_IO_CONSOLE | _IO_WRITABLE)) == (_IO_CONSOLE | _IO_WRITABLE))

/* fileno used for consoles */
#define IO_FD_CONSOLE       (-2)

#endif
