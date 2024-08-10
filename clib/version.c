/*******************************************************************
 * File:        version
 * Purpose:     Obtain the version of the C library
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include "VersionNum"

/* q.v. https://www.riscos.com/support/developers/riscos6/programmer/extendedc.html */

const char *_clib_version(void)
{
    return "C library/64\n"
           "GerphCore vsn " Module_FullVersionAndDate "\n";
}
