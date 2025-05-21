#include <stdio.h>
#include <time.h>
#include "swis.h"

int main(void)
{
    static _kernel_oserror err = { 123, "Fiddlesticks!" };
    _swi(OS_GenerateError, _IN(0), &err);
    return 0;
}
