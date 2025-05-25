#include <stdlib.h>
#include "swis_os.h"

#include "fs-errors.h"

int remove(const char *filename)
{
    _kernel_oserror *err = os_file2(6, filename);
    if (err)
        __fs_seterrno(err);
    return (err == NULL ? 0 : -1);
}
