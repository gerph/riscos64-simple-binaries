/* Lesser used seeking functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swis.h"
#include "swis_os.h"
#include "io/io-internal.h"
#include "fs/fs-errors.h"
#include <errno.h>


int fsetpos(FILE *fh, const fpos_t *posp)
{
    int fail = fseek(fh, posp->__pos, SEEK_SET);
    return fail;
}

void rewind(FILE *fh)
{
    fseek(fh, 0, SEEK_SET);
}

int fgetpos(FILE *fh, fpos_t *posp)
{
    long int pos = ftell(fh);
    posp->__pos = pos;
    return pos == -1 ? -1 : 0;
}

