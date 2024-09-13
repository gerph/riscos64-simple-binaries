/*******************************************************************
 * File:        cvt
 * Purpose:     Internal conversions for numbers
 * Author:      Gerph
 * Date:        2024-09-13
 ******************************************************************/

#ifndef CVT_H
#define CVT_H

#define __CVT_DECIMAL_SIZE (20)

/*************************************************** Gerph *********
 Function:      __cvt_uint64_decimal
 Description:   Decimal conversion of a uint64 value
 Parameters:    value = the value to convert
                buffer-> the buffer to write to (20 characters long)
 Returns:       number of characters output
 ******************************************************************/
int __cvt_uint64_decimal(uint64_t value, char *buffer);

#endif
