#include <stdio.h>
#include "io/io-internal.h"


static FILE _stdin = {0};
static FILE _stdout = {0};
static FILE _stderr = {0};
FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;
