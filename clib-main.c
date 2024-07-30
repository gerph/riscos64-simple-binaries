#include <stdlib.h>
#include <string.h>

extern int main(int argc, const char *argv[]);

int __main(const char *cli,
           const void *appspace,
           const void *append,
           const void *memend)
{
    /* FIXME: Malloc heap should start at append */

    /* Build argv */
    char *arg = strdup(cli);
    char *p;
    int argc = 0;
    int in_spaces = 1;
    for (p=arg; *p; p++)
    {
        if (in_spaces)
        {
            if (*p != ' ')
            {
                /* No longer in spaces, so this is an argument */
                argc++;
                in_spaces = 0;
            }
        }
        else
        {
            if (*p == ' ')
            {
                *p = '\0';
                in_spaces = 1;
            }
        }
    }

    /* We now know how many arguments we have, so we can initialise argv */
    char **argv = calloc(sizeof(const char *), (argc + 1));

    in_spaces = 1;
    argc = 0;
    for (p=arg; *p; p++)
    {
        if (in_spaces)
        {
            if (*p != ' ')
            {
                /* No longer in spaces, so this is an argument */
                argv[argc] = p;
                argc++;
                in_spaces = 0;
            }
        }
        else
        {
            if (*p == ' ')
            {
                *p = '\0';
                in_spaces = 1;
            }
        }
    }

    argv[argc] = NULL;

    return main(argc, (const char **)argv);
}
