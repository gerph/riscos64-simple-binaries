#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "io/io-internal.h"
#include "io/io-file-fopen.h"


FILE *freopen(const char *filename, const char *mode, FILE *oldfh)
{
    if (!oldfh)
    {
        errno = EBADF;
        return NULL;
    }
    if (filename == NULL)
    {
        /* Request to change the mode - not supported and is ignored */
        return oldfh;
    }

    CHECK_MAGIC(oldfh, NULL);

    /* We must first close this file, but not free it. */
    _fclose(oldfh);

    /* Now we perform the open with this handle */
    if (!_fopen(filename, mode, oldfh))
    {
        if (oldfh != stdout &&
            oldfh != stderr &&
            oldfh != stdin)
            free(oldfh);
        return NULL;
    }

    return oldfh;
}
