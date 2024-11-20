#include <stdlib.h>
#include "swis_os.h"

int rename(const char *old, const char *new)
{
    _kernel_oserror *err;

    err = os_fscontrol3(25, old, new);
    return (err == NULL) ? 0 : -1;
}
