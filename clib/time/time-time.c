#include <time.h>
#include "swis_os.h"


typedef uint64_t quin_t; /* A 5-byte time - always initialise the value to 0 before updating */


time_t time(time_t *tloc)
{
    quin_t quin = 0;

    if (os_word(14, 3, (char*)&quin))
        quin = 0;
    if (tloc)
        *tloc = quin / 100;
    return quin / 100;
}
