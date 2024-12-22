#include <stdio.h>

#define STRINGIFY(a) _STRINGIFY(a)
#define _STRINGIFY(a) #a

int main(int argc, char *argv[])
{
#define TEST(format, value) \
    printf("Testing %s of %s: '" format "'\n", format, STRINGIFY(value), value);

    TEST("%f", 1.0);
    TEST("%f", 1.5);
    TEST("%f", 100.0/3);
    TEST("%f", 1E20);
    TEST("%.2f", 100.0/3);
    TEST("%4f", 100.0/3);
    TEST("%9f", 100.0/3);
    TEST("%-9f", 100.0/3);
    return 0;
}
