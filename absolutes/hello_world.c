#include "swis.h"
#include "swis_os.h"

int myprint(char *str)
{
    int n = 0;
    for (; *str; str++)
    {
        os_writec(*str);
        n += 1;
    }
    os_newline();

    return n;
}

int main(int argc, char *argv)
{
    return myprint("Hello world");
}
