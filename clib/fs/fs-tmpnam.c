#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "kernel.h"

/**
 * Generate a temporary filename with a given signature.
 *
 * @return pointer to name, or NULL if no name could be generated.
 */
static char *_sys_tmpnam_(char *name, int sig)
{
    char *tail;
    bool use_dollar = false;
    /* JRF: I'm not happy with this; it means that the Wimp$ScrapDir path
            is expanded unnecessarily - we could just use the variable name
            in the filename produced. */
    if (_kernel_getenv("Wimp$ScrapDir", name, L_tmpnam-10) != NULL)
    {
      strcpy(name, "$.tmp");
      use_dollar = true;
    }

    {
        /* Check that the directory exists */
        int objtype = _kernel_osfile(5, name, NULL);
        /* The name location must be a directory (or an image) */
        if (objtype != 2 && objtype != 3)
        {
            if (use_dollar)
            {
                /* This is a very minimal system without Wimp$ScrapDir, so fall back to $ */
                strcpy(name, "$");
            }
            else
            {
                return NULL;
            }
        }
    }

    tail = name + strlen(name);
    sprintf(tail, ".x%.8x", sig);
    return name;
}


static char _tmp_file_name[L_tmpnam] = "";

char *tmpnam(char *name)
{
    static int counter = 0;
    if (name == NULL)
        name = _tmp_file_name;

    do {
      int sig = clock() ^ counter++;
      /* JRF: Return NULL if we cannot generate a temporary filename. */
      if (!_sys_tmpnam_(name, sig))
      {
        errno = ENOENT;
        return NULL;
      }
    } while (_kernel_osfile(17, name, NULL) != 0);

    return name;
}
