#include <stdlib.h>
#include <assert.h>
#include "kernel.h"
#include "swis.h"
#include "swis_os.h"
#include "cvt.h"

void __attribute__ ((__noreturn__))
     __assert_fail (const char *__assertion, const char *__file,
                    unsigned int __line, const char *__function)
{
    char line[__CVT_DECIMAL_SIZE];

    static _kernel_oserror err = {0, "Assertion failed"};
    os_write0("Assertion failed: ");
    os_write0(__assertion);
    os_newline();
    os_write0("              at: ");
    if (__function)
    {
        os_write0(__function);
        os_write0(" in ");
    }
    os_write0(__file);
    os_write0(", line ");

    __cvt_uint64_decimal(__line, line);
    os_write0(line);
    os_newline();

    _kernel_backtrace();

    os_generateerror(&err);
}
