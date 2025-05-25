/*******************************************************************
 * File:        io_internal.h
 * Purpose:     Internal information for our IO implementation
 * Author:      Gerph
 * Date:        5 Mar 2025
 ******************************************************************/

#ifndef IO_INTERNAL_H
#define IO_INTERNAL_H

#include <errno.h>
#include <stdio.h>

#define _IO_MAGIC (0x381F0000)
#define _IO_MAGIC_MASK (0xFFFF0000)
#define CHECK_MAGIC(fh, fail_code) \
                        do { \
                            if ( ((fh)->_flags & _IO_MAGIC_MASK) != _IO_MAGIC ) \
                            { \
                                errno = EBADF; \
                                return (fail_code); \
                            } \
                        } while (0)

#endif
