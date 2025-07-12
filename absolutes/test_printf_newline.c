/* Test that the printf with newline works ok */


#include <stdio.h>

int main(int argc, char *argv[])
{
    /* Newline in the format string */
    printf("using %s first\n", "percent s");
    printf("newline\nthen %s after\n", "percent s");
    printf("%s then %s\n", "percent s", "percent s");
    printf("no gap: %s%s\n", "percent s", "percent s");

    printf("----\n");
    {
        char *message = "hello\nworld";
        printf("simple: '%s'\n", message);
        printf("field width: '%16s'\n", message);
        printf("field width (left): '%-16s'\n", message);
        printf("short field width: '%5s'\n", message);
        printf("short field width (left): '%-5s'\n", message);
        printf("precision: '%.16s'\n", message);
        printf("short precision: '%.5s'\n", message);
    }

    return 0;
}
