#include "kernel.h"
#include "swis.h"

void __assert_fail(const char *message)
{
    static _kernel_oserror err = {0, "Assertion failed"};
    os_write0("Assertion failed: ");
    os_write0(message);
    os_newline();
    os_generateerror(&err);
}
