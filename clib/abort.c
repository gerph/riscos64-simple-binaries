#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include "kernel.h"
#include "swis.h"

void __attribute__ ((__noreturn__))
     abort(void)
{
    raise(SIGABRT);

    /* If we returned, we need to just get out */
    exit(1);
}
