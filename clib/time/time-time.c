#include <time.h>
#include "swis_os.h"


typedef uint64_t quin_t; /* A 5-byte time - always initialise the value to 0 before updating */

#define TIME_BASE_1970 ((70lu*365 + 70/4) * 24 * 60 * 60)


time_t time(time_t *tloc)
{
    time_t value;
    quin_t quin = 0;

    if (os_word(14, 3, (char*)&quin))
        quin = 0;
    value = (quin / 100) - TIME_BASE_1970;
    if (tloc)
        *tloc = value;
    return value;
}
