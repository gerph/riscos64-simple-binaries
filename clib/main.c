#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "clib.h"
#include "kernel/kernel-state.h"
#include "heap/init.h"
#include "swis_os.h"
#include "env.h"

/* Define this to put the arguments on the stack, rather then in the heap */
#define BUILD_ARGV_ON_STACK

/* The minimum heap we want to have */
#define MINIMUM_HEAP (4*1024)

/* The minimum heap we want to have */
#define DEFAULT_STACK (64*1024)



extern int main(int argc, const char *argv[]);

void *__aif_base;
void *__aif_end;
void *__memory_end;
uint32_t __attribute__((weak)) __aif_stacksize;
uint32_t __attribute__((weak)) __heap_min;

static void __main_fail(const char *msg)
{
    os_write0(msg);
    os_newline();
    exit(1);
}

int __main(const char *cli,
           const void *appspace,
           void *append,
           void *memend)
{
    int rc;

    /* We want to initialise the environment so that we exit cleanly */
    _env_init();

    /**** Check out memory is sufficient and that we can allocate heap ****/
    /* WARNING: The stack limit is not currently enforced here */

    if (memend < append)
    {
        __main_fail("Not enough memory for application");
    }

    /* Malloc heap starts at append, and runs to the end of memory, less stack */
    uint64_t stack_size = __aif_stacksize ? __aif_stacksize : DEFAULT_STACK;
    uint64_t stack_limit = ((uint64_t)memend) - stack_size;
    if (stack_limit < (uint64_t)append)
    {
        __main_fail("Not enough memory for stack");
    }
    uint64_t heap_min = __heap_min ? __heap_min : MINIMUM_HEAP;
    if (stack_limit < (uint64_t)append + heap_min)
    {
        __main_fail("Not enough memory for heap");
    }
    _kernel_inmodule = false;
    __heap_init(append, (void*)stack_limit);

    /* Initialise all our libraries now that we safely have a heap */
    _clib_internalinit();

    /**** Build argv ****/

#ifdef BUILD_ARGV_ON_STACK
    int spacecli = strlen(cli) + 1;
    char arg[spacecli];
#else
    char *arg = malloc(spacecli);
    if (!arg)
    {
        __main_fail("Not enough memory for CLI");
    }
#endif
    memcpy(arg, cli, spacecli);

    char *p;
    int argc = 0;
    int in_spaces = 1;
    int in_quotes = 0;
    int escape = 0;
    for (p=arg; *p; p++)
    {
        if (*p == '\\')
        {
            escape = 1;
            continue;
        }
        if (escape)
        {
            escape = 0;
            continue;
        }

        if (!in_quotes)
        {
            if (in_spaces)
            {
                if (*p != ' ')
                {
                    /* No longer in spaces, so this is an argument */
                    argc++;
                    in_spaces = 0;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (*p == ' ')
                {
                    in_spaces = 1;
                    continue;
                }
            }
            if (*p == '"')
                in_quotes = 1;
        }
        else
        {
            if (*p == '"')
            {
                in_quotes = 0;
            }
        }
    }

    if (in_quotes)
        __main_fail("Missmatched quotes in command line arguments");

    /* We now know how many arguments we have, so we can initialise argv */
#ifdef BUILD_ARGV_ON_STACK
    char *argv[argc + 1];
#else
    char **argv = calloc(sizeof(const char *), (argc + 1));
    if (!argv)
    {
        __main_fail("Not enough memory for CLI array");
    }
#endif
    in_spaces = 1;
    in_quotes = 0;
    escape = 0;
    argc = 0;
    char *argout=arg;
    for (p=arg; *p; p++)
    {
        if (*p == '\\')
        {
            escape = 1;
            continue;
        }
        if (escape)
        {
            escape = 0;
            if (*p != '"')
                *argout++ = '\\';
            *argout++=*p;
            continue;
        }

        if (!in_quotes)
        {
            if (in_spaces)
            {
                if (*p != ' ')
                {
                    /* No longer in spaces, so this is an argument */
                    argv[argc] = argout;
                    argc++;
                    in_spaces = 0;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (*p == ' ')
                {
                    *argout++ = '\0';
                    in_spaces = 1;
                    continue;
                }
            }

            if (*p == '"')
                in_quotes = 1;
            else
                *argout++=*p;
        }
        else
        {
            if (*p == '"')
            {
                in_quotes = 0;
            }
            else
            {
                *argout++=*p;
            }
        }
    }

    argv[argc] = NULL;

    /*** Call main ***/
    rc = main(argc, (const char **)argv);

    exit(rc);
    return rc;
}
