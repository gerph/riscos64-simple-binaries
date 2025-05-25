#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Define this to make the atexit() handlers go on the heap, rather than zero-init */
//#define ATEXIT_HANDLERS_ON_HEAP

/* How many atexit() handlers we support */
//#define ATEXIT_MAX (32) /* Standard defined value */
#define ATEXIT_MAX (8)


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

void __atexit_trigger(void)
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
#ifdef ATEXIT_HANDLERS_ON_HEAP
        free(funcsp);
        funcsp = NULL;
#endif
    }
}
