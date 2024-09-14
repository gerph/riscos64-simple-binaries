/*******************************************************************
 * File:        cvt_hex
 * Purpose:     Convert a hex string
 * Author:      Gerph
 * Date:        2024-09-13
 ******************************************************************/

#include <stdint.h>
#include "cvt.h"

/*************************************************** Gerph *********
 Function:      __cvt_uint64_hex
 Description:   Decimal conversion of a uint64 value
 Parameters:    value = the value to convert
                buffer-> the buffer to write to (20 characters long)
                width = the width to start at
                spaced = 1 to output leading spaces, 0 for nothing, -1 for zeros
 Returns:       number of characters output
 ******************************************************************/
int __cvt_uint64_hex(uint64_t value, char *buffer, int width, int spaced)
{
    char *p = buffer;
    int started = (spaced == -1);
    int shift;
    for (shift = (width * 4) - 4; shift >= 0; shift -= 4)
    {
        int v = (value >> shift) & 15;
        if (started || v > 0)
        {
            char out = "0123456789ABCDEF"[v];
            *p++ = out;
            started = 1;
        }
        else if (spaced == 1)
        {
            *p++ = ' ';
        }
    }
    if (value == 0 && !started)
        *p++ = '0';

    *p++ = '\0';

    return p - buffer;
}
