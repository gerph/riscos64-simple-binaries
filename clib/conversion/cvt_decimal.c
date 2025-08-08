/*******************************************************************
 * File:        cvt_decimal
 * Purpose:     Convert a decimal string
 * Author:      Gerph
 * Date:        2024-09-13
 ******************************************************************/

#include <stdint.h>
#include "cvt.h"

/*************************************************** Gerph *********
 Function:      __cvt_uint64_decimal
 Description:   Decimal conversion of a uint64 value
 Parameters:    value = the value to convert
                buffer-> the buffer to write to (20 characters long)
 Returns:       number of characters output
 ******************************************************************/
int __cvt_uint64_decimal(uint64_t value, char *buffer)
{
    char *p = buffer;
    /* Decimal printing */
    static uint64_t ints[] = {
            1,
            10,
            100,
            1000,
            10000,
            100000,
            1000000,
            10000000,
            100000000,
            1000000000,
            10000000000,
            100000000000,
            1000000000000,
            10000000000000,
            100000000000000,
            1000000000000000,
            10000000000000000,
            100000000000000000,
            1000000000000000000,
            10000000000000000000u,
        };
    int tensindex = 19;

    if (value < 100000)
        tensindex = 6;
    else if (value < 10000000000)
        tensindex = 10;

    int first = 1;
    while (tensindex >= 0)
    {
        int64_t m = ints[tensindex];
        if (value >= m)
        {
            first = 0;
            int digit = 1;
#ifdef ARCH_HAS_DIVISION
            digit = value / m;
            value = value % m;
#else
            value -= m;
            while (value >= m)
                digit += 1, value -= m;
#endif
            *p++ = '0' + digit;
        }
        else
        {
            if (!first)
                *p++ = '0';
        }
        tensindex -= 1;
    }
    /* Special case 0 */
    if (p == buffer)
        *p++ = '0';

    *p = '\0';

    return p - buffer;
}
