#include <stdlib.h>
#include "swis_os.h"

int remove(const char *filename)
{
    _kernel_oserror *err = os_file2(6, filename);
    return (err == NULL ? 0 : -1);
}
