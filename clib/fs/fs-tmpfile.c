#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "io/io-internal.h"

FILE *tmpfile(void)
{
    char *filename;
    FILE *f;
    struct _IO_marker *markers;
    filename = tmpnam(NULL);
    if (filename == NULL)
        return NULL;

    markers = calloc(1, sizeof(*markers));
    if (markers == NULL)
        return NULL;
    strcpy(markers->filename, filename);

    f = fopen(filename, "w+b");
    if (f == NULL)
    {
        free(markers);
        return NULL;
    }

    f->_markers = markers;
    f->_flags |= _IO_DELETEONCLOSE;
    return f;
}
