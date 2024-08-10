#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "heap_init.h"
#include "swis-os.h"

/* Define this to put the arguments on the stack, rather then in the heap */
#define BUILD_ARGV_ON_STACK

/* Define this to make the atexit() handlers go on the heap, rather than zero-init */
//#define ATEXIT_HANDLERS_ON_HEAP

/* The minimum heap we want to have */
#define MINIMUM_HEAP (4*1024)

/* The minimum heap we want to have */
#define DEFAULT_STACK (64*1024)

/* How many atexit() handlers we support */
//#define ATEXIT_MAX (32) /* Standard defined value */
#define ATEXIT_MAX (8)



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
    __heap_init(append, (void*)stack_limit);


    /**** Build argv ****/

#ifdef BUILD_ARGV_ON_STACK
    char arg[strlen(cli) + 1];
#else
    char *arg = malloc(strlen(cli) + 1);
    if (!arg)
    {
        __main_fail("Not enough memory for CLI");
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

    /*** Call main ***/
    rc = main(argc, (const char **)argv);

    exit(rc);
    return rc;
}



typedef void (*atexit_func_t)(void);


#ifdef ATEXIT_HANDLERS_ON_HEAP
static atexit_func_t *atexit_funcs;
#else
static atexit_func_t atexit_funcs[ATEXIT_MAX];
#endif

int atexit(atexit_func_t func)
{
    int i;
#ifdef ATEXIT_HANDLERS_ON_HEAP
    if (atexit_funcs == NULL)
    {
        atexit_funcs = calloc(sizeof(atexit_funcs), ATEXIT_MAX);
        if (atexit_funcs == NULL)
            return -1; /* Couldn't allocate */
    }
#endif

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


void _clib_finalise(void)
{
    atexit_func_t *funcsp = atexit_funcs;
    int i;

#ifdef ATEXIT_HANDLERS_ON_HEAP
    if (funcsp)
#endif
    {
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
    }

    /* Shut down our modules */
    __getenv_final();
    // __io_final();
    // __heap_final();
}

void __attribute__((noreturn)) exit(int rc)
{
    _clib_finalise();

    _Exit(rc);
}
