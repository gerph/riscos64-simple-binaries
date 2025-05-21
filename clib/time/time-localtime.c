#include <time.h>

struct tm *localtime(const time_t *time)
{
    /* FIXME: Very lazy implementation */
    return gmtime(time);
}
