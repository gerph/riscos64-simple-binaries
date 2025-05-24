#include <ctype.h>

#define is_impl(_name) \
int (is##_name) (int c) \
{ \
    const short unsigned int *ctype_b = (*__ctype_b_loc ()); \
    short unsigned int flags = ctype_b[c & 255]; \
    return flags & _IS##_name; \
}

/* Define all the 'is' functions */
is_impl(upper)
is_impl(lower)
is_impl(alpha)
is_impl(digit)
is_impl(xdigit)
is_impl(space)
is_impl(print)
is_impl(graph)
is_impl(blank)
is_impl(cntrl)
is_impl(punct)
is_impl(alnum)

/* isascii isn't in the flags */
int (isascii)(int c)
{
    if (c & ~127)
        return 0;
    return 1;
}
