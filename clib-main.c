#include <stdlib.h>
#include <string.h>

/* Define this to put the arguments on the stack, rather then in the heap */
#define BUILD_ARGV_ON_STACK

extern int main(int argc, const char *argv[]);

int __main(const char *cli,
           const void *appspace,
           const void *append,
           const void *memend)
{
    int rc;

    /* FIXME: Malloc heap should start at append */

    /* Build argv */
#ifdef BUILD_ARGV_ON_STACK
    char arg[strlen(cli) + 1];
#else
    char *arg = malloc(strlen(cli) + 1);
    if (!arg)
    {
        os_write0("Not enough memory");
        os_newline();
        exit(1);
    }
#endif
    strcpy(arg, cli);

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
#ifdef BUILD_ARGV_ON_STACK
    char *argv[argc + 1];
#else
    char **argv = calloc(sizeof(const char *), (argc + 1));
#endif
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

    rc = main(argc, (const char **)argv);

    exit(rc);
    return rc;
}



typedef void (*atexit_func_t)(void);

#define ATEXIT_MAX (32)

static atexit_func_t atexit_funcs[ATEXIT_MAX];

int atexit(atexit_func_t func)
{
    int i;
    for (i=0; i<ATEXIT_MAX; i++)
    {
        if (atexit_funcs[i] == NULL)
        {
            atexit_funcs[i] = func;
            return 0;
        }
    }

    /* All slots filled */
    return -1;
}

void exit(int rc)
{
    atexit_func_t *funcsp = atexit_funcs;
    int i;

    /* Call the registered functions in reverse order */
    for (i=ATEXIT_MAX - 1; i>=0; i--)
    {
        if (atexit_funcs[i] != NULL)
        {
            atexit_func_t func = atexit_funcs[i];
            atexit_funcs[i] = NULL;
            func();
        }
    }

    _exit(rc);
}

