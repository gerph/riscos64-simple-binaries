
/* Define this to make failures of the heap fatal */
//#define HEAP_FAIL_IS_FATAL

#ifndef HEAP_TYPE
#error HEAP_TYPE must be set
#endif

extern void __heap_fatal(const char *msg);

#define HEAP_STRINGIFY(_x) # _x

#define HEAP_TYPEFUNC_HELPER(type, func) __heap_ ## type ## _ ## func
#define HEAP_TYPEFUNC(type, func) HEAP_TYPEFUNC_HELPER(type, func)
#define HEAP_FUNC(func) HEAP_TYPEFUNC(HEAP_TYPE, func)

