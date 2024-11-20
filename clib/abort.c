#include <stdlib.h>
#include <assert.h>
#include "kernel.h"
#include "swis.h"
#include "swis_os.h"
#include "cvt.h"

void __attribute__ ((__noreturn__))
     abort(void)
{
    os_write0("Aborted");
    os_newline();
    os_newline();

    _kernel_backtrace();

    exit(1);
}
