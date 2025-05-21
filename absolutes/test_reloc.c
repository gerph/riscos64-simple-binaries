#include "swis.h"
#include "swis_os.h"

int __aif_stacksize = 1024*16;

int myprint(char *str)
{
    int n = 0;
    os_write0(str);
    os_newline();

    return n;
}

void call_1(void)
{
    myprint("call_1 called");
}

void call_2(void)
{
    myprint("call_2 called");
}

typedef void (*func_f)(void);

func_f funcs[] = {
    call_1,
    call_2,
};

int main(int argc, char *argv)
{
    myprint("Starting...");
    for (int i=0; i<sizeof(funcs) / sizeof(funcs[0]); i++)
    {
        funcs[i]();
    }
    return 0;
}
