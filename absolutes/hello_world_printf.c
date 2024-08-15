/*******************************************************************
 * File:        hello_world_printf
 * Purpose:     Showing that Printf and the C library work
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    if (argc > 1)
    {
        printf("Args:\n");
        for (int arg=1; arg<argc; arg++)
        {
            printf("  %s\n", argv[arg]);
        }
    }
    printf("C library:\n");
    printf("%s", _clib_version());
    return 0;
}
